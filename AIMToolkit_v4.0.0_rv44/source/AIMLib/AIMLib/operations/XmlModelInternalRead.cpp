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

#include "../AIMUtil.h"

#include "XmlModelInternal.h"
#include "../statement/StatementFactory.h"

#include "../../AltovaXML/XercesString.h"

#include <algorithm>
#include <limits.h>

#include "../memdebug.h"

using namespace aim_lib;
using namespace AIMXML;

static const std::string _emptyStr = std::string("");
static const iso_21090::II _emptyIi = iso_21090::II();
static const iso_21090::CD _emptyCd = iso_21090::CD();
static const iso_21090::CDVector _emptyCdVector = iso_21090::CDVector();
static const std::vector<std::string> _emptyStrVector = std::vector<std::string>();

// XML reading macros
#define GET_ST(node) node.exists() ? this->readXmlNode(node.first()) : _emptyStr
#define GET_STVECTOR(node) node.exists() ? this->readXmlNode(node.all()) : _emptyStrVector
#define GET_II(node) node.exists() ? this->readXmlNode(node.first()) : _emptyIi
#define GET_II_PTR(node, ii) node.exists() ? &(ii = this->readXmlNode(node.first())) : NULL
#define GET_CD(node) node.exists() ? this->readXmlNode(node.first()) : _emptyCd
#define GET_CD_PTR(node, cd) node.exists() ? &(cd = this->readXmlNode(node.first())) : NULL
#define GET_CDVECTOR(node) node.exists() ? this->readXmlNode(node.all()) : _emptyCdVector
#define GET_BL(node) node.exists() ? this->readXmlNode(node.first()) : false
#define GET_BL_PTR(node, flag) node.exists() ? &(flag = this->readXmlNode(node.first())) : NULL
#define GET_INT(node) node.exists() ? this->readXmlNode(node.first()) : -1
#define GET_INT_PTR(node, num) node.exists() ? &(num = this->readXmlNode(node.first())) : NULL
#define GET_REAL(node) node.exists() ? this->readXmlNode(node.first()) : 0.0
#define GET_REAL_PTR(node, val) node.exists() ? &(val = this->readXmlNode(node.first())) : NULL
#define GET_DATETIME(node) node.exists() ? this->xmlNodeToDateTime(node.first()) : DateTime()
#define GET_DATE(node) node.exists() ? this->xmlNodeToDate(node.first()) : Date()
#define GET_TIME(node) node.exists() ? this->xmlNodeToTime(node.first()) : Time()

// Helpers
const iso_21090::II XmlModelInternal::readXmlNode(AIMXML::iso::CII xmlIi)
{
	return iso_21090::II(xmlIi.root);
}

const iso_21090::CD XmlModelInternal::readXmlNode(AIMXML::iso::CCD xmlCd)
{
	std::string codeValue = xmlCd.code.exists() ? xmlCd.code : _emptyStr;
	std::string codeMeaning = xmlCd.displayName.exists() ? (xmlCd.displayName.first().value2.exists() ? xmlCd.displayName.first().value2 : _emptyStr) : _emptyStr;
	std::string codingSchemeDesignator = xmlCd.codeSystemName.exists() ? xmlCd.codeSystemName : _emptyStr;
	std::string codingSchemeVersion = xmlCd.codeSystemVersion.exists() ? xmlCd.codeSystemVersion : _emptyStr;

	if (codingSchemeVersion.empty())
		return iso_21090::CD(codeValue, codeMeaning, codingSchemeDesignator);
	else
		return iso_21090::CD(codeValue, codeMeaning, codingSchemeDesignator, codingSchemeVersion);
}

const iso_21090::CDVector XmlModelInternal::readXmlNode(AIMXML::Iterator<AIMXML::iso::CCD> xmlCdIter)
{
	iso_21090::CDVector cdVector;

	while(xmlCdIter)
	{
		iso_21090::CD cd = this->readXmlNode(*xmlCdIter);
		cdVector.push_back(cd);
		++xmlCdIter;
	}

	return cdVector;
}

const std::string XmlModelInternal::readXmlNode(AIMXML::iso::CST xmlSt)
{
	return xmlSt.value2.exists() ? xmlSt.value2 : _emptyStr;
}

const std::vector<std::string> XmlModelInternal::readXmlNode(AIMXML::Iterator<AIMXML::iso::CST> xmlStIter)
{
	std::vector<std::string> strVector;

	while(xmlStIter)
	{
		std::string str = this->readXmlNode(*xmlStIter);
		strVector.push_back(str);
		++xmlStIter;
	}

	return strVector;
}

const bool XmlModelInternal::readXmlNode(AIMXML::iso::CBL xmlBl)
{
	assert(xmlBl.value2.exists()); // it really should exist
	return xmlBl.value2.exists() ? xmlBl.value2 : false;
}

const int XmlModelInternal::readXmlNode(AIMXML::iso::CINT xmlInt)
{
	assert(xmlInt.value2.exists()); // it really should exist
	return xmlInt.value2.exists() ? xmlInt.value2 : 0;
}

const double XmlModelInternal::readXmlNode(AIMXML::iso::CREAL xmlReal)
{
	assert(xmlReal.value2.exists()); // it really should exist
	return xmlReal.value2.exists() ? xmlReal.value2 : 0.0;
}

const DateTime XmlModelInternal::xmlNodeToDateTime(AIMXML::iso::CTS xmlTs)
{
	return AIMUtil::DateTimeConvert(AIMUtil::DateTimeConvert(xmlTs.value2.exists() ? xmlTs.value2 : _emptyStr));
}

const Date XmlModelInternal::xmlNodeToDate(AIMXML::iso::CTS xmlTs)
{
	return AIMUtil::DateConvert(AIMUtil::DateConvert(xmlTs.value2.exists() ? xmlTs.value2 : _emptyStr));
}

const Time XmlModelInternal::xmlNodeToTime(AIMXML::iso::CTS xmlTs)
{
	return AIMUtil::TimeConvert(AIMUtil::TimeConvert(xmlTs.value2.exists() ? xmlTs.value2 : _emptyStr));
}

ImageAnnotationCollection* XmlModelInternal::readXmlNodeImageAnnotationCollection(AIMXML::CImageAnnotationCollection& xmlImgAnnotationCollection)
{
	ImageAnnotationCollection* pImgAnnColl = new ImageAnnotationCollection();

	try
	{
		// AnnotationCollection
		this->readXmlNode(*pImgAnnColl, xmlImgAnnotationCollection);

		// Person
		if (xmlImgAnnotationCollection.person.exists())
		{
			CPerson xmlPatient = xmlImgAnnotationCollection.person.first();
			Person patient = this->readXmlNode(xmlPatient);
			pImgAnnColl->SetPerson(&patient);
		}

		// Image Annotations
		if (xmlImgAnnotationCollection.imageAnnotations.exists())
		{
			CimageAnnotationsType xmlImgAnnotations = xmlImgAnnotationCollection.imageAnnotations.first();
			ImageAnnotationVector imgAnnotations = this->readXmlNode(xmlImgAnnotations);
			pImgAnnColl->SetImageAnnotations(imgAnnotations);
		}
	}
	//catch (const std::exception& ex)
	catch (...)
	{
		delete pImgAnnColl;
		pImgAnnColl = NULL;
		throw;
	}

	return pImgAnnColl;
}

AnnotationOfAnnotationCollection* XmlModelInternal::readXmlNodeAnnotationOfAnnotationCollection(AIMXML::CAnnotationOfAnnotationCollection& xmlAnnOfAnnotationCollection)
{
	AnnotationOfAnnotationCollection* pAnnOfAnnColl = new AnnotationOfAnnotationCollection();

	try
	{
		// AnnotationCollection
		this->readXmlNode(*pAnnOfAnnColl, xmlAnnOfAnnotationCollection);

		// Annotation of Annotations
		if (xmlAnnOfAnnotationCollection.annotationOfAnnotations.exists())
		{
			CannotationOfAnnotationsType xmlAnnOfAnnotations = xmlAnnOfAnnotationCollection.annotationOfAnnotations.first();
			AnnotationOfAnnotationVector annOfAnnotations = this->readXmlNode(xmlAnnOfAnnotations);
			pAnnOfAnnColl->SetAnnotationOfAnnotations(annOfAnnotations);
		}
	}
	//catch (const std::exception& ex)
	catch (...)
	{
		delete pAnnOfAnnColl;
		pAnnOfAnnColl = NULL;
		throw;
	}

	return pAnnOfAnnColl;
}

void XmlModelInternal::readXmlNode(AnnotationCollection& annotationCollection, AIMXML::CAnnotationCollection& xmlAnnColl)
{
	// AIM Version
	//annotationCollection.SetAimVersion(xmlAnnColl.aimVersion.exists() ? xmlAnnColl.aimVersion : _emptyStr);
	assert(AimEnum::GetAimVersionString(annotationCollection.GetAimVersion()) == (xmlAnnColl.aimVersion.exists() ? xmlAnnColl.aimVersion : _emptyStr));
	// UID
	annotationCollection.SetUniqueIdentifier(GET_II(xmlAnnColl.uniqueIdentifier));
	// Name
	annotationCollection.SetDescription(GET_ST(xmlAnnColl.description));
	// Date Time
	annotationCollection.SetDateTime(GET_DATETIME(xmlAnnColl.dateTime));

	// User
	if (xmlAnnColl.user.exists())
	{
		CUser xmlUser = xmlAnnColl.user.first();
		User user = this->readXmlNode(xmlUser);
		annotationCollection.SetUser(&user);
	}

	// Equipment
	if (xmlAnnColl.equipment.exists())
	{
		CEquipment xmlEquipment = xmlAnnColl.equipment.first();
		Equipment equipment = this->readXmlNode(xmlEquipment);
		annotationCollection.SetEquipment(&equipment);
	}
}

