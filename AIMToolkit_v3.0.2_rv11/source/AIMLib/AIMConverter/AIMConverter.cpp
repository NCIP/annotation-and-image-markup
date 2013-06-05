/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


// AIMConverter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "AIMConverter.h"

#include <exception>
#include <iostream>
#include <fstream>

using namespace std;

#include "ConverterUtil.h"

static const std::string CONVERTER_PARAM_SR = std::string("SR");
static const std::string CONVERTER_PARAM_XML = std::string("AIM");
static const std::string CONVERTER_PARAM_CDA = std::string("CDA");

AIMConverter::AIMConverter()
{
}

AIMConverter::~AIMConverter()
{
}

int main(int argc, char* argv[])
{
	string err; // error(s) to report

	if (argc > 6)
	{
		string arg;
		string inFileName, outFileName;
		AIMConverter::AIM_FILE_TYPE inputType = AIMConverter::AFT_UNKNOWN;
		AIMConverter::AIM_FILE_TYPE outputType = AIMConverter::AFT_UNKNOWN;

		int argIdx = 1;
		while (argIdx < 4 && err.length() < 1) // check the first two parameters with their arguments
		{
			// Input file type
			arg.assign(argv[argIdx]);
			if (ConverterUtil::nocase_cmp(arg, "-i") == 0 || ConverterUtil::nocase_cmp(arg, "-input") == 0 )
			{
				arg.assign(argv[argIdx + 1]);
				if (ConverterUtil::nocase_cmp(arg, CONVERTER_PARAM_XML) == 0)
					inputType = AIMConverter::AFT_AIM_XML;
				else if (ConverterUtil::nocase_cmp(arg, CONVERTER_PARAM_SR) == 0)
					inputType = AIMConverter::AFT_DICOM_SR;
				else if (ConverterUtil::nocase_cmp(arg, CONVERTER_PARAM_CDA) == 0)
					inputType = AIMConverter::AFT_HL7_CDA;
				else
					err.assign("Unknown input type \"").append(arg).append("\"");
			}
			// Output file type
			else if (ConverterUtil::nocase_cmp(arg, "-o") == 0 || ConverterUtil::nocase_cmp(arg, "-output") == 0 )
			{
				arg.assign(argv[argIdx + 1]);
				if (ConverterUtil::nocase_cmp(arg, CONVERTER_PARAM_XML) == 0)
					outputType = AIMConverter::AFT_AIM_XML;
				else if (ConverterUtil::nocase_cmp(arg, CONVERTER_PARAM_SR) == 0)
					outputType = AIMConverter::AFT_DICOM_SR;
				else if (ConverterUtil::nocase_cmp(arg, CONVERTER_PARAM_CDA) == 0)
					outputType = AIMConverter::AFT_HL7_CDA;
				else
					err.assign("Unknown output type \"").append(arg).append("\"");
			}
			argIdx += 2;
		}

		if (inputType == AIMConverter::AFT_UNKNOWN || outputType == AIMConverter::AFT_UNKNOWN || err.length() > 0)
			goto USAGE;

		inFileName.assign(argv[5]);
		outFileName.assign(argv[6]);

		// Do Conversion
		AIMConverter aimConverter;
		err = aimConverter.DoConversion(inFileName, inputType, outFileName, outputType);

		if (err.length() > 0)
			goto USAGE;

		return 0;
	}

USAGE:
	// Usage:
	// converter -i[nput] AIM|SR|CDA -o[utput] AIM|SR|CDA input_file_name output_file_name

	if (err.length() > 0)
		cout << "Error: " << err << endl;

	cout << "Usage:" << endl;
	string progName = argv[0];
	string::size_type pos = progName.find_last_of("\\");
	if (pos != string::npos)
		progName = progName.substr(pos + 1);
	pos = progName.find_last_of("/");
	if (pos != string::npos)
		progName = progName.substr(pos + 1);
	const static std::string params(CONVERTER_PARAM_XML + "|" + CONVERTER_PARAM_SR + "|" + CONVERTER_PARAM_CDA); // "AIM|SR|CDA"
	cout << progName << " -i[nput] " << params << " -o[utput] " << params << " input_file output_file" << endl;

	return -1;
}

