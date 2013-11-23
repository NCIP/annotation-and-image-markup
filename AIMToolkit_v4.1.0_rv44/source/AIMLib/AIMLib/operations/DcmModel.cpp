/*
Copyright (c) 2008-2013, Northwestern University
All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 
  Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
 
  Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
 
  Neither the name of the Northwestern University nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
