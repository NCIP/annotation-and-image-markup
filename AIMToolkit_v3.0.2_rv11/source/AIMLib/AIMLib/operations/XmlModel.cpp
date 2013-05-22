/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "../stdafx.h"
#include "../model/AimHeaders.h"

#include "BaseModel.h"
#include "XmlModel.h"

#include "XmlModelInternal.h"

//#include "../AIMUtil.h"


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

void XmlModel::WriteAnnotationToFile(const Annotation& annotation, const std::string& fileName)
{
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
	xmlModelInt.createXmlNode(xmlDoc, &const_cast<Annotation&>(annotation)); 

	xmlDoc.SaveToFile(fileName, true);

	// Release xerces
	XMLPlatformUtils::Terminate();
}

void XmlModel::WriteAnnotationsToFile(const AnnotationPtrVector& annotations, const std::string& fileName)
{
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
	xmlModelInt.createXmlNodes(xmlDoc, annotations); 

	xmlDoc.SaveToFile(fileName, true);

	// Release xerces
	XMLPlatformUtils::Terminate();
}

std::string::size_type XmlModel::WriteAnnotationToXmlString(Annotation* pAnnotation, std::string::traits_type::char_type* pBuf, std::string::size_type bufSize)
{
	// pAnnotation is a pointer to the AIM model.
	if (pAnnotation == NULL)
		return 0;

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
	xmlModelInt.createXmlNode(xmlDoc, pAnnotation); 

	std::string retXml = xmlDoc.SaveToString(true);

	// Release xerces
	XMLPlatformUtils::Terminate();

	if (retXml.length() < bufSize)
		return retXml.copy(pBuf, bufSize);
	else
		return retXml.length() + sizeof(std::string::traits_type::char_type);
}

std::string::size_type XmlModel::WriteAnnotationsToXmlString(const AnnotationPtrVector& annotations, std::string::traits_type::char_type* pBuf, std::string::size_type bufSize)
{
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
	xmlModelInt.createXmlNodes(xmlDoc, annotations); 

	std::string retXml = xmlDoc.SaveToString(true);

	// Release xerces
	XMLPlatformUtils::Terminate();

	if (retXml.length() < bufSize)
		return retXml.copy(pBuf, bufSize);
	else
		return retXml.length() + sizeof(std::string::traits_type::char_type);
}

Annotation::AnnotationKind XmlModel::ReadAnnotationFromFile(Annotation **ppAnnotation, const std::string &fileName)
{
	if (ppAnnotation == NULL)
		return Annotation::AK_Unknown;

	if (fileName.empty())
	{
		*ppAnnotation = NULL;
		return Annotation::AK_Unknown;
	}

	// Initialize xerces
	try {
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& toCatch) {
		std::cout << _T("Initialization Error [") << __LINE__ << _T("]:") << toCatch.getMessage() << std::endl;
		assert(false);
		return Annotation::AK_Unknown;
	}

	CAIMXML doc = CAIMXML::LoadFromFile(_T(fileName));

	Annotation::AnnotationKind retVal = Annotation::AK_Unknown;
	XmlModelInternal xmlModelInt;
	if (doc.ImageAnnotation.exists())
	{
		CImageAnnotation imgAnnotation = doc.ImageAnnotation.first();
		*ppAnnotation = xmlModelInt.readXmlNodeImageAnnotation(imgAnnotation);
		if (*ppAnnotation != NULL)
			retVal = Annotation::AK_ImageAnnotation;
	}
	else if (doc.AnnotationOfAnnotation.exists())
	{
		CAnnotationOfAnnotation annOfAnnotation = doc.AnnotationOfAnnotation.first();
		*ppAnnotation = xmlModelInt.readXmlNodeAnnotationOfAnnotation(annOfAnnotation);
		if (*ppAnnotation != NULL)
			retVal = Annotation::AK_AnnotationOfAnnotation;
	}
	else
	{
		*ppAnnotation = NULL;
	}

	// Release xerces
	XMLPlatformUtils::Terminate();

	return retVal;
}