const ImageAnnotationVector XmlModelInternal::readXmlNode(AIMXML::CimageAnnotationsType& xmlImageAnnotations)
{
	ImageAnnotationVector imgAnnotations;

	if (xmlImageAnnotations.ImageAnnotation.exists())
	{
		for (AIMXML::Iterator<CImageAnnotation> iter = xmlImageAnnotations.ImageAnnotation.all(); iter; ++iter)
		{
			ImageAnnotation imgAnnotation;

			// Read Annotation Entity data
			this->readXmlNode(imgAnnotation, *iter);

			// Segmentation Entities
			if (iter->segmentationEntityCollection.exists())
			{
				CsegmentationEntityCollectionType xmlSegmentationEntities = iter->segmentationEntityCollection.first();
				SegmentationEntityPtrVector segmentationEntities = this->readXmlNode(xmlSegmentationEntities);
				imgAnnotation.SetSegmentationEntityCollection(segmentationEntities);
				while(segmentationEntities.size() > 0)
				{
					delete segmentationEntities[segmentationEntities.size() - 1];
					segmentationEntities.pop_back();
				}
			}
			// Markup Entities
			if (iter->markupEntityCollection.exists())
			{
				CmarkupEntityCollectionType xmlMarkupEntities = iter->markupEntityCollection.first();
				MarkupEntityPtrVector markupEntities = this->readXmlNode(xmlMarkupEntities);
				imgAnnotation.SetMarkupEntityCollection(markupEntities);
				while(markupEntities.size() > 0)
				{
					delete markupEntities[markupEntities.size() - 1];
					markupEntities.pop_back();
				}
			}
			// Image Reference Entities
			if (iter->imageReferenceEntityCollection.exists())
			{
				CimageReferenceEntityCollectionType xmlImageRefEntities = iter->imageReferenceEntityCollection.first();
				ImageReferenceEntityPtrVector imageRefEntities = this->readXmlNode(xmlImageRefEntities);
				imgAnnotation.SetImageReferenceEntityCollection(imageRefEntities);
				while(imageRefEntities.size() > 0)
				{
					delete imageRefEntities[imageRefEntities.size() - 1];
					imageRefEntities.pop_back();
				}
			}
			// Image Annotation Statements
			if (iter->imageAnnotationStatementCollection.exists())
			{
				CimageAnnotationStatementCollectionType xmlImgAnnStatements = iter->imageAnnotationStatementCollection.first();
				ImageAnnotationStatementPtrVector imgAnnStatements = this->readXmlNode(xmlImgAnnStatements);
				imgAnnotation.SetImageAnnotationStatementCollection(imgAnnStatements);
				while(imgAnnStatements.size() > 0)
				{
					delete imgAnnStatements[imgAnnStatements.size() - 1];
					imgAnnStatements.pop_back();
				}
			}

			imgAnnotations.push_back(imgAnnotation);
		}
	}
	
	return imgAnnotations;
}

const AnnotationOfAnnotationVector XmlModelInternal::readXmlNode(AIMXML::CannotationOfAnnotationsType& xmlAnnOfAnnotations)
{
	AnnotationOfAnnotationVector annOfAnnotations;

	if (xmlAnnOfAnnotations.AnnotationOfAnnotation.exists())
	{
		for (AIMXML::Iterator<CAnnotationOfAnnotation> iter = xmlAnnOfAnnotations.AnnotationOfAnnotation.all(); iter; ++iter)
		{
			AnnotationOfAnnotation annOfAnnotation;

			// Read Annotation Entity data
			this->readXmlNode(annOfAnnotation, *iter);

			// Adjudication Obseravation
			if (iter->adjudicationObservation.exists())
			{
				CAdjudicationObservation xmlAdjudicationObs = iter->adjudicationObservation.first();
				AdjudicationObservation adjudicationObs = this->readXmlNode(xmlAdjudicationObs);
				annOfAnnotation.SetAdjudicationObservation(&adjudicationObs);
			}
			// Annotation of Annotation Statements
			if (iter->annotationOfAnnotationStatementCollection.exists())
			{
				CannotationOfAnnotationStatementCollectionType xmlAnnOfAnnStatements = iter->annotationOfAnnotationStatementCollection.first();
				AnnotationOfAnnotationStatementPtrVector annOfAnnStatements = this->readXmlNode(xmlAnnOfAnnStatements);
				annOfAnnotation.SetAnnotationOfAnnotationStatementCollection(annOfAnnStatements);
				while(annOfAnnStatements.size() > 0)
				{
					delete annOfAnnStatements[annOfAnnStatements.size() - 1];
					annOfAnnStatements.pop_back();
				}
			}

			annOfAnnotations.push_back(annOfAnnotation);
		}
	}

	return annOfAnnotations;
}

void XmlModelInternal::readXmlNode(AnnotationEntity& annotationEntity, AIMXML::CAnnotationEntity& xmlAnnEntity)
{
	// PORTABILITY NOTE: Linux wants to have const references when passing arguments, but we don't get that from Altova code.
	// Also, Linux cannot pass temp variables as const references to methods
	// That's why we need to have two intermediate variables for each set method

	iso_21090::II uid;

	annotationEntity.SetUniqueIdentifier(GET_II(xmlAnnEntity.uniqueIdentifier));
	annotationEntity.SetTypeCode(GET_CDVECTOR(xmlAnnEntity.typeCode));
	annotationEntity.SetDateTime(GET_DATETIME(xmlAnnEntity.dateTime));
	annotationEntity.SetName(GET_ST(xmlAnnEntity.name));
	annotationEntity.SetComment(GET_ST(xmlAnnEntity.comment));
	annotationEntity.SetPrecedentReferencedAnnotationUid(GET_II_PTR(xmlAnnEntity.precedentReferencedAnnotationUid, uid));
	annotationEntity.SetTemplateUid(GET_II_PTR(xmlAnnEntity.templateUid, uid));

	// Imaging Physical Entities
	if (xmlAnnEntity.imagingPhysicalEntityCollection.exists())
	{
		CimagingPhysicalEntityCollectionType xmlImgPhysEntityCollection = xmlAnnEntity.imagingPhysicalEntityCollection.first();
		ImagingPhysicalEntityVector imgPhysEnities = this->readXmlNode(xmlImgPhysEntityCollection);
		annotationEntity.SetImagingPhysicalEntityCollection(imgPhysEnities);
	}

	// Imaging Observation Entities
	if (xmlAnnEntity.imagingObservationEntityCollection.exists())
	{
		CimagingObservationEntityCollectionType xmlImgObsChars = xmlAnnEntity.imagingObservationEntityCollection.first();
		ImagingObservationEntityVector imgObsChars = this->readXmlNode(xmlImgObsChars);
		annotationEntity.SetImagingObservationEntityCollection(imgObsChars);
	}
	// Inference Entities
	if (xmlAnnEntity.inferenceEntityCollection.exists())
	{
		CinferenceEntityCollectionType xmlInferenceEntities = xmlAnnEntity.inferenceEntityCollection.first();
		InferenceEntityVector inferenceEntities = this->readXmlNode(xmlInferenceEntities);
		annotationEntity.SetInferenceEntityCollection(inferenceEntities);
	}
	// Annotation Role Entities
	if (xmlAnnEntity.annotationRoleEntityCollection.exists())
	{
		CannotationRoleEntityCollectionType xmlAnnRoleEntities = xmlAnnEntity.annotationRoleEntityCollection.first();
		AnnotationRoleEntityVector annotationRoleEntities = this->readXmlNode(xmlAnnRoleEntities);
		annotationEntity.SetAnnotationRoleEntityCollection(annotationRoleEntities);
	}
	// Calcualtion Entities
	if (xmlAnnEntity.calculationEntityCollection.exists())
	{
		CcalculationEntityCollectionType xmlCalculationEntities = xmlAnnEntity.calculationEntityCollection.first();
		CalculationEntityVector calculatuionEntities = this->readXmlNode(xmlCalculationEntities);
		annotationEntity.SetCalculationEntityCollection(calculatuionEntities);
	}
	// Lesion Observation Entities
	if (xmlAnnEntity.lesionObservationEntityCollection.exists())
	{
		ClesionObservationEntityCollectionType xmlLesionObsEntities = xmlAnnEntity.lesionObservationEntityCollection.first();
		LesionObservationEntityPtrVector lesionObsEntities = this->readXmlNode(xmlLesionObsEntities);
		annotationEntity.SetLesionOservationEntityCollection(lesionObsEntities);
		while(lesionObsEntities.size() > 0)
		{
			delete lesionObsEntities[lesionObsEntities.size() - 1];
			lesionObsEntities.pop_back();
		}
	}
	// Task Context Entities
	if (xmlAnnEntity.taskContextEntityCollection.exists())
	{
		CtaskContextEntityCollectionType xmlTaskContextEntities = xmlAnnEntity.taskContextEntityCollection.first();
		TaskContextEntityVector taskContextEntities = this->readXmlNode(xmlTaskContextEntities);
		annotationEntity.SetTaskContextEntityCollection(taskContextEntities);
	}
	// Audit Trail
	if (xmlAnnEntity.auditTrailCollection.exists())
	{
		CauditTrailCollectionType xmlAuditTrails = xmlAnnEntity.auditTrailCollection.first();
		AuditTrailVector auditTrails = this->readXmlNode(xmlAuditTrails);
		annotationEntity.SetAuditTrailCollection(auditTrails);
	}
}

const ImagingPhysicalEntityVector XmlModelInternal::readXmlNode(AIMXML::CimagingPhysicalEntityCollectionType& xmlImgPhysEntities)
{
	ImagingPhysicalEntityVector imgPhysEntities;

	bool flag;
	double dVal;
	iso_21090::CD code;
	iso_21090::CDVector CDVector;

	if (xmlImgPhysEntities.ImagingPhysicalEntity.exists())
	{
		for(AIMXML::Iterator<CImagingPhysicalEntity> iter = xmlImgPhysEntities.ImagingPhysicalEntity.all(); iter; ++iter)
		{
			ImagingPhysicalEntity imgPhysEntity;

			imgPhysEntity.SetUniqueIdentifier(GET_II(iter->uniqueIdentifier));
			imgPhysEntity.SetTypeCode(GET_CDVECTOR(iter->typeCode));
			imgPhysEntity.SetQuestionTypeCode(GET_CDVECTOR(iter->questionTypeCode));
			imgPhysEntity.SetIsPresent(GET_BL_PTR(iter->isPresent, flag));
			imgPhysEntity.SetAnnotatorConfidence(GET_REAL_PTR(iter->annotatorConfidence, dVal));
			imgPhysEntity.SetLabel(GET_ST(iter->label));
			imgPhysEntity.SetQuestionIndex(GET_INT(iter->questionIndex));
			imgPhysEntity.SetComment(GET_ST(iter->comment));

			if (iter->imagingPhysicalEntityCharacteristicCollection.exists())
			{
				CimagingPhysicalEntityCharacteristicCollectionType xmlImgPhysChars = iter->imagingPhysicalEntityCharacteristicCollection.first();
				ImagingPhysicalEntityCharacteristicVector imgPhysEntityChars = this->readXmlNode(xmlImgPhysChars);
				imgPhysEntity.SetImagingPhysicalEntityCharacteristicCollection(imgPhysEntityChars);
			}

			if (iter->imagingObservationCharacteristicCollection.exists())
			{
				CimagingObservationCharacteristicCollectionType2 xmlImgObsChars = iter->imagingObservationCharacteristicCollection.first();
				ImagingObservationCharacteristicVector imgObsChars = this->readXmlNode(xmlImgObsChars);
				imgPhysEntity.SetImagingObservationCharacteristicCollection(imgObsChars);
			}

			imgPhysEntities.push_back(imgPhysEntity);
		}
	}

	return imgPhysEntities;
}

