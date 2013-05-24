/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "../AimHeaders.h"

#include "BaseModel.h"
#include "DcmModelInternal.h"
#include "DcmModel.h"

#include "../AIMUtil.h"

using namespace aim_lib;

const std::string DcmModel::_defaultUIDPrefix = "2.999.99.9"; // TODO - we need a real default UID prefix for AIM lib

DcmModel::DcmModel(const std::string& uidPrefix/* = _defaultUIDPrefix*/){
	_uidPrefix = uidPrefix;
}

DcmModel::~DcmModel(void){
}

// Caller is responsible for deallocating returned object
AnnotationCollection* DcmModel::ReadAnnotationCollectionFromFile(const std::string& fileName){
	DcmModelInternal dcmModelInternal(_uidPrefix);

	AnnotationCollection* pCollection = NULL;
	try
	{
		OFCondition ofCondition = dcmModelInternal.ReadDocFromFile(&pCollection, fileName);
		if (!ofCondition.good())
		{
			if (pCollection){
				delete pCollection;
				pCollection = NULL;
			}
			std::string err = std::string("Failed to load SR from file <").append(fileName).append(">:");
			err += ofCondition.text();
			dcmModelInternal.printDebug(std::string(__FILE__).append(": ").append(err).c_str());
		}
	}
	catch(const std::exception& ex)
	{
		std::string err = std::string("Error loading SR from file<").append(fileName).append(">:");
		err += ex.what();
		dcmModelInternal.printDebug(err.c_str());
	}
	return pCollection;
}

void DcmModel::WriteAnnotationCollectionToFile(const AnnotationCollection* pAnnotationCollection, const std::string& fileName){
	DcmModelInternal dcmModelInternal(_uidPrefix);
	std::ofstream* pDcmtkXmlFile = NULL;
	DSRDocument* pDoc = NULL;

	// Run through basic validator
	if (pAnnotationCollection)
		this->ValidateCollection(*pAnnotationCollection);

#ifdef _DEBUG
	std::ofstream dcmtkXmlFile;
	dcmtkXmlFile.open("dcmtk_output.xml", std::ios::out | std::ios::trunc);
	pDcmtkXmlFile = &dcmtkXmlFile;
#endif

	if (pAnnotationCollection)
	{
		try
		{
			pDoc = dcmModelInternal.CreateDSRDocument(*pAnnotationCollection, pDcmtkXmlFile);
			if (pDoc != NULL)
				dcmModelInternal.WriteDocToFile(*pDoc, fileName);
		}
		catch(const std::exception& ex)
		{
			std::string err = "Error writing to file:\t";
			err += ex.what();
			dcmModelInternal.printDebug(err.c_str());
		}
	}
	else
	{
		std::string err = "Error writing to file:\tGiven annotation collection does not exist";
		dcmModelInternal.printDebug(err.c_str());
	}

#ifdef _DEBUG
	if (dcmtkXmlFile.is_open())
		dcmtkXmlFile.close();
#endif

	if (pDoc != NULL)
	{
		delete pDoc;
		pDoc = NULL;
	}
}