Annotation::AnnotationKind XmlModel::ReadAnnotationFromXmlString(aim_lib::Annotation **ppAnnotation, const std::string &xmlIn)
{
	if (ppAnnotation == NULL)
		return Annotation::AK_Unknown;

	if (xmlIn.empty())
	{
		*ppAnnotation = NULL;
		return Annotation::AK_Unknown;
	}


	// Initialize xerces
	try {
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& toCatch) {
		std::cout << _T("Initialization Error [") << __LINE__ << _T("]:") << toCatch.getMessage() << std::endl;
		assert(false);
		return Annotation::AK_Unknown;
	}

	CAIMXML doc = CAIMXML::LoadFromString(_T(xmlIn));

	Annotation::AnnotationKind retVal = Annotation::AK_Unknown;
	XmlModelInternal xmlModelInt;
	if (doc.ImageAnnotation.exists())
	{
		CImageAnnotation imgAnnotation = doc.ImageAnnotation.first();
		*ppAnnotation = xmlModelInt.readXmlNodeImageAnnotation(imgAnnotation);
		if (*ppAnnotation != NULL)
			retVal = Annotation::AK_ImageAnnotation;
	}
	else if (doc.AnnotationOfAnnotation.exists())
	{
		CAnnotationOfAnnotation annOfAnnotation = doc.AnnotationOfAnnotation.first();
		*ppAnnotation = xmlModelInt.readXmlNodeAnnotationOfAnnotation(annOfAnnotation);
		if (*ppAnnotation != NULL)
			retVal = Annotation::AK_AnnotationOfAnnotation;
	}
	else
	{
		*ppAnnotation = NULL;
	}

	// Release xerces
	XMLPlatformUtils::Terminate();


	return Annotation::AK_Unknown;
}

int XmlModel::ReadAnnotationsFromFile(const std::string &fileName)
{
	if (_xmlFileName == fileName)
		return (int)_annotations.size();

	this->ClearAnnotations();
	//_currentAnnotation = 0;

	if (fileName.empty())
		return 0;

	// Initialize xerces
	try {
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& toCatch) {
		std::cout << _T("Initialization Error [") << __LINE__ << _T("]:") << toCatch.getMessage() << std::endl;
		assert(false);
		return 0; // annotations;
	}

	CAIMXML doc = CAIMXML::LoadFromFile(_T(fileName));

	XmlModelInternal xmlModelInt;
	if (doc.ImageAnnotation.exists())
	{
		for (AIMXML::Iterator<CImageAnnotation> iter = doc.ImageAnnotation.all(); iter; ++iter)
		{
			ImageAnnotation* pImgAnnotation = xmlModelInt.readXmlNodeImageAnnotation(iter);
			if (pImgAnnotation != NULL)
				_annotations.push_back(pImgAnnotation);
		}
	}
	if (doc.AnnotationOfAnnotation.exists())
	{
		for (AIMXML::Iterator<CAnnotationOfAnnotation> iter = doc.AnnotationOfAnnotation.all(); iter; ++iter)
		{
			AnnotationOfAnnotation* pAnnOfAnnotation = xmlModelInt.readXmlNodeAnnotationOfAnnotation(iter);
			if (pAnnOfAnnotation != NULL)
				_annotations.push_back(pAnnOfAnnotation);
		}
	}

	// Release xerces
	XMLPlatformUtils::Terminate();

	return (int)_annotations.size();
}

Annotation* XmlModel::GetNextAnnotation(aim_lib::Annotation** pAnnotation)
{
	assert(pAnnotation != NULL);

	if (_annotations.size() > 0)
	{
		*pAnnotation = _annotations[0];
		_annotations.erase(_annotations.begin());
	}
	else
	{
		*pAnnotation = NULL;
	}

	return *pAnnotation;
}