const ImagingPhysicalEntityCharacteristicVector XmlModelInternal::readXmlNode(AIMXML::CimagingPhysicalEntityCharacteristicCollectionType& xmlImgPhysEntityChars)
{
	ImagingPhysicalEntityCharacteristicVector imgPhysEntChars;

	double dVal;

	if (xmlImgPhysEntityChars.ImagingPhysicalEntityCharacteristic.exists())
	{
		for(AIMXML::Iterator<CImagingPhysicalEntityCharacteristic> iter = xmlImgPhysEntityChars.ImagingPhysicalEntityCharacteristic.all(); iter; ++iter)
		{
			ImagingPhysicalEntityCharacteristic imgPhysEntChar;

			imgPhysEntChar.SetTypeCode(GET_CDVECTOR(iter->typeCode));
			imgPhysEntChar.SetQuestionTypeCode(GET_CDVECTOR(iter->questionTypeCode));
			imgPhysEntChar.SetAnnotatorConfidence(GET_REAL_PTR(iter->annotatorConfidence, dVal));
			imgPhysEntChar.SetLabel(GET_ST(iter->label));
			imgPhysEntChar.SetQuestionIndex(GET_INT(iter->questionIndex));
			imgPhysEntChar.SetComment(GET_ST(iter->comment));

			if (iter->characteristicQuantificationCollection.exists())
			{
				CcharacteristicQuantificationCollectionType2 xmlCharQuantifictions = iter->characteristicQuantificationCollection.first();
				CharacteristicQuantificationPtrVector charQuantifiactions = this->readXmlNode(xmlCharQuantifictions);
				imgPhysEntChar.SetCharacteristicQuantificationCollection(charQuantifiactions);
				while(charQuantifiactions.size() > 0)
				{
					delete charQuantifiactions[charQuantifiactions.size() - 1];
					charQuantifiactions.pop_back();
				}
			}

			imgPhysEntChars.push_back(imgPhysEntChar);
		}
	}

	return imgPhysEntChars;
}

const ImagingObservationEntityVector XmlModelInternal::readXmlNode(AIMXML::CimagingObservationEntityCollectionType& xmlImagingObsEntities)
{
	ImagingObservationEntityVector imgObsEntities;

	bool flag;
	double dVal;
	iso_21090::CD code;
	iso_21090::CDVector CDVector;

	if (xmlImagingObsEntities.ImagingObservationEntity.exists())
	{
		for(AIMXML::Iterator<CImagingObservationEntity> iter = xmlImagingObsEntities.ImagingObservationEntity.all(); iter; ++iter)
		{
			ImagingObservationEntity imgObsEntity;

			imgObsEntity.SetUniqueIdentifier(GET_II(iter->uniqueIdentifier));
			imgObsEntity.SetTypeCode(GET_CDVECTOR(iter->typeCode));
			imgObsEntity.SetQuestionTypeCode(GET_CDVECTOR(iter->questionTypeCode));
			imgObsEntity.SetIsPresent(GET_BL_PTR(iter->isPresent, flag));
			imgObsEntity.SetAnnotatorConfidence(GET_REAL_PTR(iter->annotatorConfidence, dVal));
			imgObsEntity.SetLabel(GET_ST(iter->label));
			imgObsEntity.SetQuestionIndex(GET_INT(iter->questionIndex));
			imgObsEntity.SetComment(GET_ST(iter->comment));

			if (iter->imagingObservationCharacteristicCollection.exists())
			{
				CimagingObservationCharacteristicCollectionType xmlImgObsChars = iter->imagingObservationCharacteristicCollection.first();
				ImagingObservationCharacteristicVector imgObsChars = this->readXmlNode(xmlImgObsChars);
				imgObsEntity.SetImagingObservationCharacteristicCollection(imgObsChars);
			}

			imgObsEntities.push_back(imgObsEntity);
		}
	}

	return imgObsEntities;
}

const ImagingObservationCharacteristicVector XmlModelInternal::readXmlNode(AIMXML::CimagingObservationCharacteristicCollectionType& xmlImagingObsCharacteristics)
{
	ImagingObservationCharacteristicVector imgObsChars;

	if (xmlImagingObsCharacteristics.ImagingObservationCharacteristic.exists())
	{
		for(AIMXML::Iterator<CImagingObservationCharacteristic> iter = xmlImagingObsCharacteristics.ImagingObservationCharacteristic.all(); iter; ++iter)
		{
			ImagingObservationCharacteristic imgObsChar = this->readXmlNode(*iter);
			imgObsChars.push_back(imgObsChar);
		}
	}

	return imgObsChars;
}

const ImagingObservationCharacteristicVector XmlModelInternal::readXmlNode(AIMXML::CimagingObservationCharacteristicCollectionType2& xmlImagingObsCharacteristics)
{
	ImagingObservationCharacteristicVector imgObsChars;

	if (xmlImagingObsCharacteristics.ImagingObservationCharacteristic.exists())
	{
		for(AIMXML::Iterator<CImagingObservationCharacteristic> iter = xmlImagingObsCharacteristics.ImagingObservationCharacteristic.all(); iter; ++iter)
		{
			ImagingObservationCharacteristic imgObsChar = this->readXmlNode(*iter);
			imgObsChars.push_back(imgObsChar);
		}
	}

	return imgObsChars;
}

const ImagingObservationCharacteristic XmlModelInternal::readXmlNode(AIMXML::CImagingObservationCharacteristic& xmlImgObsChar)
{
	ImagingObservationCharacteristic imgObsChar;

	double dVal;

	imgObsChar.SetTypeCode(GET_CDVECTOR(xmlImgObsChar.typeCode));
	imgObsChar.SetQuestionTypeCode(GET_CDVECTOR(xmlImgObsChar.questionTypeCode));
	imgObsChar.SetAnnotatorConfidence(GET_REAL_PTR(xmlImgObsChar.annotatorConfidence, dVal));
	imgObsChar.SetLabel(GET_ST(xmlImgObsChar.label));
	imgObsChar.SetQuestionIndex(GET_INT(xmlImgObsChar.questionIndex));
	imgObsChar.SetComment(GET_ST(xmlImgObsChar.comment));

	if (xmlImgObsChar.characteristicQuantificationCollection.exists())
	{
		CcharacteristicQuantificationCollectionType xmlCharQuantifictions = xmlImgObsChar.characteristicQuantificationCollection.first();
		CharacteristicQuantificationPtrVector charQuantifiactions = this->readXmlNode(xmlCharQuantifictions);
		imgObsChar.SetCharacteristicQuantificationCollection(charQuantifiactions);
		while(charQuantifiactions.size() > 0)
		{
			delete charQuantifiactions[charQuantifiactions.size() - 1];
			charQuantifiactions.pop_back();
		}
	}

	return imgObsChar;
}


const CharacteristicQuantificationPtrVector XmlModelInternal::readXmlNode(AIMXML::CcharacteristicQuantificationCollectionType& xmlCharQuantifications)
{
	CharacteristicQuantificationPtrVector charQuantifications;

	if (xmlCharQuantifications.CharacteristicQuantification.exists())
	{
		for(AIMXML::Iterator<CCharacteristicQuantification> iter = xmlCharQuantifications.CharacteristicQuantification.all(); iter; ++iter)
		{
			CharacteristicQuantification* pCharQuantification = this->readXmlNode(*iter);
			if (pCharQuantification)
				charQuantifications.push_back(pCharQuantification);
		}
	}

	return charQuantifications;
}

const CharacteristicQuantificationPtrVector XmlModelInternal::readXmlNode(AIMXML::CcharacteristicQuantificationCollectionType2& xmlCharQuantifications)
{
	CharacteristicQuantificationPtrVector charQuantifications;

	if (xmlCharQuantifications.CharacteristicQuantification.exists())
	{
		for(AIMXML::Iterator<CCharacteristicQuantification> iter = xmlCharQuantifications.CharacteristicQuantification.all(); iter; ++iter)
		{
			CharacteristicQuantification* pCharQuantification = this->readXmlNode(*iter);
			if (pCharQuantification)
				charQuantifications.push_back(pCharQuantification);
		}
	}

	return charQuantifications;
}

