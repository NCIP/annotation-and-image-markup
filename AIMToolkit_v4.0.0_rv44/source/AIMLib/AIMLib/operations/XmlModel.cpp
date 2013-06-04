/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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

	CAIMXML xmlDoc = CAIMXML::CreateDocument();

	XmlModelInternal xmlModelInt;
	xmlModelInt.createXmlNode(xmlDoc, &const_cast<AnnotationCollection&>(*pAnnotationCollection)); 

	xmlDoc.SaveToFile(fileName, true);

	// Release xerces
	XMLPlatformUtils::Terminate();
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