string AIMConverter::DoConversion(const string& inFileName, AIM_FILE_TYPE inFileType, const string& outFileName, AIM_FILE_TYPE outFileType)
{
	string err;

	// 1. Input/Output file types are the same
	// Do simple file copy
	if (inFileType == outFileType)
	{
		ifstream infile(inFileName.c_str());
		if (infile)
		{
			ofstream outfile(outFileName.c_str());
			if (outfile)
			{
				outfile << infile.rdbuf();
				outfile.flush();
				outfile.close();
				infile.close();
			}
			else
			{
				err.assign("Output file \"").append(outFileName).append("\" cannot be open for writing");
			}
		}
		else
		{
			err.assign("Input file \"").append(inFileName).append("\" cannot be open for reading");
		}

		return err;
	}

	// 2. Input/output file types are different.

	aim_lib::AnnotationPtrVector annotations;
	aim_lib::BaseModel* pInputModel = NULL;

	// Create input document model
	try
	{
		err = this->CreateModel(inFileType, &pInputModel);
	}
	catch(exception& ex)
	{
		err.assign("Failed to create input file model for file \"" + inFileName + "\"\nError:\n").append(ex.what());
	}

	if (err.length() > 0)
	{
		delete pInputModel;
		pInputModel = NULL;
		return err;
	}

	if (pInputModel == NULL)
		return "Failed to create input file model. Out of memory?";

	// Read all annotations into memory
	try
	{
		int annCnt = pInputModel->ReadAnnotationsFromFile(inFileName);
		while(annCnt > 0)
		{
			aim_lib::Annotation* pAnnotation = pInputModel->GetNextAnnotation(&pAnnotation);
			if (pAnnotation != NULL)
				annotations.push_back(pAnnotation);
			annCnt--;
		}
	}
	catch(exception& ex)
	{
		err.assign("Error reading annotation(s) from file \"").append(inFileName).append("\":\n").append(ex.what());
	}

	delete pInputModel;
	pInputModel = NULL;

	if (annotations.size() == 0)
		return "No annotations were read from file \"" + inFileName + "\". Does the file exist?";

	// Create output document model
	aim_lib::BaseModel* pOutputModel = NULL;
	try
	{
		err = this->CreateModel(outFileType, &pOutputModel);
	}
	catch(exception& ex)
	{
		err.assign("Failed to create output file model for file \"" + outFileName + "\"\nError:\n").append(ex.what());
	}

	if (err.length() > 0)
	{
		delete pOutputModel;
		pOutputModel = NULL;
		return err;
	}

	if (pOutputModel == NULL)
		return "Failed to create output file model. Out of memory?";

	// Write annotation(s) to file
	try
	{
		pOutputModel->WriteAnnotationsToFile(annotations, outFileName);
	}
	catch(exception& ex)
	{
		err.assign("Error writing annotation(s) to file \"").append(outFileName).append("\":\n").append(ex.what());
	}

	delete pOutputModel;
	pOutputModel = NULL;

	return err;
}

std::string AIMConverter::CreateModel(AIM_FILE_TYPE modelType, aim_lib::BaseModel** pModel)
{
	std::string err;

	switch(modelType)
	{
	case AFT_AIM_XML:
		try
		{
			*pModel = new aim_lib::XmlModel();
		}
		catch(...){}
		break;
	case AFT_DICOM_SR:
		try
		{
			*pModel = new aim_lib::DcmModel();
		}
		catch(...){}
		break;
	case AFT_HL7_CDA:
		err.assign("HL7 CDA model is not implemented");
		//try
		//{
		//	*pModel = new aim_lib::CdaModel();
		//}
		//catch(...){}
		break;
	default:
		err.assign("Unknown input file type");
		break;
	}

	return err;
}