CharacteristicQuantification* XmlModelInternal::readXmlNode(AIMXML::CCharacteristicQuantification& xmlCharQuantification)
{
	CharacteristicQuantification* pCharQuantification = NULL;
	std::string quantificationType = this->GetSubClassType(xmlCharQuantification.GetNode());
	if(C_QUANTIFICATION_NUMERICAL_NAME == quantificationType)
	{
		CNumerical xmlNumerical = xmlCharQuantification.GetNode();
		Numerical numerical;

		if (xmlNumerical.value2.exists())
			numerical.SetValue(GET_REAL(xmlNumerical.value2));
		numerical.SetUcumString(GET_ST(xmlNumerical.ucumString));
		if (xmlNumerical.operator2.exists())
			numerical.SetOperator(AimEnum::StringToComparisonOperatorType(xmlNumerical.operator2));

		pCharQuantification = numerical.Clone();
	}
	else if (C_QUANTIFICATION_QUANTILE_NAME == quantificationType)
	{
		CQuantile xmlQuantile = xmlCharQuantification.GetNode();
		Quantile quantile;

		quantile.SetBins(GET_INT(xmlQuantile.bins));
		quantile.SetSelectedBin(GET_INT(xmlQuantile.selectedBin));
		quantile.SetMinValue(GET_REAL(xmlQuantile.minValue));
		quantile.SetMaxValue(GET_REAL(xmlQuantile.maxValue));

		pCharQuantification = quantile.Clone();
	}
	else if (C_QUANTIFICATION_NON_QUANTIFIABLE_NAME == quantificationType)
	{
		CNonQuantifiable xmlNonQuantifiable = xmlCharQuantification.GetNode();
		NonQuantifiable nonQuantifiable;

		nonQuantifiable.SetTypeCode(GET_CD(xmlNonQuantifiable.typeCode));

		pCharQuantification = nonQuantifiable.Clone();
	}
	else if (C_QUANTIFICATION_SCALE_NAME == quantificationType)
	{
		CScale xmlScale = xmlCharQuantification.GetNode();
		Scale scale;

		scale.SetValue(GET_ST(xmlScale.value2));
		scale.SetScaleType(Scale::StringToScaleType(xmlScale.type));

		pCharQuantification = scale.Clone();
	}
	else if (C_QUANTIFICATION_INTERVAL_NAME == quantificationType)
	{
		CInterval xmlInterval = xmlCharQuantification.GetNode();
		Interval interval;

		interval.SetMinValue(GET_REAL(xmlInterval.minValue));
		interval.SetMaxValue(GET_REAL(xmlInterval.maxValue));
		if (xmlInterval.minOperator.exists())
			interval.SetMinOperator(AimEnum::StringToComparisonOperatorType(xmlInterval.minOperator));
		if (xmlInterval.maxOperator.exists())
			interval.SetMaxOperator(AimEnum::StringToComparisonOperatorType(xmlInterval.maxOperator));
		interval.SetUcumString(GET_ST(xmlInterval.ucumString));

		pCharQuantification = interval.Clone();
	}
	else
		assert(false);

	if (pCharQuantification)
	{
		double dVal;

		pCharQuantification->SetAnnotatorConfidence(GET_REAL_PTR(xmlCharQuantification.annotatorConfidence, dVal));
		pCharQuantification->SetCharacteristicQuantificationIndex(GET_INT(xmlCharQuantification.characteristicQuantificationIndex));
		pCharQuantification->SetComment(GET_ST(xmlCharQuantification.comment));
		pCharQuantification->SetLabel(GET_ST(xmlCharQuantification.label));
		pCharQuantification->SetValueDescription(GET_ST(xmlCharQuantification.valueDescription));
		pCharQuantification->SetValueLabel(GET_ST(xmlCharQuantification.valueLabel));
	}

	return pCharQuantification;
}

const InferenceEntityVector XmlModelInternal::readXmlNode(AIMXML::CinferenceEntityCollectionType& xmlInferenceEntities)
{
	InferenceEntityVector inferenceEntities;

	if (xmlInferenceEntities.InferenceEntity.exists())
	{
		for(AIMXML::Iterator<CInferenceEntity> iter = xmlInferenceEntities.InferenceEntity.all(); iter; ++iter)
		{
			InferenceEntity inferenceEntity;
			bool flag;
			double dVal;

			inferenceEntity.SetUniqueIdentifier(GET_II(iter->uniqueIdentifier));
			inferenceEntity.SetTypeCode(GET_CDVECTOR(iter->typeCode));
			inferenceEntity.SetQuestionTypeCode(GET_CDVECTOR(iter->questionTypeCode));
			inferenceEntity.SetImageEvidence(GET_BL(iter->imageEvidence));
			inferenceEntity.SetIsPresent(GET_BL_PTR(iter->isPresent, flag));
			inferenceEntity.SetAnnotatorConfidence(GET_REAL_PTR(iter->annotatorConfidence, dVal));
			inferenceEntity.SetLabel(GET_ST(iter->label));
			inferenceEntity.SetQuestionIndex(GET_INT(iter->questionIndex));
			inferenceEntity.SetDescription(GET_ST(iter->description));
			inferenceEntity.SetComment(GET_ST(iter->comment));

			inferenceEntities.push_back(inferenceEntity);
		}
	}

	return inferenceEntities;
}

const AnnotationRoleEntityVector XmlModelInternal::readXmlNode(AIMXML::CannotationRoleEntityCollectionType& xmlAnnotationRoleEntities)
{
	AnnotationRoleEntityVector annotationRoleEntities;

	if (xmlAnnotationRoleEntities.AnnotationRoleEntity.exists())
	{
		for(AIMXML::Iterator<CAnnotationRoleEntity> iter = xmlAnnotationRoleEntities.AnnotationRoleEntity.all(); iter; ++iter)
		{
			AnnotationRoleEntity annRoleEntity;

			annRoleEntity.SetUniqueIdentifier(GET_II(iter->uniqueIdentifier));
			annRoleEntity.SetQuestionTypeCode(GET_CDVECTOR(iter->questionTypeCode));
			annRoleEntity.SetRoleCode(GET_CD(iter->roleCode));
			annRoleEntity.SetRoleSequenceNumber(GET_INT(iter->roleSequenceNumber));

			annotationRoleEntities.push_back(annRoleEntity);
		}
	}

	return annotationRoleEntities;
}

const TaskContextEntityVector XmlModelInternal::readXmlNode(AIMXML::CtaskContextEntityCollectionType& xmlTaskContextEntities)
{
	TaskContextEntityVector taskContextEntities;

	if (xmlTaskContextEntities.TaskContextEntity.exists())
	{
		for(AIMXML::Iterator<CTaskContextEntity> iter = xmlTaskContextEntities.TaskContextEntity.all(); iter; ++iter)
		{
			TaskContextEntity taskContextEntity = this->readXmlNode(*iter);
			taskContextEntities.push_back(taskContextEntity);
		}
	}

	return taskContextEntities;
}

const TaskContextEntityVector XmlModelInternal::readXmlNode(AIMXML::CtaskContextEntityCollectionType2& xmlTaskContextEntities)
{
	TaskContextEntityVector taskContextEntities;

	if (xmlTaskContextEntities.TaskContextEntity.exists())
	{
		for(AIMXML::Iterator<CTaskContextEntity> iter = xmlTaskContextEntities.TaskContextEntity.all(); iter; ++iter)
		{
			TaskContextEntity taskContextEntity = this->readXmlNode(*iter);
			taskContextEntities.push_back(taskContextEntity);
		}
	}

	return taskContextEntities;
}

const TaskContextEntity XmlModelInternal::readXmlNode(AIMXML::CTaskContextEntity& xmlTaskContextEntity)
{
	TaskContextEntity taskContextEntity;
	iso_21090::CD code;

	taskContextEntity.SetUniqueIdentifier(GET_II(xmlTaskContextEntity.uniqueIdentifier));
	taskContextEntity.SetWorklistTaskUid(GET_II(xmlTaskContextEntity.worklistTaskUid));
	taskContextEntity.SetWorklistTaskName(GET_ST(xmlTaskContextEntity.worklistTaskName));
	taskContextEntity.SetWorklistTaskDescription(GET_ST(xmlTaskContextEntity.worklistTaskDescription));
	taskContextEntity.SetWorklistTaskCategory(GET_CD(xmlTaskContextEntity.worklistTaskCategory));
	taskContextEntity.SetWorklistTaskLevel(GET_CD(xmlTaskContextEntity.worklistTaskLevel));
	taskContextEntity.SetWorklistTaskType(GET_CD(xmlTaskContextEntity.worklistTaskType));
	taskContextEntity.SetWorklistTaskRepeatType(GET_CD_PTR(xmlTaskContextEntity.worklistTaskRepeatType, code));
	taskContextEntity.SetWorklistTaskVariabilityType(GET_CD_PTR(xmlTaskContextEntity.worklistTaskVariabilityType, code));
	taskContextEntity.SetWorklistTaskVersion(GET_ST(xmlTaskContextEntity.worklistTaskVersion));
	taskContextEntity.SetWorklistSubtaskUid(GET_II(xmlTaskContextEntity.worklistSubtaskUid));
	taskContextEntity.SetWorklistSubtaskName(GET_ST(xmlTaskContextEntity.worklistSubtaskName));
	taskContextEntity.SetWorklistSubtaskStartDateTime(GET_DATETIME(xmlTaskContextEntity.worklistSubtaskStartDateTime));
	taskContextEntity.SetWorklistSubtaskClosedDateTime(GET_DATETIME(xmlTaskContextEntity.worklistSubtaskClosedDateTime));

	if (xmlTaskContextEntity.taskContextEntityCollection.exists())
	{
		CtaskContextEntityCollectionType2 xmlTaskContextEntities = xmlTaskContextEntity.taskContextEntityCollection.first();
		TaskContextEntityVector taskContextEntities = this->readXmlNode(xmlTaskContextEntities);
		taskContextEntity.SetTaskContextEntityCollection(taskContextEntities);
	}

	return taskContextEntity;
}

// Audit Trail Collection
const AuditTrailVector XmlModelInternal::readXmlNode(AIMXML::CauditTrailCollectionType& xmlAuditTrails)
{
	AuditTrailVector auditTrails;

	if (xmlAuditTrails.AuditTrail.exists())
	{
		for(AIMXML::Iterator<CAuditTrail> iter = xmlAuditTrails.AuditTrail.all(); iter; ++iter)
		{
			AuditTrail auditTrail;
			iso_21090::II uid;

			auditTrail.SetStatusCode(GET_CD(iter->statusCode));
			auditTrail.SetDateTime(GET_DATETIME(iter->dateTime));
			auditTrail.SetChangeReason(GET_CD(iter->changeReason));
			auditTrail.SetWorklistSubtaskUid(GET_II_PTR(iter->worklistSubtaskUid, uid));
			auditTrail.SetComment(GET_ST(iter->comment));

			auditTrails.push_back(auditTrail);
		}
	}

	return auditTrails;
}

