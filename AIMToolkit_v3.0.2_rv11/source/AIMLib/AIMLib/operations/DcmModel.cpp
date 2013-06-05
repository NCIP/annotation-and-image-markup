/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "../model/AimHeaders.h"

#include "BaseModel.h"
#include "DcmModelInternal.h"
#include "DcmModel.h"

#include "../AIMUtil.h"
#include "../AIMCodes.h"

using namespace aim_lib;

const std::string DcmModel::_defaultUIDPrefix = "999.99.9"; // TODO - we need a real default UID prefix for AIM lib

DcmModel::DcmModel(const std::string& uidPrefix/* = _defaultUIDPrefix*/)
{
	_uidPrefix = uidPrefix;
}

DcmModel::~DcmModel(void)
{
}

void DcmModel::WriteAnnotationToFile(const aim_lib::Annotation& annotation, const std::string &fileName)
//void DcmModel::WriteAnnotationToFile(const aim_lib::Annotation& annotation, const aim_lib::DicomTagCollection &headerTagValues, const std::string &fileName)
{
	AnnotationPtrVector annotations;

	annotations.push_back(const_cast<Annotation*>(&annotation));

	this->WriteAnnotationsToFile(annotations, fileName);
	annotations.clear();
}

void DcmModel::WriteAnnotationsToFile(const aim_lib::AnnotationPtrVector& annotations, const std::string &fileName)
//void DcmModel::WriteAnnotationsToFile(const aim_lib::AnnotationPtrVector& annotations, const aim_lib::DicomTagCollection &headerTagValues, const std::string &fileName)
{
	DcmModelInternal dcmModelInternal(_uidPrefix);
	std::ofstream* pDcmtkXmlFile = NULL;
	DSRDocument* pDoc = NULL;

#ifdef _DEBUG
	std::ofstream dcmtkXmlFile;
	dcmtkXmlFile.open("dcmtk_output.xml", std::ios::out | std::ios::trunc);
	pDcmtkXmlFile = &dcmtkXmlFile;
#endif

	try
	{
		pDoc = dcmModelInternal.CreateDSRDocument(annotations, pDcmtkXmlFile);
		if (pDoc != NULL)
			dcmModelInternal.WriteDocToFile(*pDoc, fileName);
	}
	catch(std::exception ex)
	{
		std::string err = "Error writing to file:\t";
		err += ex.what();
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

void DcmModel::ReadAnnotationFromFile(Annotation** ppAnnotation, const std::string& fileName)
{
	DcmModelInternal dcmModelInternal(_uidPrefix);

	try
	{
		OFCondition ofCondition = dcmModelInternal.ReadDocFromFile(ppAnnotation, fileName);
		if (!ofCondition.good())
		{
			*ppAnnotation = NULL;
			std::string err = std::string("Failed to load SR from file <").append(fileName).append(">:");
			err += ofCondition.text();
			dcmModelInternal.printDebug(std::string(__FILE__).append(": ").append(err).c_str());
		}
	}
	catch(std::exception ex)
	{
		std::string err = std::string("Error loading SR from file<").append(fileName).append(">:");
		err += ex.what();
		dcmModelInternal.printDebug(err.c_str());
	}
}

int DcmModel::ReadAnnotationsFromFile(const std::string &fileName)
{
	DcmModelInternal dcmModelInternal(_uidPrefix);

	try
	{
		this->ClearAnnotations();
		//_currentAnnotation = 0;
		return dcmModelInternal.ReadDocFromFile(_annotations, fileName);
	}
	catch(std::exception ex)
	{
		std::string err = std::string("Error loading SR from file<").append(fileName).append(">:");
		err += ex.what();
		dcmModelInternal.printDebug(err.c_str());
	}

	return 0;
}

Annotation* DcmModel::GetNextAnnotation(Annotation** pAnnotation)
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
