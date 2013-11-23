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
#include "XmlModel.h"

#include "XmlModelInternal.h"

#include <stdexcept>

// xerces include
#include "xercesc/util/PlatformUtils.hpp"
// Other include files, declarations, and non-Xerces-C++ initializations.
XERCES_CPP_NAMESPACE_USE 

#include <iostream>

using namespace aim_lib;
using namespace AIMXML;

XmlModel::XmlModel(void)
{
}

XmlModel::~XmlModel(void)
{
}

void XmlModel::WriteAnnotationCollectionToFile(const AnnotationCollection* pAnnotationCollection, const std::string& fileName)
{
	if (!pAnnotationCollection)
		throw std::invalid_argument("Annotation Collection cannot be uninitialized");

	// Run through basic validator
	if (pAnnotationCollection)
		this->ValidateCollection(*pAnnotationCollection);

	// Initialize xerces
	try {
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& toCatch) {
		std::cout << _T("Initialization Error [") << __LINE__ << _T("]:") << toCatch.getMessage() << std::endl;
		assert(false);
		throw;
	}

	try {
		CAIMXML xmlDoc = CAIMXML::CreateDocument();

		XmlModelInternal xmlModelInt;
		xmlModelInt.createXmlNode(xmlDoc, &const_cast<AnnotationCollection&>(*pAnnotationCollection)); 

		xmlDoc.SaveToFile(fileName, true);

		// Release xerces
		XMLPlatformUtils::Terminate();
	}
	catch (...)
	{
		// Release xerces
		XMLPlatformUtils::Terminate();
		throw;
	}
}

std::string::size_type XmlModel::WriteAnnotationCollectionToXmlString(const AnnotationCollection* pAnnotationCollection, std::string::traits_type::char_type* pBuf, std::string::size_type bufSize)
{
	// pAnnotationCollection is a pointer to the AIM model.
	if (!pAnnotationCollection)
		return 0;

	// Run through basic validator
	if (pAnnotationCollection)
		this->ValidateCollection(*pAnnotationCollection);

	// zero-out buffer
	memset(pBuf, 0, bufSize);

	// Initialize xerces
	try {
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& toCatch) {
		std::cout << _T("Initialization Error [") << __LINE__ << _T("]:") << toCatch.getMessage() << std::endl;
		assert(false);
		return -1;
	}

	try {
		CAIMXML xmlDoc = CAIMXML::CreateDocument();

		XmlModelInternal xmlModelInt;
		xmlModelInt.createXmlNode(xmlDoc, &const_cast<AnnotationCollection&>(*pAnnotationCollection));

		std::string retXml = xmlDoc.SaveToString(true);

		// Release xerces
		XMLPlatformUtils::Terminate();

		if (retXml.length() < bufSize)
			return retXml.copy(pBuf, bufSize);
		else
			return retXml.length() + sizeof(std::string::traits_type::char_type);
	}
	catch (...)
	{
		// Release xerces
		XMLPlatformUtils::Terminate();
		throw;
	}
}

AnnotationCollection* XmlModel::ReadAnnotationCollectionFromFile(const std::string& fileName)
{
	if (fileName.empty())
		throw std::invalid_argument("Annotation file name cannot be empty");

	// Initialize xerces
	try {
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& toCatch) {
		std::cout << _T("Initialization Error [") << __LINE__ << _T("]:") << toCatch.getMessage() << std::endl;
		assert(false);
		throw std::runtime_error("Internal error: failed to initalized required components");
	}

	try {
		CAIMXML doc = CAIMXML::LoadFromFile(_T(fileName));

		AnnotationCollection* pAnnotationCollection = NULL;
		XmlModelInternal xmlModelInt;
		if (doc.ImageAnnotationCollection.exists())
		{
			CImageAnnotationCollection imgAnnotationColl = doc.ImageAnnotationCollection.first();
			pAnnotationCollection = xmlModelInt.readXmlNodeImageAnnotationCollection(imgAnnotationColl);
		}
		else if (doc.AnnotationOfAnnotationCollection.exists())
		{
			CAnnotationOfAnnotationCollection annOfAnnotationColl = doc.AnnotationOfAnnotationCollection.first();
			pAnnotationCollection = xmlModelInt.readXmlNodeAnnotationOfAnnotationCollection(annOfAnnotationColl);
		}

		// Release xerces
		XMLPlatformUtils::Terminate();

		return pAnnotationCollection;
	}
	catch (...)
	{
		// Release xerces
		XMLPlatformUtils::Terminate();
		throw;
	}
}

AnnotationCollection* XmlModel::ReadAnnotationCollectionFromXmlString(const std::string& xmlIn)
{
	if (xmlIn.empty())
		throw std::invalid_argument("Annotation content cannot be empty");

	// Initialize xerces
	try {
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& toCatch) {
		std::cout << _T("Initialization Error [") << __LINE__ << _T("]:") << toCatch.getMessage() << std::endl;
		assert(false);
		throw std::runtime_error("Internal error: failed to initalized required components");
	}

	try {
		CAIMXML doc = CAIMXML::LoadFromString(_T(xmlIn));

		AnnotationCollection* pAnnotationCollection = NULL;
		XmlModelInternal xmlModelInt;
		if (doc.ImageAnnotationCollection.exists())
		{
			CImageAnnotationCollection imgAnnotationColl = doc.ImageAnnotationCollection.first();
			pAnnotationCollection = xmlModelInt.readXmlNodeImageAnnotationCollection(imgAnnotationColl);
		}
		else if (doc.AnnotationOfAnnotationCollection.exists())
		{
			CAnnotationOfAnnotationCollection annOfAnnotationColl = doc.AnnotationOfAnnotationCollection.first();
			pAnnotationCollection = xmlModelInt.readXmlNodeAnnotationOfAnnotationCollection(annOfAnnotationColl);
		}

		// Release xerces
		XMLPlatformUtils::Terminate();

		return pAnnotationCollection;
	}
	catch (...)
	{
		// Release xerces
		XMLPlatformUtils::Terminate();
		throw;
	}
}