const CalculationEntityVector XmlModelInternal::readXmlNode(AIMXML::CcalculationEntityCollectionType& xmlCalculationEntities)
{
	CalculationEntityVector calcEntities;

	if (xmlCalculationEntities.CalculationEntity.exists())
	{
		for(AIMXML::Iterator<CCalculationEntity> iter = xmlCalculationEntities.CalculationEntity.all(); iter; ++iter)
		{
			CalculationEntity calcEntity;

			calcEntity.SetUniqueIdentifier(GET_II(iter->uniqueIdentifier));
			calcEntity.SetTypeCode(GET_CDVECTOR(iter->typeCode));
			calcEntity.SetQuestionTypeCode(GET_CDVECTOR(iter->questionTypeCode));
			calcEntity.SetDescription(GET_ST(iter->description));
			calcEntity.SetMathML(GET_ST(iter->mathML));
			calcEntity.SetQuestionIndex(GET_INT(iter->questionIndex));

			// Algorithm
			if (iter->algorithm.exists())
			{
				CAlgorithm xmlAlgorithm = iter->algorithm.first();
				Algorithm algorithm = this->readXmlNode(xmlAlgorithm);
				calcEntity.SetAlgorithm(&algorithm);
			}

			// Calculation Result
			if (iter->calculationResultCollection.exists())
			{
				CcalculationResultCollectionType xmlCalcResults = iter->calculationResultCollection.first();
				CalculationResultPtrVector calcResults = this->readXmlNode(xmlCalcResults);
				calcEntity.SetCalculationResultCollection(calcResults);
				while(calcResults.size() > 0)
				{
					delete calcResults[calcResults.size() - 1];
					calcResults.pop_back();
				}
			}

			calcEntities.push_back(calcEntity);
		}
	}

	return calcEntities;
}

const Algorithm XmlModelInternal::readXmlNode(AIMXML::CAlgorithm& xmlAlgorithm)
{
	Algorithm algorithm;
	iso_21090::II uid;

	algorithm.SetName(GET_ST(xmlAlgorithm.name));
	algorithm.SetType(GET_CDVECTOR(xmlAlgorithm.type));
	algorithm.SetUniqueIdentifier(GET_II_PTR(xmlAlgorithm.uniqueIdentifier, uid));
	algorithm.SetVersion(GET_ST(xmlAlgorithm.version));
	algorithm.SetDescription(GET_ST(xmlAlgorithm.description));

	if (xmlAlgorithm.parameterCollection.exists())
	{
		CparameterCollectionType xmlParameters = xmlAlgorithm.parameterCollection.first();
		ParameterVector parameters = this->readXmlNode(xmlParameters);
		algorithm.SetParameterCollection(parameters);
	}

	return algorithm;
}

const ParameterVector XmlModelInternal::readXmlNode(AIMXML::CparameterCollectionType& xmlParameters)
{
	ParameterVector parameters;

	if (xmlParameters.Parameter.exists())
	{
		for(AIMXML::Iterator<CParameter> iter = xmlParameters.Parameter.all(); iter; ++iter)
		{
			Parameter param;

			param.SetName(GET_ST(iter->name));
			param.SetValue(GET_ST(iter->value2));
			param.SetDataType(GET_CD(iter->dataType));

			parameters.push_back(param);
		}
	}

	return parameters;
}

const CalculationResultPtrVector XmlModelInternal::readXmlNode(AIMXML::CcalculationResultCollectionType& xmlCalculationResults)
{
	CalculationResultPtrVector calcResults;

	if (xmlCalculationResults.CalculationResult.exists())
	{
		for(AIMXML::Iterator<CCalculationResult> iter = xmlCalculationResults.CalculationResult.all(); iter; ++iter)
		{
			CalculationResult* pCalcResult = NULL;

			std::string resultClass = this->GetSubClassType(iter->GetNode());
			if ("CompactCalculationResult" == resultClass)
			{
				CCompactCalculationResult xmlCompactCalcResult = iter->GetNode();
				CompactCalculationResult compactCalcResult;
				iso_21090::CD code;

				compactCalcResult.SetValue(GET_ST(xmlCompactCalcResult.value2));
				compactCalcResult.SetEncoding(GET_CD_PTR(xmlCompactCalcResult.encoding, code));
				compactCalcResult.SetCompression(GET_CD_PTR(xmlCompactCalcResult.compression, code));

				pCalcResult = compactCalcResult.Clone();
			}
			else if ("ExtendedCalculationResult" == resultClass)
			{
				CExtendedCalculationResult xmlExtendedCalcResult = iter->GetNode();
				ExtendedCalculationResult extendedCalcResult;

				if (xmlExtendedCalcResult.calculationDataCollection.exists())
				{
					CcalculationDataCollectionType xmlCalcData = xmlExtendedCalcResult.calculationDataCollection.first();
					CalculationDataVector calcData = this->readXmlNode(xmlCalcData);
					extendedCalcResult.SetCalculationDataCollection(calcData);
				}

				pCalcResult = extendedCalcResult.Clone();
			}
			else
				assert(false); // unknown calculation result class

			if (pCalcResult)
			{
				pCalcResult->SetType(iter->type.exists() ? CalculationResult::StringToCalculationResultType(iter->type) : CalculationResult::InvalidCalculationResultType);
				pCalcResult->SetUnitOfMeasure(GET_ST(iter->unitOfMeasure));
				pCalcResult->SetDataType(GET_CD(iter->dataType));

				if (iter->dimensionCollection.exists())
				{
					CdimensionCollectionType xmlDimensions = iter->dimensionCollection.first();
					DimensionVector dimensions = this->readXmlNode(xmlDimensions);
					pCalcResult->SetDimensionCollection(dimensions);
				}

				calcResults.push_back(pCalcResult);
			}
		}
	}

	return calcResults;
}

const DimensionVector XmlModelInternal::readXmlNode(AIMXML::CdimensionCollectionType& xmlDimensions)
{
	DimensionVector dimensions;

	if (xmlDimensions.Dimension.exists())
	{
		for(AIMXML::Iterator<CDimension> iter = xmlDimensions.Dimension.all(); iter; ++iter)
		{
			Dimension dim;

			dim.SetIndex(GET_INT(iter->index));
			dim.SetSize(GET_INT(iter->size));
			dim.SetLabel(GET_ST(iter->label));

			dimensions.push_back(dim);
		}
	}

	return dimensions;
}

const CalculationDataVector XmlModelInternal::readXmlNode(AIMXML::CcalculationDataCollectionType& xmlCalcData)
{
	CalculationDataVector calcData;

	if (xmlCalcData.CalculationData.exists())
	{
		for(AIMXML::Iterator<CCalculationData> iter = xmlCalcData.CalculationData.all(); iter; ++iter)
		{
			CalculationData calcDatum;

			calcDatum.SetValue(GET_ST(iter->value2));

			if (iter->coordinateCollection.exists())
			{
				CcoordinateCollectionType xmlCoords = iter->coordinateCollection.first();
				CoordinateVector coords = this->readXmlNode(xmlCoords);
				calcDatum.SetCoordinateCollection(coords);
			}

			calcData.push_back(calcDatum);
		}
	}

	return calcData;
}

const CoordinateVector XmlModelInternal::readXmlNode(AIMXML::CcoordinateCollectionType& xmlCoordinates)
{
	CoordinateVector coords;

	if (xmlCoordinates.Coordinate.exists())
	{
		for(AIMXML::Iterator<CCoordinate> iter = xmlCoordinates.Coordinate.all(); iter; ++iter)
		{
			Coordinate coord;

			coord.SetDimensionIndex(GET_INT(iter->dimensionIndex));
			coord.SetPosition(GET_INT(iter->position));

			coords.push_back(coord);
		}
	}

	return coords;
}

const LesionObservationEntityPtrVector XmlModelInternal::readXmlNode(AIMXML::ClesionObservationEntityCollectionType& xmlLesionObsEntities)
{
	LesionObservationEntityPtrVector lesionObsEntities;

	if (xmlLesionObsEntities.LesionObservationEntity.exists())
	{
		for(AIMXML::Iterator<CLesionObservationEntity> iter = xmlLesionObsEntities.LesionObservationEntity.all(); iter; ++iter)
		{
			LesionObservationEntity* pLesionObsEntity = NULL;

			std::string lesionClass = this->GetSubClassType(iter->GetNode());
			if ("GeneralLesionObservationEntity" == lesionClass)
			{
				CGeneralLesionObservationEntity xmlGenLesionObsEntity = iter->GetNode();
				GeneralLesionObservationEntity genLesionObsEntity;
				iso_21090::CD code;

				genLesionObsEntity.SetTrackingIdentifier(GET_ST(xmlGenLesionObsEntity.trackingIdentifier));
				genLesionObsEntity.SetLesionType(GET_CD(xmlGenLesionObsEntity.lesionType));
				genLesionObsEntity.SetReconstructionInterval(GET_CD_PTR(xmlGenLesionObsEntity.reconstructionInterval, code));
				genLesionObsEntity.SetLaterality(GET_CD_PTR(xmlGenLesionObsEntity.laterality, code));

				pLesionObsEntity = genLesionObsEntity.Clone();
			}
			else if ("TimePointLesionObservationEntity" == lesionClass)
			{
				CTimePointLesionObservationEntity xmlTimePointLesionObsEntity = iter->GetNode();
				TimePointLesionObservationEntity timePointLesionObsEntity;
				iso_21090::CD code;
				iso_21090::II uid;
				bool flag;

				timePointLesionObsEntity.SetCalibration(GET_BL(xmlTimePointLesionObsEntity.calibration));
				timePointLesionObsEntity.SetPredecessorLesionTrackingUid(GET_II_PTR(xmlTimePointLesionObsEntity.predecessorLesionTrackingUid, uid));
				timePointLesionObsEntity.SetComment(GET_ST(xmlTimePointLesionObsEntity.comment));
				timePointLesionObsEntity.SetTherapeuticResponse(GET_CD_PTR(xmlTimePointLesionObsEntity.therapeuticResponse, code));
				timePointLesionObsEntity.SetQualitativeAssessment(GET_CD_PTR(xmlTimePointLesionObsEntity.qualitativeAssessment, code));
				timePointLesionObsEntity.SetCanEvaluateLesion(GET_BL_PTR(xmlTimePointLesionObsEntity.canEvaluateLesion, flag));
				timePointLesionObsEntity.SetReasonUnableToEvaluate(GET_CD_PTR(xmlTimePointLesionObsEntity.reasonUnableToEvaluate, code));
				timePointLesionObsEntity.SetCanMeasureLesion(GET_BL_PTR(xmlTimePointLesionObsEntity.canMeasureLesion, flag));
				timePointLesionObsEntity.SetReasonUnableToMeasure(GET_CD_PTR(xmlTimePointLesionObsEntity.reasonUnableToMeasure, code));
				timePointLesionObsEntity.SetIsUnequivocalProgression(GET_BL_PTR(xmlTimePointLesionObsEntity.isUnequivocalProgression, flag));

				pLesionObsEntity = timePointLesionObsEntity.Clone();
			}
			else
				assert(false); // Unknow lesion class

			if (pLesionObsEntity)
			{
				bool flag;

				pLesionObsEntity->SetUniqueIdentifier(GET_II(iter->uniqueIdentifier));
				pLesionObsEntity->SetLesionUniqueIdentifier(GET_II(iter->lesionUniqueIdentifier));
				pLesionObsEntity->SetIsAdditionalObservation(GET_BL_PTR(iter->isAdditionalObservation, flag));

				lesionObsEntities.push_back(pLesionObsEntity);
			}
		}
	}

	return lesionObsEntities;
}

