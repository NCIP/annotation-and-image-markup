/*
  Classname: AIMConverter

  © 2008-2010 Northwestern University

  Authors:
  Vladimir Kleper
  Northwestern University
  Feinberg School of Medicine
  Department of Radiology
  Imaging Informatics Section
  Chicago, IL

The Academic Free License v. 2.1

This Academic Free License (the "License") applies to any original work of
authorship (the "Original Work") whose owner (the "Licensor") has placed the
following notice immediately following the copyright notice for the Original
Work:

Licensed under the Academic Free License version 2.1

1) Grant of Copyright License. Licensor hereby grants You a world-wide, royalty-
free, non-exclusive, perpetual, sublicenseable license to do the following:

a) to reproduce the Original Work in copies;

b) to prepare derivative works ("Derivative Works") based upon the Original Work;

c) to distribute copies of the Original Work and Derivative Works to the public;

d) to perform the Original Work publicly; and

e) to display the Original Work publicly.

2) Grant of Patent License. Licensor hereby grants You a world-wide, royalty-
free, non-exclusive, perpetual, sublicenseable license, under patent claims
owned or controlled by the Licensor that are embodied in the Original Work as
furnished by the Licensor, to make, use, sell and offer for sale the Original
Work and Derivative Works.

3) Grant of Source Code License. The term "Source Code" means the preferred form
of the Original Work for making modifications to it and all available
documentation describing how to modify the Original Work. Licensor hereby agrees
to provide a machine-readable copy of the Source Code of the Original Work along
with each copy of the Original Work that Licensor distributes. Licensor reserves
the right to satisfy this obligation by placing a machine-readable copy of the
Source Code in an information repository reasonably calculated to permit
inexpensive and convenient access by You for as long as Licensor continues to
distribute the Original Work, and by publishing the address of that information
repository in a notice immediately following the copyright notice that applies
to the Original Work.

4) Exclusions From License Grant. Neither the names of Licensor, nor the names
of any contributors to the Original Work, nor any of their trademarks or service
marks, may be used to endorse or promote products derived from this Original
Work without express prior written permission of the Licensor. Nothing in this
License shall be deemed to grant any rights to trademarks, copyrights, patents,
trade secrets or any other intellectual property of Licensor except as expressly
stated herein. No patent license is granted to make, use, sell or offer to sell
embodiments of any patent claims other than the licensed claims defined in
Section 2. No right is granted to the trademarks of Licensor even if such marks
are included in the Original Work. Nothing in this License shall be interpreted
to prohibit Licensor from licensing under different terms from this License any
Original Work that Licensor otherwise would have a right to license.

5) This section intentionally omitted.

6) Attribution Rights. You must retain, in the Source Code of any Derivative
Works that You create, all copyright, patent or trademark notices from the
Source Code of the Original Work, as well as any notices of licensing and any
descriptive text identified therein as an "Attribution Notice." You must cause
the Source Code for any Derivative Works that You create to carry a prominent
Attribution Notice reasonably calculated to inform recipients that You have
modified the Original Work.

7) Warranty of Provenance and Disclaimer of Warranty. Licensor warrants that the
copyright in and to the Original Work and the patent rights granted herein by
Licensor are owned by the Licensor or are sublicensed to You under the terms of
this License with the permission of the contributor(s) of those copyrights and
patent rights. Except as expressly stated in the immediately proceeding
sentence, the Original Work is provided under this License on an "AS IS" BASIS
and WITHOUT WARRANTY, either express or implied, including, without limitation,
the warranties of NON-INFRINGEMENT, MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE. THE ENTIRE RISK AS TO THE QUALITY OF THE ORIGINAL WORK IS WITH YOU.
This DISCLAIMER OF WARRANTY constitutes an essential part of this License. No
license to Original Work is granted hereunder except under this disclaimer.

8) Limitation of Liability. Under no circumstances and under no legal theory,
whether in tort (including negligence), contract, or otherwise, shall the
Licensor be liable to any person for any direct, indirect, special, incidental,
or consequential damages of any character arising as a result of this License or
the use of the Original Work including, without limitation, damages for loss of
goodwill, work stoppage, computer failure or malfunction, or any and all other
commercial damages or losses. This limitation of liability shall not apply to
liability for death or personal injury resulting from Licensor's negligence to
the extent applicable law prohibits such limitation. Some jurisdictions do not
allow the exclusion or limitation of incidental or consequential damages, so
this exclusion and limitation may not apply to You.

9) Acceptance and Termination. If You distribute copies of the Original Work or
a Derivative Work, You must make a reasonable effort under the circumstances to
obtain the express assent of recipients to the terms of this License. Nothing
else but this License (or another written agreement between Licensor and You)
grants You permission to create Derivative Works based upon the Original Work or
to exercise any of the rights granted in Section 1 herein, and any attempt to do
so except under the terms of this License (or another written agreement between
Licensor and You) is expressly prohibited by U.S. copyright law, the equivalent
laws of other countries, and by international treaty. Therefore, by exercising
any of the rights granted to You in Section 1 herein, You indicate Your
acceptance of this License and all of its terms and conditions.

10) Termination for Patent Action. This License shall terminate automatically
and You may no longer exercise any of the rights granted to You by this License
as of the date You commence an action, including a cross-claim or counterclaim,
against Licensor or any licensee alleging that the Original Work infringes a
patent. This termination provision shall not apply for an action alleging patent
infringement by combinations of the Original Work with other software or 
hardware.

11) Jurisdiction, Venue and Governing Law. Any action or suit relating to this
License may be brought only in the courts of a jurisdiction wherein the Licensor
resides or in which Licensor conducts its primary business, and under the laws
of that jurisdiction excluding its conflict-of-law provisions. The application
of the United Nations Convention on Contracts for the International Sale of
Goods is expressly excluded. Any use of the Original Work outside the scope of
this License or after its termination shall be subject to the requirements and
penalties of the U.S. Copyright Act, 17 U.S.C. § 101 et seq., the equivalent
laws of other countries, and international treaty. This section shall survive
the termination of this License.

12) Attorneys Fees. In any action to enforce the terms of this License or
seeking damages relating thereto, the prevailing party shall be entitled to
recover its costs and expenses, including, without limitation, reasonable
attorneys' fees and costs incurred in connection with such action, including any
appeal of such action. This section shall survive the termination of this
License.

13) Miscellaneous. This License represents the complete agreement concerning the
subject matter hereof. If any provision of this License is held to be
unenforceable, such provision shall be reformed only to the extent necessary to
make it enforceable.

14) Definition of "You" in This License. "You" throughout this License, whether
in upper or lower case, means an individual or a legal entity exercising rights
under, and complying with all of the terms of, this License. For legal entities,
"You" includes any entity that controls, is controlled by, or is under common
control with you. For purposes of this definition, "control" means (i) the
power, direct or indirect, to cause the direction or management of such entity,
whether by contract or otherwise, or (ii) ownership of fifty percent (50%) or
more of the outstanding shares, or (iii) beneficial ownership of such entity.

15) Right to Use. You may use the Original Work in all ways not otherwise
restricted or conditioned by this License or by law, and Licensor promises not
to interfere with or be responsible for such uses by You.

This license is Copyright (C) 2003-2004 Lawrence E. Rosen. All rights reserved.
Permission is hereby granted to copy and distribute this license without
modification. This license may not be modified without the express written
permission of its copyright owner.

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