const SegmentationEntityPtrVector XmlModelInternal::readXmlNode(AIMXML::CsegmentationEntityCollectionType& xmlSegmentationEntities)
{
	SegmentationEntityPtrVector segmentationEntities;

	if (xmlSegmentationEntities.SegmentationEntity.exists())
	{
		for(AIMXML::Iterator<CSegmentationEntity> iter = xmlSegmentationEntities.SegmentationEntity.all(); iter; ++iter)
		{
			SegmentationEntity* pSegEntity = NULL;

			std::string segmentationClass = this->GetSubClassType(iter->GetNode());
			if ("DicomSegmentationEntity" == segmentationClass)
			{
				CDicomSegmentationEntity xmlDicomSegEntity = iter->GetNode();
				DicomSegmentationEntity dicomSegEntity;

				dicomSegEntity.SetSopInstanceUid(GET_II(xmlDicomSegEntity.sopInstanceUid));
				dicomSegEntity.SetSopClassUid(GET_II(xmlDicomSegEntity.sopClassUid));
				dicomSegEntity.SetReferencedSopInstanceUid(GET_II(xmlDicomSegEntity.referencedSopInstanceUid));
				dicomSegEntity.SetSegmentNumber(GET_INT(xmlDicomSegEntity.segmentNumber));

				pSegEntity = dicomSegEntity.Clone();
			}
			else
				assert(false); // Unknown class

			if (pSegEntity)
			{
				pSegEntity->SetUniqueIdentifier(GET_II(iter->uniqueIdentifier));

				segmentationEntities.push_back(pSegEntity);
			}
		}
	}

	return segmentationEntities;
}

const MarkupEntityPtrVector XmlModelInternal::readXmlNode(AIMXML::CmarkupEntityCollectionType& xmlMarkupEntities)
{
	MarkupEntityPtrVector markupEntities;

	if (xmlMarkupEntities.MarkupEntity.exists())
	{
		for(AIMXML::Iterator<CMarkupEntity> iter = xmlMarkupEntities.MarkupEntity.all(); iter; ++iter)
		{
			MarkupEntity* pMarkupEntity = NULL;

			std::string markupClass = this->GetSubClassType(iter->GetNode());
			if ("TextAnnotationEntity" == markupClass)
			{
				CTextAnnotationEntity xmlTextAnnEntity = iter->GetNode();
				TextAnnotationEntity textAnnEntity = this->readXmlNode(xmlTextAnnEntity);
				pMarkupEntity = textAnnEntity.Clone();
			}
			else
				pMarkupEntity = this->readXmlNode(*iter); // Geometric Shape

			if (pMarkupEntity)
				markupEntities.push_back(pMarkupEntity);
			else
				assert(false); // Uknown markup class
		}
	}

	return markupEntities;
}

const TextAnnotationEntity XmlModelInternal::readXmlNode(AIMXML::CTextAnnotationEntity& xmlTextAnnEntity)
{
	TextAnnotationEntity textAnnEntity;

	textAnnEntity.SetUniqueIdentifier(GET_II(xmlTextAnnEntity.uniqueIdentifier));
	textAnnEntity.SetText(GET_ST(xmlTextAnnEntity.text));
	textAnnEntity.SetFont(GET_ST(xmlTextAnnEntity.font));
	textAnnEntity.SetFontColor(GET_ST(xmlTextAnnEntity.fontColor));
	textAnnEntity.SetFontEffect(GET_ST(xmlTextAnnEntity.fontEffect));
	textAnnEntity.SetFontSize(GET_ST(xmlTextAnnEntity.fontSize));
	textAnnEntity.SetFontStyle(GET_ST(xmlTextAnnEntity.fontStyle));
	textAnnEntity.SetTextJustify(GET_ST(xmlTextAnnEntity.textJustify));
	textAnnEntity.SetFontOpacity(GET_ST(xmlTextAnnEntity.fontOpacity));

	if (xmlTextAnnEntity.geometricShapeEntity.exists())
	{
		CGeometricShapeEntity xmlGeoShapeEntity = xmlTextAnnEntity.geometricShapeEntity.first();
		GeometricShapeEntity* pGeoShapeEntity = this->readXmlNode(xmlGeoShapeEntity);
		textAnnEntity.SetGeometricShapeEntity(pGeoShapeEntity);
		delete pGeoShapeEntity;
	}

	return textAnnEntity;
}

GeometricShapeEntity* XmlModelInternal::readXmlNode(AIMXML::CMarkupEntity& xmlMarkupEntity)
{
	GeometricShapeEntity* pGeoShapeEntity = NULL;

	std::string markupClass = this->GetSubClassType(xmlMarkupEntity.GetNode());
	if ("TwoDimensionPoint" == markupClass)
	{
		CTwoDimensionPoint xmlTwoDimEntity = xmlMarkupEntity.GetNode();
		TwoDimensionPoint entity2D;
		this->readXmlNode(entity2D, xmlTwoDimEntity);
		pGeoShapeEntity = entity2D.Clone();
	}
	else if ("TwoDimensionCircle" == markupClass)
	{
		CTwoDimensionCircle xmlTwoDimEntity = xmlMarkupEntity.GetNode();
		TwoDimensionCircle entity2D;
		this->readXmlNode(entity2D, xmlTwoDimEntity);
		pGeoShapeEntity = entity2D.Clone();
	}
	else if ("TwoDimensionEllipse" == markupClass)
	{
		CTwoDimensionEllipse xmlTwoDimEntity = xmlMarkupEntity.GetNode();
		TwoDimensionEllipse entity2D;
		this->readXmlNode(entity2D, xmlTwoDimEntity);
		pGeoShapeEntity = entity2D.Clone();
	}
	else if ("TwoDimensionPolyline" == markupClass)
	{
		CTwoDimensionPolyline xmlTwoDimEntity = xmlMarkupEntity.GetNode();
		TwoDimensionPolyline entity2D;
		this->readXmlNode(entity2D, xmlTwoDimEntity);
		pGeoShapeEntity = entity2D.Clone();
	}
	else if ("TwoDimensionMultiPoint" == markupClass)
	{
		CTwoDimensionMultiPoint xmlTwoDimEntity = xmlMarkupEntity.GetNode();
		TwoDimensionMultiPoint entity2D;
		this->readXmlNode(entity2D, xmlTwoDimEntity);
		pGeoShapeEntity = entity2D.Clone();
	}
	else if ("ThreeDimensionPoint" == markupClass)
	{
		CThreeDimensionPoint xmlThreeDimEntity = xmlMarkupEntity.GetNode();
		ThreeDimensionPoint entity3D;
		this->readXmlNode(entity3D, xmlThreeDimEntity);
		pGeoShapeEntity = entity3D.Clone();
	}
	else if ("ThreeDimensionEllipse" == markupClass)
	{
		CThreeDimensionEllipse xmlThreeDimEntity = xmlMarkupEntity.GetNode();
		ThreeDimensionEllipse entity3D;
		this->readXmlNode(entity3D, xmlThreeDimEntity);
		pGeoShapeEntity = entity3D.Clone();
	}
	else if ("ThreeDimensionEllipsoid" == markupClass)
	{
		CThreeDimensionEllipsoid xmlThreeDimEntity = xmlMarkupEntity.GetNode();
		ThreeDimensionEllipsoid entity3D;
		this->readXmlNode(entity3D, xmlThreeDimEntity);
		pGeoShapeEntity = entity3D.Clone();
	}
	else if ("ThreeDimensionPolyline" == markupClass)
	{
		CThreeDimensionPolyline xmlThreeDimEntity = xmlMarkupEntity.GetNode();
		ThreeDimensionPolyline entity3D;
		this->readXmlNode(entity3D, xmlThreeDimEntity);
		pGeoShapeEntity = entity3D.Clone();
	}
	else if ("ThreeDimensionPolygon" == markupClass)
	{
		CThreeDimensionPolygon xmlThreeDimEntity = xmlMarkupEntity.GetNode();
		ThreeDimensionPolygon entity3D;
		this->readXmlNode(entity3D, xmlThreeDimEntity);
		pGeoShapeEntity = entity3D.Clone();
	}
	else if ("ThreeDimensionMultiPoint" == markupClass)
	{
		CThreeDimensionMultiPoint xmlThreeDimEntity = xmlMarkupEntity.GetNode();
		ThreeDimensionMultiPoint entity3D;
		this->readXmlNode(entity3D, xmlThreeDimEntity);
		pGeoShapeEntity = entity3D.Clone();
	}

	return pGeoShapeEntity;
}

void XmlModelInternal::readXmlNode(TwoDimensionGeometricShapeEntity& twoDimGeoShapeEntity, AIMXML::CTwoDimensionGeometricShapeEntity& xmlTwoDimGeoShapeEntity)
{
	iso_21090::CD code;
	iso_21090::II uid;

	twoDimGeoShapeEntity.SetUniqueIdentifier(GET_II(xmlTwoDimGeoShapeEntity.uniqueIdentifier));
	twoDimGeoShapeEntity.SetQuestionTypeCode(GET_CDVECTOR(xmlTwoDimGeoShapeEntity.questionTypeCode));
	twoDimGeoShapeEntity.SetShapeIdentifier(GET_INT(xmlTwoDimGeoShapeEntity.shapeIdentifier));
	twoDimGeoShapeEntity.SetLabel(GET_ST(xmlTwoDimGeoShapeEntity.label));
	twoDimGeoShapeEntity.SetDescription(GET_ST(xmlTwoDimGeoShapeEntity.description));
	twoDimGeoShapeEntity.SetIncludeFlag(GET_BL(xmlTwoDimGeoShapeEntity.includeFlag));
	twoDimGeoShapeEntity.SetComment(GET_ST(xmlTwoDimGeoShapeEntity.comment));
	twoDimGeoShapeEntity.SetLineColor(GET_ST(xmlTwoDimGeoShapeEntity.lineColor));
	twoDimGeoShapeEntity.SetLineOpacity(GET_ST(xmlTwoDimGeoShapeEntity.lineOpacity));
	twoDimGeoShapeEntity.SetLineStyle(GET_ST(xmlTwoDimGeoShapeEntity.lineStyle));
	twoDimGeoShapeEntity.SetLineThickness(GET_ST(xmlTwoDimGeoShapeEntity.lineThickness));
	twoDimGeoShapeEntity.SetQuestionIndex(GET_INT(xmlTwoDimGeoShapeEntity.questionIndex));
	twoDimGeoShapeEntity.SetInterpolationMethod(GET_CD_PTR(xmlTwoDimGeoShapeEntity.interpolationMethod, code));
	twoDimGeoShapeEntity.SetImageReferenceUid(GET_II_PTR(xmlTwoDimGeoShapeEntity.imageReferenceUid, uid));
	twoDimGeoShapeEntity.SetReferencedFrameNumber(GET_INT(xmlTwoDimGeoShapeEntity.referencedFrameNumber));
	twoDimGeoShapeEntity.SetUri(GET_ST(xmlTwoDimGeoShapeEntity.uri));

	if (xmlTwoDimGeoShapeEntity.twoDimensionSpatialCoordinateCollection.exists())
	{
		CtwoDimensionSpatialCoordinateCollectionType xmlTwoDimensionSpatialCoordinates = xmlTwoDimGeoShapeEntity.twoDimensionSpatialCoordinateCollection.first();
		TwoDimensionSpatialCoordinateVector twoDimensionSpatialCoords;
		for(AIMXML::Iterator<CTwoDimensionSpatialCoordinate> iter = xmlTwoDimensionSpatialCoordinates.TwoDimensionSpatialCoordinate.all(); iter; ++iter)
		{
			TwoDimensionSpatialCoordinate twoDimSpatialCoord;

			twoDimSpatialCoord.SetX(GET_REAL(iter->x));
			twoDimSpatialCoord.SetY(GET_REAL(iter->y));
			twoDimSpatialCoord.SetCoordinateIndex(GET_INT(iter->coordinateIndex));

			twoDimensionSpatialCoords.push_back(twoDimSpatialCoord);
		}

		twoDimGeoShapeEntity.SetTwoDimensionSpatialCoordinateCollection(twoDimensionSpatialCoords);
	}
}

void XmlModelInternal::readXmlNode(ThreeDimensionGeometricShapeEntity& threeDimGeoShapeEntity, AIMXML::CThreeDimensionGeometricShapeEntity& xmlThreeDimGeoShapeEntity)
{
	iso_21090::CD code;
	iso_21090::II uid;

	threeDimGeoShapeEntity.SetUniqueIdentifier(GET_II(xmlThreeDimGeoShapeEntity.uniqueIdentifier));
	threeDimGeoShapeEntity.SetQuestionTypeCode(GET_CDVECTOR(xmlThreeDimGeoShapeEntity.questionTypeCode));
	threeDimGeoShapeEntity.SetShapeIdentifier(GET_INT(xmlThreeDimGeoShapeEntity.shapeIdentifier));
	threeDimGeoShapeEntity.SetLabel(GET_ST(xmlThreeDimGeoShapeEntity.label));
	threeDimGeoShapeEntity.SetDescription(GET_ST(xmlThreeDimGeoShapeEntity.description));
	threeDimGeoShapeEntity.SetIncludeFlag(GET_BL(xmlThreeDimGeoShapeEntity.includeFlag));
	threeDimGeoShapeEntity.SetComment(GET_ST(xmlThreeDimGeoShapeEntity.comment));
	threeDimGeoShapeEntity.SetLineColor(GET_ST(xmlThreeDimGeoShapeEntity.lineColor));
	threeDimGeoShapeEntity.SetLineOpacity(GET_ST(xmlThreeDimGeoShapeEntity.lineOpacity));
	threeDimGeoShapeEntity.SetLineStyle(GET_ST(xmlThreeDimGeoShapeEntity.lineStyle));
	threeDimGeoShapeEntity.SetLineThickness(GET_ST(xmlThreeDimGeoShapeEntity.lineThickness));
	threeDimGeoShapeEntity.SetQuestionIndex(GET_INT(xmlThreeDimGeoShapeEntity.questionIndex));
	threeDimGeoShapeEntity.SetInterpolationMethod(GET_CD_PTR(xmlThreeDimGeoShapeEntity.interpolationMethod, code));
	threeDimGeoShapeEntity.SetFrameOfReferenceUid(GET_II_PTR(xmlThreeDimGeoShapeEntity.frameOfReferenceUid, uid));
	threeDimGeoShapeEntity.SetFiducialUid(GET_II_PTR(xmlThreeDimGeoShapeEntity.fiducialUid, uid));

	if (xmlThreeDimGeoShapeEntity.threeDimensionSpatialCoordinateCollection.exists())
	{
		CthreeDimensionSpatialCoordinateCollectionType xmlThreeDimensionSpatialCoordinates = xmlThreeDimGeoShapeEntity.threeDimensionSpatialCoordinateCollection.first();
		ThreeDimensionSpatialCoordinateVector threeDimensionSpatialCoords;
		for(AIMXML::Iterator<CThreeDimensionSpatialCoordinate> iter = xmlThreeDimensionSpatialCoordinates.ThreeDimensionSpatialCoordinate.all(); iter; ++iter)
		{
			ThreeDimensionSpatialCoordinate threeDimSpatialCoord;

			threeDimSpatialCoord.SetX(GET_REAL(iter->x));
			threeDimSpatialCoord.SetY(GET_REAL(iter->y));
			threeDimSpatialCoord.SetZ(GET_REAL(iter->z));
			threeDimSpatialCoord.SetCoordinateIndex(GET_INT(iter->coordinateIndex));

			threeDimensionSpatialCoords.push_back(threeDimSpatialCoord);
		}

		threeDimGeoShapeEntity.SetThreeDimensionSpatialCoordinateCollection(threeDimensionSpatialCoords);
	}
}

const ImageReferenceEntityPtrVector XmlModelInternal::readXmlNode(AIMXML::CimageReferenceEntityCollectionType& xmlImageRefereneceEntities)
{
	ImageReferenceEntityPtrVector imageRefEntities;

	if (xmlImageRefereneceEntities.ImageReferenceEntity.exists())
	{
		for(AIMXML::Iterator<CImageReferenceEntity> iter = xmlImageRefereneceEntities.ImageReferenceEntity.all(); iter; ++iter)
		{
			ImageReferenceEntity* pImageRefEntity = NULL;

			std::string imageRefClass = this->GetSubClassType(iter->GetNode());
			if ("DicomImageReferenceEntity" == imageRefClass)
			{
				CDicomImageReferenceEntity xmlDicomImageRefEntity = iter->GetNode();
				DicomImageReferenceEntity dicomImageRefEntity;

				if (xmlDicomImageRefEntity.imageStudy.exists())
				{
					CImageStudy xmlImageStudy = xmlDicomImageRefEntity.imageStudy.first();
					ImageStudy imageStudy = this->readXmlNode(xmlImageStudy);
					dicomImageRefEntity.SetImageStudy(imageStudy);
				}

				pImageRefEntity = dicomImageRefEntity.Clone();
			}
			else if ("UriImageReferenceEntity" == imageRefClass)
			{
				CUriImageReferenceEntity xmlUriImageRefEntity = iter->GetNode();
				UriImageReferenceEntity uriImageRefEntity;

				uriImageRefEntity.SetUri(GET_ST(xmlUriImageRefEntity.uri));
				uriImageRefEntity.SetMimeType(GET_ST(xmlUriImageRefEntity.mimeType));

				pImageRefEntity = uriImageRefEntity.Clone();
			}
			else
				assert(false); // Unexpected image reference class

			if (pImageRefEntity)
			{
				pImageRefEntity->SetUniqueIdentifier(GET_II(iter->uniqueIdentifier));

				imageRefEntities.push_back(pImageRefEntity);
			}
		}
	}

	return imageRefEntities;
}

const ImageStudy XmlModelInternal::readXmlNode(AIMXML::CImageStudy& xmlImageStudy)
{
	ImageStudy imageStudy;

	imageStudy.SetInstanceUid(GET_II(xmlImageStudy.instanceUid));
	imageStudy.SetStartDate(GET_DATE(xmlImageStudy.startDate));
	imageStudy.SetStartTime(GET_TIME(xmlImageStudy.startTime));
	imageStudy.SetProcedureDescription(GET_ST(xmlImageStudy.procedureDescription));

	if (xmlImageStudy.referencedDicomObjectCollection.exists())
	{
		CreferencedDicomObjectCollectionType xmlRefDicomObjects = xmlImageStudy.referencedDicomObjectCollection.first();
		ReferencedDicomObjectVector refDicomObjects = this->readXmlNode(xmlRefDicomObjects);
		imageStudy.SetReferencedDicomObjectCollection(refDicomObjects);
	}

	if (xmlImageStudy.imageSeries.exists())
	{
		CImageSeries xmlImageSeries = xmlImageStudy.imageSeries.first();
		ImageSeries imageSeries = this->readXmlNode(xmlImageSeries);
		imageStudy.SetImageSeries(imageSeries);
	}

	return imageStudy;
}

const ImageSeries XmlModelInternal::readXmlNode(AIMXML::CImageSeries& xmlImageSeries)
{
	ImageSeries imageSeries;

	imageSeries.SetInstanceUid(GET_II(xmlImageSeries.instanceUid));
	imageSeries.SetModality(GET_CD(xmlImageSeries.modality));

	if (xmlImageSeries.imageCollection.exists())
	{
		CimageCollectionType xmlImages = xmlImageSeries.imageCollection.first();
		ImageVector images = this->readXmlNode(xmlImages);
		imageSeries.SetImageCollection(images);
	}

	return imageSeries;
}

const ReferencedDicomObjectVector XmlModelInternal::readXmlNode(AIMXML::CreferencedDicomObjectCollectionType& xmlRefDicomObjects)
{
	ReferencedDicomObjectVector refDicomObjects;

	if (xmlRefDicomObjects.ReferencedDicomObject.exists())
	{
		for(AIMXML::Iterator<CReferencedDicomObject> iter = xmlRefDicomObjects.ReferencedDicomObject.all(); iter; ++iter)
		{
			ReferencedDicomObject refDicomObject;

			refDicomObject.SetModality(GET_CD(iter->modality));
			refDicomObject.SetSopInstanceUid(GET_II(iter->sopInstanceUid));

			refDicomObjects.push_back(refDicomObject);
		}
	}

	return refDicomObjects;
}

const ImageVector XmlModelInternal::readXmlNode(AIMXML::CimageCollectionType& xmlImages)
{
	ImageVector images;

	if (xmlImages.Image.exists())
	{
		for(AIMXML::Iterator<CImage> iter = xmlImages.Image.all(); iter; ++iter)
		{
			Image image;

			image.SetSopClassUid(GET_II(iter->sopClassUid));
			image.SetSopInstanceUid(GET_II(iter->sopInstanceUid));

			if (iter->generalImage.exists())
			{
				CGeneralImage xmlGeneralImage = iter->generalImage.first();
				GeneralImage generalImage;

				generalImage.SetPatientOrientationColumn(GET_ST(xmlGeneralImage.patientOrientationColumn));
				generalImage.SetPatientOrientationRow(GET_ST(xmlGeneralImage.patientOrientationRow));

				image.SetGeneralImage(&generalImage);
			}

			if (iter->imagePlane.exists())
			{
				CImagePlane xmlImagePlane = iter->imagePlane.first();
				ImagePlane imagePlane;
				double dVal;

				imagePlane.SetRowImageOrientationX(GET_REAL_PTR(xmlImagePlane.rowImageOrientationX, dVal));
				imagePlane.SetRowImageOrientationY(GET_REAL_PTR(xmlImagePlane.rowImageOrientationY, dVal));
				imagePlane.SetRowImageOrientationZ(GET_REAL_PTR(xmlImagePlane.rowImageOrientationZ, dVal));
				imagePlane.SetColumnImageOrientationX(GET_REAL_PTR(xmlImagePlane.columnImageOrientationX, dVal));
				imagePlane.SetColumnImageOrientationY(GET_REAL_PTR(xmlImagePlane.columnImageOrientationY, dVal));
				imagePlane.SetColumnImageOrientationZ(GET_REAL_PTR(xmlImagePlane.columnImageOrientationZ, dVal));
				imagePlane.SetVerticalPixelSpacing(GET_REAL_PTR(xmlImagePlane.verticalPixelSpacing, dVal));
				imagePlane.SetHorizontalPixelSpacing(GET_REAL_PTR(xmlImagePlane.horizontalPixelSpacing, dVal));
				imagePlane.SetSliceThickness(GET_REAL_PTR(xmlImagePlane.sliceThickness, dVal));
				imagePlane.SetImagePositionX(GET_REAL_PTR(xmlImagePlane.imagePositionX, dVal));
				imagePlane.SetImagePositionY(GET_REAL_PTR(xmlImagePlane.imagePositionY, dVal));
				imagePlane.SetImagePositionZ(GET_REAL_PTR(xmlImagePlane.imagePositionZ, dVal));

				image.SetImagePlane(&imagePlane);
			}

			images.push_back(image);
		}
	}

	return images;
}

// Image Annotation Statement collection
const ImageAnnotationStatementPtrVector XmlModelInternal::readXmlNode(AIMXML::CimageAnnotationStatementCollectionType& xmlImgAnnStatements)
{
	ImageAnnotationStatementPtrVector imgAnnStatements;

	if (xmlImgAnnStatements.ImageAnnotationStatement.exists())
	{
		for(AIMXML::Iterator<CAnnotationStatement> iter = xmlImgAnnStatements.ImageAnnotationStatement.all(); iter; ++iter)
		{
			AnnotationStatement* pAnnStmt = StatementFactory::Create(this->GetSubClassType(iter->GetNode()));
			if (pAnnStmt)
			{
				pAnnStmt->SetSubjectUniqueIdentifier(GET_II(iter->subjectUniqueIdentifier));
				pAnnStmt->SetObjectUniqueIdentifier(GET_II(iter->objectUniqueIdentifier));
				imgAnnStatements.push_back(pAnnStmt);
			}
			else
				assert(false); // Unknown annotation statement class
		}
	}

	return imgAnnStatements;
}

// Annotation of Annotation Statement collection
const AnnotationOfAnnotationStatementPtrVector XmlModelInternal::readXmlNode(AIMXML::CannotationOfAnnotationStatementCollectionType& xmlAnnOfAnnStatements)
{
	AnnotationOfAnnotationStatementPtrVector annOfAnnStatements;

	if (xmlAnnOfAnnStatements.AnnotationOfAnnotationStatement.exists())
	{
		for(AIMXML::Iterator<CAnnotationStatement> iter = xmlAnnOfAnnStatements.AnnotationOfAnnotationStatement.all(); iter; ++iter)
		{
			AnnotationStatement* pAnnStmt = StatementFactory::Create(this->GetSubClassType(iter->GetNode()));
			if (pAnnStmt)
			{
				pAnnStmt->SetSubjectUniqueIdentifier(GET_II(iter->subjectUniqueIdentifier));
				pAnnStmt->SetObjectUniqueIdentifier(GET_II(iter->objectUniqueIdentifier));
				annOfAnnStatements.push_back(pAnnStmt);
			}
			else
				assert(false); // Unknown annotation statement class
		}
	}

	return annOfAnnStatements;
}

const AdjudicationObservation XmlModelInternal::readXmlNode(AIMXML::CAdjudicationObservation& xmlAdjudicationObs)
{
	AdjudicationObservation adjudicationObs;
	iso_21090::CD code;

	adjudicationObs.SetObservationUid(GET_II(xmlAdjudicationObs.observationUid));
	adjudicationObs.SetObservationScope(GET_CD(xmlAdjudicationObs.observationScope));
	adjudicationObs.SetPersonObserversRoleInThisProcedure(GET_CD_PTR(xmlAdjudicationObs.personObserversRoleInThisProcedure, code));
	adjudicationObs.SetIdentifierWithinAcceptedPersonObserversRole(GET_STVECTOR(xmlAdjudicationObs.identifierWithinAcceptedPersonObserversRole));
	adjudicationObs.SetIdentifierWithinRejectedPersonObserversRole(GET_STVECTOR(xmlAdjudicationObs.identifierWithinRejectedPersonObserversRole));
	adjudicationObs.SetReasonForChoice(GET_CD(xmlAdjudicationObs.reasonForChoice));
	adjudicationObs.SetReasonForDiscordance(GET_CD_PTR(xmlAdjudicationObs.reasonForDiscordance, code));
	adjudicationObs.SetComment(GET_ST(xmlAdjudicationObs.comment));
	adjudicationObs.SetImageQualityIssuesDiscordance(GET_BL(xmlAdjudicationObs.imageQualityIssuesDiscordance));

	return adjudicationObs;
}

// User 
const User XmlModelInternal::readXmlNode(CUser& xmlUser)
{
	User user;
	user.SetName(GET_ST(xmlUser.name));
	user.SetLoginName(GET_ST(xmlUser.loginName));
	user.SetRoleInTrial(GET_ST(xmlUser.roleInTrial));
	user.SetNumberWithinRoleOfClinicalTrial(GET_INT(xmlUser.numberWithinRoleOfClinicalTrial));
	return user;
}

// Equipment
const Equipment XmlModelInternal::readXmlNode(CEquipment& xmlEquipment)
{
	Equipment equipment;

	equipment.SetManufacturerName(GET_ST(xmlEquipment.manufacturerName));
	equipment.SetManufacturerModelName(GET_ST(xmlEquipment.manufacturerModelName));
	equipment.SetSoftwareVersion(GET_ST(xmlEquipment.softwareVersion));
	equipment.SetDeviceSerialNumber(GET_ST(xmlEquipment.deviceSerialNumber));

	return equipment;
}

// Person
const Person XmlModelInternal::readXmlNode(AIMXML::CPerson& xmlPerson)
{
	Person person;
	person.SetName(GET_ST(xmlPerson.name));
	person.SetId(GET_ST(xmlPerson.id));
	person.SetBirthDate(GET_DATE(xmlPerson.birthDate));
	person.SetSex(GET_ST(xmlPerson.sex));
	person.SetEthnicGroup(GET_ST(xmlPerson.ethnicGroup));

	return person;
}

const std::string XmlModelInternal::GetSubClassType(xercesc::DOMNode *pNode)
{
	if (!pNode || !pNode->getAttributes())
		return "";

//	return altova::CNode::GetNodeTextValue(pNode->getAttributes()->getNamedItem(L"xsi:type"));

	std::vector<string_type> nsPrefixes;

	string_type nsPrefix = XercesUnstringTemp(pNode->getPrefix());
	string_type classType = XercesUnstringTemp(pNode->getAttributes()->getNamedItem(XercesStringTemp(_T("xsi:type")))->getNodeValue());

	if (!nsPrefix.empty())
		nsPrefixes.push_back(nsPrefix);

	// Find all xmlns:xyz attributes and collect their local names
	const static string_type xmlns("xmlns");
	xercesc::DOMNamedNodeMap* pAttrs = pNode->getAttributes();
	for(XMLSize_t i=0; i < pAttrs->getLength(); i++)
	{
		xercesc::DOMNode* pAttr = pAttrs->item(i);
		nsPrefix = XercesUnstringTemp(pAttr->getPrefix());
		if (nsPrefix == xmlns)
		{
			string_type localName = XercesUnstringTemp(pAttr->getLocalName());
			nsPrefixes.push_back(localName);
		}
	}

	// Remove namespace prefix from type value
	for (std::vector<string_type>::iterator iter = nsPrefixes.begin(); iter < nsPrefixes.end(); iter++)
	{
		nsPrefix = iter->c_str();
		if (classType.find(nsPrefix) == 0)
			return classType.substr(nsPrefix.size() + 1);
	}

	return classType;
	//return nsPrefix.empty() ? classType : classType.substr(nsPrefix.size() + 1);
}
