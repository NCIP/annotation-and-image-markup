/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "../stdafx.h"
#include "../AimHeaders.h"

#include "../AIMUtil.h"

#include "XmlModelInternal.h"

#include <typeinfo>

using namespace aim_lib;
using namespace AIMXML;
using namespace iso;

// ISO21090 helper macros
#define CREATE_ST(xmlNode, strVal) { CST xmlStr = xmlNode.append(); populateXmlNode(xmlStr, strVal); }
#define CREATE_BL(xmlNode, boolVal) { CBL xmlBool = xmlNode.append(); populateXmlNode(xmlBool, boolVal); }
#define CREATE_INT(xmlNode, intVal) { CINT xmlInt = xmlNode.append(); populateXmlNode(xmlInt, intVal); }
#define CREATE_REAL(xmlNode, dblVal) { CREAL xmlReal = xmlNode.append(); populateXmlNode(xmlReal, dblVal); }
#define CREATE_TS(xmlNode, dtVal) { CTS xmlTs = xmlNode.append(); populateXmlNode(xmlTs, dtVal); }
#define CREATE_II(xmlNode, iiVal) { CII xmlII = xmlNode.append(); populateXmlNode(xmlII, iiVal); }
#define CREATE_CD(xmlNode, cdVal) { CCD xmlCd = xmlNode.append(); populateXmlNode(xmlCd, cdVal); }

static const std::string C_AIM_SCHEMA_LOCATION="AIM_v4_rv44_XML.xsd";

/*
 * This class uses AIM data model to populate AIM XML data model by traversing every class
 * in the AIM data model and generating corresponding AIM XML data model.
 *
 */

XmlModelInternal::XmlModelInternal(void)
{
}

XmlModelInternal::~XmlModelInternal(void)
{
}

/*
* 
*/
void XmlModelInternal::createXmlNode(CAIMXML& xmlDoc, AnnotationCollection* pAnnotationCollection)
{
	if (pAnnotationCollection)
	{
		switch(pAnnotationCollection->GetAnnotationCollectionType())
		{
		case AnnotationCollection::ACT_ImageAnnotationCollection:
			{
				const ImageAnnotationCollection* pImgAnnotationCollection = dynamic_cast<const ImageAnnotationCollection*>(pAnnotationCollection);
				if (pImgAnnotationCollection)
				{
					CImageAnnotationCollection imgAnnColl = xmlDoc.ImageAnnotationCollection.append();
					xmlDoc.SetSchemaLocation(C_AIM_SCHEMA_LOCATION);

					this->populateXmlNode(imgAnnColl, *pImgAnnotationCollection);
				}
				else
					assert(false);
			}
			break;
		case AnnotationCollection::ACT_AnnotationOfAnnotationCollection:
			{
				const AnnotationOfAnnotationCollection* pAnnOfAnnColl = dynamic_cast<const AnnotationOfAnnotationCollection*>(pAnnotationCollection);
				if (pAnnOfAnnColl)
				{
					CAnnotationOfAnnotationCollection annOfAnnColl = xmlDoc.AnnotationOfAnnotationCollection.append();
					xmlDoc.SetSchemaLocation(C_AIM_SCHEMA_LOCATION);

					this->populateXmlNode(annOfAnnColl, *pAnnOfAnnColl);
				}
				else
					assert(false);
			}
			break;
		default:
			assert(false);
		}
	}
	else
		assert(false);
}

/*
* Create ImageAnnotationCollection
*/
void XmlModelInternal::populateXmlNode(AIMXML::CImageAnnotationCollection& xmlAnnotationColl, const ImageAnnotationCollection& imageAnnotationColl)
{
	this->populateXmlNode(dynamic_cast<AIMXML::CAnnotationCollection&>(xmlAnnotationColl), dynamic_cast<const AnnotationCollection&>(imageAnnotationColl));

	if (imageAnnotationColl.GetPerson())
	{
		CPerson xmlPerson = xmlAnnotationColl.person.append();
		this->populateXmlNode(xmlPerson, *imageAnnotationColl.GetPerson());
	}

	const ImageAnnotationVector& imageAnnotations = imageAnnotationColl.GetImageAnnotations();
	if (imageAnnotations.size() > 0)
	{
		CimageAnnotationsType xmlImageAnnotations = xmlAnnotationColl.imageAnnotations.append();
		for (ImageAnnotationVector::const_iterator iter = imageAnnotations.begin(); iter < imageAnnotations.end(); iter++)
		{
			this->createXmlNode(xmlImageAnnotations, *iter);
		}
	}
}

/*
* Create AnnotationOfAnnotationCollection
*/
void XmlModelInternal::populateXmlNode(AIMXML::CAnnotationOfAnnotationCollection& xmlAnnotationColl, const AnnotationOfAnnotationCollection& annOfAnnColl)
{
	this->populateXmlNode(dynamic_cast<AIMXML::CAnnotationCollection&>(xmlAnnotationColl), dynamic_cast<const AnnotationCollection&>(annOfAnnColl));

	const AnnotationOfAnnotationVector& annOfAnnotations = annOfAnnColl.GetAnnotationOfAnnotations();
	if (annOfAnnotations.size() > 0)
	{
		CannotationOfAnnotationsType xmlAnnOfAnnotations = xmlAnnotationColl.annotationOfAnnotations.append();
		for (AnnotationOfAnnotationVector::const_iterator iter = annOfAnnotations.begin(); iter < annOfAnnotations.end(); iter++)
		{
			this->createXmlNode(xmlAnnOfAnnotations, *iter);
		}
	}
}

/*
* Create AnnotationCollection
*/
void XmlModelInternal::populateXmlNode(AIMXML::CAnnotationCollection& xmlAnnotationColl, const AnnotationCollection& annotationColl)
{
	CREATE_II(xmlAnnotationColl.uniqueIdentifier, annotationColl.GetUniqueIdentifier());
	xmlAnnotationColl.aimVersion = _T(AimEnum::GetAimVersionString(annotationColl.GetAimVersion()));
	if (!annotationColl.GetDescription().empty())
		CREATE_ST(xmlAnnotationColl.description, annotationColl.GetDescription());
	CREATE_TS(xmlAnnotationColl.dateTime, annotationColl.GetDateTime());

	if (annotationColl.GetUser())
	{
		CUser xmlUser = xmlAnnotationColl.user.append();
		this->populateXmlNode(xmlUser, *annotationColl.GetUser());
	}

	if (annotationColl.GetEquipment())
	{
		CEquipment xmlEquipment = xmlAnnotationColl.equipment.append();
		this->populateXmlNode(xmlEquipment, *annotationColl.GetEquipment());
	}
}

/*
* Create AnnotationCollection
*/
void XmlModelInternal::populateXmlNode(AIMXML::CAnnotationEntity& xmlAnnotationEntity, const AnnotationEntity& annotationEntity)
{
	CREATE_II(xmlAnnotationEntity.uniqueIdentifier, annotationEntity.GetUniqueIdentifier());
	for (iso_21090::CDVector::const_iterator iter = annotationEntity.GetTypeCode().begin(); iter < annotationEntity.GetTypeCode().end(); iter++)
		CREATE_CD(xmlAnnotationEntity.typeCode, *iter);
	CREATE_TS(xmlAnnotationEntity.dateTime, annotationEntity.GetDateTime());
	CREATE_ST(xmlAnnotationEntity.name, annotationEntity.GetName());
	if (!annotationEntity.GetComment().empty())
		CREATE_ST(xmlAnnotationEntity.comment, annotationEntity.GetComment());
	if (annotationEntity.GetPrecedentReferencedAnnotationUid())
		CREATE_II(xmlAnnotationEntity.precedentReferencedAnnotationUid, *annotationEntity.GetPrecedentReferencedAnnotationUid());
	if (annotationEntity.GetTemplateUid())
		CREATE_II(xmlAnnotationEntity.templateUid, *annotationEntity.GetTemplateUid());

	const AuditTrailVector& auditTrails = annotationEntity.GetAuditTrailCollection();
	if (auditTrails.size() > 0)
	{
		CauditTrailCollectionType xmlAuditTrails = xmlAnnotationEntity.auditTrailCollection.append();
		for (AuditTrailVector::const_iterator iter = auditTrails.begin(); iter < auditTrails.end(); iter++)
			this->createXmlNode(xmlAuditTrails, *iter);
	}

	// Imaging Physical Entities
	const ImagingPhysicalEntityVector& imagingPhysEntities = annotationEntity.GetImagingPhysicalEntityCollection();
	if (imagingPhysEntities.size() > 0)
	{
		CimagingPhysicalEntityCollectionType xmlImagingPhysEntities = xmlAnnotationEntity.imagingPhysicalEntityCollection.append();
		for (ImagingPhysicalEntityVector::const_iterator iter = imagingPhysEntities.begin(); iter < imagingPhysEntities.end(); iter++)
			this->createXmlNode(xmlImagingPhysEntities, *iter);
	}
	// Calculation Entities
	const CalculationEntityVector& calcEntities = annotationEntity.GetCalculationEntityCollection();
	if (calcEntities.size() > 0)
	{
		CcalculationEntityCollectionType xmlCalcEntities = xmlAnnotationEntity.calculationEntityCollection.append();
		for (CalculationEntityVector::const_iterator iter = calcEntities.begin(); iter < calcEntities.end(); iter++)
			this->createXmlNode(xmlCalcEntities, *iter);
	}
	// Inference Entities
	const InferenceEntityVector& inferenceEntities = annotationEntity.GetInferenceEntityCollection();
	if (inferenceEntities.size() > 0)
	{
		CinferenceEntityCollectionType xmlInferenceEntities = xmlAnnotationEntity.inferenceEntityCollection.append();
		for (InferenceEntityVector::const_iterator iter = inferenceEntities.begin(); iter < inferenceEntities.end(); iter++)
			this->createXmlNode(xmlInferenceEntities, *iter);
	}
	// Annotation Role Entities
	const AnnotationRoleEntityVector& annotationRoleEntities = annotationEntity.GetAnnotationRoleEntityCollection();
	if (annotationRoleEntities.size() > 0)
	{
		CannotationRoleEntityCollectionType xmlAnnotationRoleEntities = xmlAnnotationEntity.annotationRoleEntityCollection.append();
		for (AnnotationRoleEntityVector::const_iterator iter = annotationRoleEntities.begin(); iter < annotationRoleEntities.end(); iter++)
			this->createXmlNode(xmlAnnotationRoleEntities, *iter);
	}
	// Lesion Observation Entities
	const LesionObservationEntityPtrVector& lesionObsEntities = annotationEntity.GetLesionObservationEntityCollection();
	if (lesionObsEntities.size() > 0)
	{
		ClesionObservationEntityCollectionType xmlLesionObsEntities = xmlAnnotationEntity.lesionObservationEntityCollection.append();
		for (LesionObservationEntityPtrVector::const_iterator iter = lesionObsEntities.begin(); iter < lesionObsEntities.end(); iter++)
			this->createXmlNode(xmlLesionObsEntities, *iter);
	}
	// Imaging Observation Entities
	const ImagingObservationEntityVector& imagingObsEntities = annotationEntity.GetImagingObservationEntityCollection();
	if (imagingObsEntities.size() > 0)

	{
		CimagingObservationEntityCollectionType xmlImagingObsEntities = xmlAnnotationEntity.imagingObservationEntityCollection.append();
		for (ImagingObservationEntityVector::const_iterator iter = imagingObsEntities.begin(); iter < imagingObsEntities.end(); iter++)
			this->createXmlNode(xmlImagingObsEntities, *iter);
	}
	// Task Context Entities
	const TaskContextEntityVector& taskContextEntities = annotationEntity.GetTaskContextEntityCollection();
	if (taskContextEntities.size() > 0)
	{
		CtaskContextEntityCollectionType xmlTaskContextEntities = xmlAnnotationEntity.taskContextEntityCollection.append();
		for (TaskContextEntityVector::const_iterator iter = taskContextEntities.begin(); iter < taskContextEntities.end(); iter++)
		{
			CTaskContextEntity xmlTaskContextEntity = xmlTaskContextEntities.TaskContextEntity.append();
			this->populateXmlNode(xmlTaskContextEntity, *iter);
		}
	}
}

/*
* Create ImageAnnotation
*/
void XmlModelInternal::createXmlNode(AIMXML::CimageAnnotationsType& xmlParent, const ImageAnnotation& imgAnnotation)
{
	CImageAnnotation xmlImageAnnotation = xmlParent.ImageAnnotation.append();

	this->populateXmlNode(dynamic_cast<AIMXML::CAnnotationEntity&>(xmlImageAnnotation), dynamic_cast<const AnnotationEntity&>(imgAnnotation));

	// Segmentation Entities
	const SegmentationEntityPtrVector& segmentations = imgAnnotation.GetSegmentationEntityCollection();
	if (segmentations.size() > 0)
	{
		CsegmentationEntityCollectionType xmlSegmentations = xmlImageAnnotation.segmentationEntityCollection.append();
		for (SegmentationEntityPtrVector::const_iterator iter = segmentations.begin(); iter < segmentations.end(); iter++)
			this->createXmlNode(xmlSegmentations, *iter);
	}
	// Markup Entities
	const MarkupEntityPtrVector& markupEntities = imgAnnotation.GetMarkupEntityCollection();
	if (markupEntities.size() > 0)
	{
		CmarkupEntityCollectionType xmlMarkupEntities = xmlImageAnnotation.markupEntityCollection.append();
		for (MarkupEntityPtrVector::const_iterator iter = markupEntities.begin(); iter < markupEntities.end(); iter++)
			this->createXmlNode(xmlMarkupEntities, *iter);
	}
	// Image Annotation Statements
	const ImageAnnotationStatementPtrVector& imageAnnStatements = imgAnnotation.GetImageAnnotationStatementCollection();
	if (imageAnnStatements.size() > 0)
	{
		CimageAnnotationStatementCollectionType xmlImgAnnStatements = xmlImageAnnotation.imageAnnotationStatementCollection.append();
		for (ImageAnnotationStatementPtrVector::const_iterator iter = imageAnnStatements.begin(); iter < imageAnnStatements.end(); iter++)
			this->createXmlNode(xmlImgAnnStatements, *iter);
	}
	// Image Reference Entities
	const ImageReferenceEntityPtrVector& imageReferenceEntities = imgAnnotation.GetImageReferenceEntityCollection();
	if (imageReferenceEntities.size() > 0)
	{
		CimageReferenceEntityCollectionType xmlImageRefEntities = xmlImageAnnotation.imageReferenceEntityCollection.append();
		for (ImageReferenceEntityPtrVector::const_iterator iter = imageReferenceEntities.begin(); iter < imageReferenceEntities.end(); iter++)
			this->createXmlNode(xmlImageRefEntities, *iter);
	}
}

/*
* Create AnnotationOfAnnotation
*/
void XmlModelInternal::createXmlNode(AIMXML::CannotationOfAnnotationsType& xmlParent, const AnnotationOfAnnotation& annotationOfAnnotation)
{
	CAnnotationOfAnnotation xmlAnnotationOfAnnotation = xmlParent.AnnotationOfAnnotation.append();

	this->populateXmlNode(dynamic_cast<AIMXML::CAnnotationEntity&>(xmlAnnotationOfAnnotation), dynamic_cast<const AnnotationEntity&>(annotationOfAnnotation));
	
	// Adjudication Entities
	if (annotationOfAnnotation.GetAdjudicationObservation())
	{
		CAdjudicationObservation xmlAdjudicationObs = xmlAnnotationOfAnnotation.adjudicationObservation.append();
		this->populateXmlNode(xmlAdjudicationObs, *annotationOfAnnotation.GetAdjudicationObservation());
	}
	// Annotation of Annotation Statements
	const AnnotationOfAnnotationStatementPtrVector& annOfAnnStatements = annotationOfAnnotation.GetAnnotationOfAnnotationStatementCollection();
	if (annOfAnnStatements.size() > 0)
	{
		CannotationOfAnnotationStatementCollectionType xmlAnnOfAnnStatements = xmlAnnotationOfAnnotation.annotationOfAnnotationStatementCollection.append();
		for (AnnotationOfAnnotationStatementPtrVector::const_iterator iter = annOfAnnStatements.begin(); iter < annOfAnnStatements.end(); iter++)
			this->createXmlNode(xmlAnnOfAnnStatements, *iter);
	}
}

void XmlModelInternal::createXmlNode(AIMXML::CimagingPhysicalEntityCollectionType& xmlParent, const ImagingPhysicalEntity& imagingPhysEntity)
{
	CImagingPhysicalEntity xmlImgPhysEntity = xmlParent.ImagingPhysicalEntity.append();

	CREATE_II(xmlImgPhysEntity.uniqueIdentifier, imagingPhysEntity.GetUniqueIdentifier());
	for (iso_21090::CDVector::const_iterator iter = imagingPhysEntity.GetTypeCode().begin(); iter < imagingPhysEntity.GetTypeCode().end(); iter++)
		CREATE_CD(xmlImgPhysEntity.typeCode, *iter);
	for (iso_21090::CDVector::const_iterator iter = imagingPhysEntity.GetQuestionTypeCode().begin(); iter < imagingPhysEntity.GetQuestionTypeCode().end(); iter++)
		CREATE_CD(xmlImgPhysEntity.questionTypeCode, *iter);
	if (imagingPhysEntity.GetIsPresent())
		CREATE_BL(xmlImgPhysEntity.isPresent, *imagingPhysEntity.GetIsPresent());
	if (imagingPhysEntity.GetAnnotatorConfidence())
		CREATE_REAL(xmlImgPhysEntity.annotatorConfidence, *imagingPhysEntity.GetAnnotatorConfidence());
	if (!imagingPhysEntity.GetLabel().empty())
		CREATE_ST(xmlImgPhysEntity.label, imagingPhysEntity.GetLabel());
	if (imagingPhysEntity.GetQuestionIndex() != -1)
		CREATE_INT(xmlImgPhysEntity.questionIndex, imagingPhysEntity.GetQuestionIndex());
	if (!imagingPhysEntity.GetComment().empty())
		CREATE_ST(xmlImgPhysEntity.comment, imagingPhysEntity.GetComment());

	const ImagingPhysicalEntityCharacteristicVector& imgPhysEntityChars = imagingPhysEntity.GetImagingPhysicalEntityCharacteristicCollection();
	if (imgPhysEntityChars.size() > 0)
	{
		CimagingPhysicalEntityCharacteristicCollectionType xmlImgPhysEntChars = xmlImgPhysEntity.imagingPhysicalEntityCharacteristicCollection.append();
		for (ImagingPhysicalEntityCharacteristicVector::const_iterator iter = imgPhysEntityChars.begin(); iter < imgPhysEntityChars.end(); iter++)
			this->createXmlNode(xmlImgPhysEntChars, *iter);
	}

	const ImagingObservationCharacteristicVector& imgObsChars = imagingPhysEntity.GetImagingObservationCharacteristicCollection();
	if (imgObsChars.size() > 0)
	{
		CimagingObservationCharacteristicCollectionType2 xmlImgObsChars = xmlImgPhysEntity.imagingObservationCharacteristicCollection.append();
		for (ImagingObservationCharacteristicVector::const_iterator iter = imgObsChars.begin(); iter < imgObsChars.end(); iter++)
		{
			CImagingObservationCharacteristic xmlImgObsChar = xmlImgObsChars.ImagingObservationCharacteristic.append();
			this->populateXmlNode(xmlImgObsChar, *iter);
		}
	}
}

void XmlModelInternal::createXmlNode(AIMXML::CimagingPhysicalEntityCharacteristicCollectionType& xmlParent, const ImagingPhysicalEntityCharacteristic& imagingPhysEntChar)
{
	CImagingPhysicalEntityCharacteristic xmlImgPhysEntityChar = xmlParent.ImagingPhysicalEntityCharacteristic.append();

	for (iso_21090::CDVector::const_iterator iter = imagingPhysEntChar.GetTypeCode().begin(); iter < imagingPhysEntChar.GetTypeCode().end(); iter++)
		CREATE_CD(xmlImgPhysEntityChar.typeCode, *iter);
	for (iso_21090::CDVector::const_iterator iter = imagingPhysEntChar.GetQuestionTypeCode().begin(); iter < imagingPhysEntChar.GetQuestionTypeCode().end(); iter++)
		CREATE_CD(xmlImgPhysEntityChar.questionTypeCode, *iter);
	if (imagingPhysEntChar.GetAnnotatorConfidence())
		CREATE_REAL(xmlImgPhysEntityChar.annotatorConfidence, *imagingPhysEntChar.GetAnnotatorConfidence());
	if (!imagingPhysEntChar.GetLabel().empty())
		CREATE_ST(xmlImgPhysEntityChar.label, imagingPhysEntChar.GetLabel());
	if (imagingPhysEntChar.GetQuestionIndex() != -1)
		CREATE_INT(xmlImgPhysEntityChar.questionIndex, imagingPhysEntChar.GetQuestionIndex());
	if (!imagingPhysEntChar.GetComment().empty())
		CREATE_ST(xmlImgPhysEntityChar.comment, imagingPhysEntChar.GetComment());

	const CharacteristicQuantificationPtrVector& charQuantifications = imagingPhysEntChar.GetCharacteristicQuantificationCollection();
	if (charQuantifications.size() > 0)
	{
		CcharacteristicQuantificationCollectionType2 xmlCharQuantifications = xmlImgPhysEntityChar.characteristicQuantificationCollection.append();
		for (CharacteristicQuantificationPtrVector::const_iterator iter = charQuantifications.begin(); iter < charQuantifications.end(); iter++)
		{
			if (*iter)
			{
				CharacteristicQuantificationWrapper wrapper(&xmlCharQuantifications);
				this->createXmlNode(wrapper, **iter);
			}
		}
	}
}

void XmlModelInternal::createXmlNode(AIMXML::CimagingObservationEntityCollectionType& xmlParent, const ImagingObservationEntity& imagingObsEntity)
{
	CImagingObservationEntity xmlImgObsEntity = xmlParent.ImagingObservationEntity.append();

	CREATE_II(xmlImgObsEntity.uniqueIdentifier, imagingObsEntity.GetUniqueIdentifier());
	for (iso_21090::CDVector::const_iterator iter = imagingObsEntity.GetTypeCode().begin(); iter < imagingObsEntity.GetTypeCode().end(); iter++)
		CREATE_CD(xmlImgObsEntity.typeCode, *iter);
	for (iso_21090::CDVector::const_iterator iter = imagingObsEntity.GetQuestionTypeCode().begin(); iter < imagingObsEntity.GetQuestionTypeCode().end(); iter++)
		CREATE_CD(xmlImgObsEntity.questionTypeCode, *iter);
	if (imagingObsEntity.GetAnnotatorConfidence())
		CREATE_REAL(xmlImgObsEntity.annotatorConfidence, *imagingObsEntity.GetAnnotatorConfidence());
	if (!imagingObsEntity.GetLabel().empty())
		CREATE_ST(xmlImgObsEntity.label, imagingObsEntity.GetLabel());
	if (!imagingObsEntity.GetComment().empty())
		CREATE_ST(xmlImgObsEntity.comment, imagingObsEntity.GetComment());
	if (imagingObsEntity.GetIsPresent())
		CREATE_BL(xmlImgObsEntity.isPresent, *imagingObsEntity.GetIsPresent());
	if (imagingObsEntity.GetQuestionIndex() != -1)
		CREATE_INT(xmlImgObsEntity.questionIndex, imagingObsEntity.GetQuestionIndex());

	const ImagingObservationCharacteristicVector& imgObsChars = imagingObsEntity.GetImagingObservationCharacteristicCollection();
	if (imgObsChars.size() > 0)
	{
		CimagingObservationCharacteristicCollectionType xmlImgObsChars = xmlImgObsEntity.imagingObservationCharacteristicCollection.append();
		for (ImagingObservationCharacteristicVector::const_iterator iter = imgObsChars.begin(); iter < imgObsChars.end(); iter++)
		{
			CImagingObservationCharacteristic xmlImgObsChar = xmlImgObsChars.ImagingObservationCharacteristic.append();
			this->populateXmlNode(xmlImgObsChar, *iter);
		}
	}
}

void XmlModelInternal::populateXmlNode(AIMXML::CImagingObservationCharacteristic& xmlImgObsChar, const ImagingObservationCharacteristic& imagingObjChar)
{
	for (iso_21090::CDVector::const_iterator iter = imagingObjChar.GetTypeCode().begin(); iter < imagingObjChar.GetTypeCode().end(); iter++)
		CREATE_CD(xmlImgObsChar.typeCode, *iter);
	for (iso_21090::CDVector::const_iterator iter = imagingObjChar.GetQuestionTypeCode().begin(); iter < imagingObjChar.GetQuestionTypeCode().end(); iter++)
		CREATE_CD(xmlImgObsChar.questionTypeCode, *iter);
	if (imagingObjChar.GetAnnotatorConfidence())
		CREATE_REAL(xmlImgObsChar.annotatorConfidence, *imagingObjChar.GetAnnotatorConfidence());
	if (!imagingObjChar.GetLabel().empty())
		CREATE_ST(xmlImgObsChar.label, imagingObjChar.GetLabel());
	if (!imagingObjChar.GetComment().empty())
		CREATE_ST(xmlImgObsChar.comment, imagingObjChar.GetComment());
	if (imagingObjChar.GetQuestionIndex() != -1)
		CREATE_INT(xmlImgObsChar.questionIndex, imagingObjChar.GetQuestionIndex());

	const CharacteristicQuantificationPtrVector& charQuantifications = imagingObjChar.GetCharacteristicQuantificationCollection();
	if (charQuantifications.size() > 0)
	{
		CcharacteristicQuantificationCollectionType xmlCharQuantifications = xmlImgObsChar.characteristicQuantificationCollection.append();
		for (CharacteristicQuantificationPtrVector::const_iterator iter = charQuantifications.begin(); iter < charQuantifications.end(); iter++)
		{
			if (*iter)
			{
				CharacteristicQuantificationWrapper wrapper(&xmlCharQuantifications);
				this->createXmlNode(wrapper, **iter);
			}
		}
	}
}

void XmlModelInternal::createXmlNode(CharacteristicQuantificationWrapper& parentObj, const CharacteristicQuantification& charQuantification)
{
	switch(charQuantification.GetQuantificationType())
	{
	case CharacteristicQuantification::QT_Numerical:
		{
			const Numerical& numerical = dynamic_cast<const Numerical&>(charQuantification);
			CNumerical xmlNumerical = parentObj.appendSpecial(AIMXML::_altova_ti_altova_CNumerical).GetNode();
			this->populateXmlNode(xmlNumerical, charQuantification);
			CREATE_ST(xmlNumerical.ucumString, numerical.GetUcumString());
			CREATE_REAL(xmlNumerical.value2, numerical.GetValue());
			if (numerical.GetOperator() != InvalidComparisonOperatorType && numerical.GetOperator() != None)
				xmlNumerical.operator2 = _T(AimEnum::ComparisonOperatorTypeToString(numerical.GetOperator()));
		}
		break;
	case CharacteristicQuantification::QT_Quantile:
		{
			const Quantile& quantile = dynamic_cast<const Quantile&>(charQuantification);
			CQuantile xmlQuantile = parentObj.appendSpecial(AIMXML::_altova_ti_altova_CQuantile).GetNode();
			this->populateXmlNode(xmlQuantile, charQuantification);
			CREATE_INT(xmlQuantile.bins, quantile.GetBins());
			CREATE_INT(xmlQuantile.selectedBin, quantile.GetSelectedBin());
			CREATE_REAL(xmlQuantile.minValue, quantile.GetMinValue());
			CREATE_REAL(xmlQuantile.maxValue, quantile.GetMaxValue());
		}
		break;
	case CharacteristicQuantification::QT_Non_Quantifiable:
		{
			const NonQuantifiable& nonQuantifiable = dynamic_cast<const NonQuantifiable&>(charQuantification);
			CNonQuantifiable xmlNonQuantifiable = parentObj.appendSpecial(AIMXML::_altova_ti_altova_CNonQuantifiable).GetNode();
			this->populateXmlNode(xmlNonQuantifiable, charQuantification);
			CREATE_CD(xmlNonQuantifiable.typeCode, nonQuantifiable.GetTypeCode());
		}
		break;
	case CharacteristicQuantification::QT_Scale:
		{
			const Scale& scale = dynamic_cast<const Scale&>(charQuantification);
			CScale xmlScale = parentObj.appendSpecial(AIMXML::_altova_ti_altova_CScale).GetNode();
			this->populateXmlNode(xmlScale, charQuantification);
			CREATE_ST(xmlScale.value2, scale.GetValue());
			xmlScale.type = _T(Scale::ScaleTypeToString(scale.GetScaleType()));
		}
		break;
	case CharacteristicQuantification::QT_Interval:
		{
			const Interval& interval = dynamic_cast<const Interval&>(charQuantification);
			CInterval xmlInterval = parentObj.appendSpecial(AIMXML::_altova_ti_altova_CInterval).GetNode();
			this->populateXmlNode(xmlInterval, charQuantification);
			CREATE_REAL(xmlInterval.minValue, interval.GetMinValue());
			CREATE_REAL(xmlInterval.maxValue, interval.GetMaxValue());
			CREATE_ST(xmlInterval.ucumString, interval.GetUcumString());
			if (interval.GetMinOperator() != InvalidComparisonOperatorType && interval.GetMinOperator() != None)
				xmlInterval.minOperator	= _T(AimEnum::ComparisonOperatorTypeToString(interval.GetMinOperator()));
			if (interval.GetMaxOperator() != InvalidComparisonOperatorType && interval.GetMaxOperator() != None)
				xmlInterval.maxOperator	= _T(AimEnum::ComparisonOperatorTypeToString(interval.GetMaxOperator()));
		}
		break;
	default:
		assert(false); // Unknown Quantification Characteristic
		return;
	}
}

/*
* Populate common elements of CharacteristicQuantification
*/
void XmlModelInternal::populateXmlNode(AIMXML::CCharacteristicQuantification& xmlCharQuantification, const CharacteristicQuantification& charQuantification)
{
	if (charQuantification.GetAnnotatorConfidence())
		CREATE_REAL(xmlCharQuantification.annotatorConfidence, *charQuantification.GetAnnotatorConfidence());
	if (charQuantification.GetCharacteristicQuantificationIndex() != -1)
		CREATE_INT(xmlCharQuantification.characteristicQuantificationIndex, charQuantification.GetCharacteristicQuantificationIndex());
	CREATE_ST(xmlCharQuantification.label, charQuantification.GetLabel());
	if (!charQuantification.GetValueLabel().empty())
		CREATE_ST(xmlCharQuantification.valueLabel, charQuantification.GetValueLabel());
	if (!charQuantification.GetValueDescription().empty())
		CREATE_ST(xmlCharQuantification.valueDescription, charQuantification.GetValueDescription());
	if (!charQuantification.GetComment().empty())
		CREATE_ST(xmlCharQuantification.comment, charQuantification.GetComment());
}

void XmlModelInternal::createXmlNode(AIMXML::CinferenceEntityCollectionType& xmlParent, const InferenceEntity& inferenceEntity)
{
	CInferenceEntity xmlInferenceEntity = xmlParent.InferenceEntity.append();

	CREATE_II(xmlInferenceEntity.uniqueIdentifier, inferenceEntity.GetUniqueIdentifier());
	CREATE_BL(xmlInferenceEntity.imageEvidence, inferenceEntity.GetIsImageEvidence());
	if (inferenceEntity.GetIsPresent())
		CREATE_BL(xmlInferenceEntity.isPresent, *inferenceEntity.GetIsPresent());
	for (iso_21090::CDVector::const_iterator iter = inferenceEntity.GetTypeCode().begin(); iter < inferenceEntity.GetTypeCode().end(); iter++)
		CREATE_CD(xmlInferenceEntity.typeCode, *iter);
	for (iso_21090::CDVector::const_iterator iter = inferenceEntity.GetQuestionTypeCode().begin(); iter < inferenceEntity.GetQuestionTypeCode().end(); iter++)
		CREATE_CD(xmlInferenceEntity.questionTypeCode, *iter);
	if (inferenceEntity.GetAnnotatorConfidence())
		CREATE_REAL(xmlInferenceEntity.annotatorConfidence, *inferenceEntity.GetAnnotatorConfidence());
	if (!inferenceEntity.GetDescription().empty())
		CREATE_ST(xmlInferenceEntity.description, inferenceEntity.GetDescription());
	if (!inferenceEntity.GetLabel().empty())
		CREATE_ST(xmlInferenceEntity.label, inferenceEntity.GetLabel());
	if (inferenceEntity.GetQuestionIndex() != -1)
		CREATE_INT(xmlInferenceEntity.questionIndex, inferenceEntity.GetQuestionIndex());
	if (!inferenceEntity.GetComment().empty())
		CREATE_ST(xmlInferenceEntity.comment, inferenceEntity.GetComment());
}

void XmlModelInternal::createXmlNode(AIMXML::CcalculationEntityCollectionType& xmlParent, const CalculationEntity& calculation)
{
	CCalculationEntity xmlCalcEntity = xmlParent.CalculationEntity.append();

	CREATE_II(xmlCalcEntity.uniqueIdentifier, calculation.GetUniqueIdentifier());
	for (iso_21090::CDVector::const_iterator iter = calculation.GetTypeCode().begin(); iter < calculation.GetTypeCode().end(); iter++)
		CREATE_CD(xmlCalcEntity.typeCode, *iter);
	for (iso_21090::CDVector::const_iterator iter = calculation.GetQuestionTypeCode().begin(); iter < calculation.GetQuestionTypeCode().end(); iter++)
		CREATE_CD(xmlCalcEntity.questionTypeCode, *iter);
	if (!calculation.GetDescription().empty())
		CREATE_ST(xmlCalcEntity.description, calculation.GetDescription());
	if (!calculation.GetMathML().empty())
		CREATE_ST(xmlCalcEntity.mathML, calculation.GetMathML());
	if (calculation.GetQuestionIndex() != -1)
		CREATE_INT(xmlCalcEntity.questionIndex, calculation.GetQuestionIndex());

	const CalculationResultPtrVector& calcResults = calculation.GetCalculationResultCollection();
	if (calcResults.size() > 0)
	{
		CcalculationResultCollectionType xmlCalcResults = xmlCalcEntity.calculationResultCollection.append();
		for (CalculationResultPtrVector::const_iterator iter = calcResults.begin(); iter < calcResults.end(); iter++)
			this->createXmlNode(xmlCalcResults, *iter);
	}
	if (calculation.GetAlgorithm())
	{
		CAlgorithm xmlAlorithm = xmlCalcEntity.algorithm.append();
		this->populateXmlNode(xmlAlorithm, *calculation.GetAlgorithm());
	}

}

void XmlModelInternal::populateXmlNode(AIMXML::CAlgorithm& xmlAlgorithm, const Algorithm& algorithm)
{
	CREATE_ST(xmlAlgorithm.name, algorithm.GetName());
	for (iso_21090::CDVector::const_iterator iter = algorithm.GetType().begin(); iter < algorithm.GetType().end(); iter++)
		CREATE_CD(xmlAlgorithm.type, *iter);
	if (algorithm.GetUniqueIdentifier())
		CREATE_II(xmlAlgorithm.uniqueIdentifier, *algorithm.GetUniqueIdentifier());
	if (!algorithm.GetVersion().empty())
		CREATE_ST(xmlAlgorithm.version, algorithm.GetVersion());
	if (!algorithm.GetDescription().empty())
		CREATE_ST(xmlAlgorithm.description, algorithm.GetDescription());

	const ParameterVector& params = algorithm.GetParameterCollection();
	if (params.size() > 0)
	{
		CparameterCollectionType xmlParams = xmlAlgorithm.parameterCollection.append();
		for (ParameterVector::const_iterator iter = params.begin(); iter < params.end(); iter++)
			this->createXmlNode(xmlParams, *iter);
	}
}

void XmlModelInternal::createXmlNode(AIMXML::CparameterCollectionType& xmlParent, const Parameter& parameter)
{
	CParameter xmlParam = xmlParent.Parameter.append();

	CREATE_ST(xmlParam.name, parameter.GetName());
	CREATE_ST(xmlParam.value2, parameter.GetValue());
	CREATE_CD(xmlParam.dataType, parameter.GetDataType());
}

void XmlModelInternal::createXmlNode(AIMXML::CcalculationResultCollectionType& xmlParent, const CalculationResult* pCalcResult)
{
	if (!pCalcResult)
		return;

	const CompactCalculationResult* pCompactCalcResult = dynamic_cast<const CompactCalculationResult*>(pCalcResult);
	const ExtendedCalculationResult* pExtendedCalcResult = dynamic_cast<const ExtendedCalculationResult*>(pCalcResult);

	assert(pCompactCalcResult || pExtendedCalcResult);

	if (pCompactCalcResult)
	{
		assert(!pExtendedCalcResult);
		CCompactCalculationResult xmlCompactCalcResult = xmlParent.CalculationResult.appendSpecial(AIMXML::_altova_ti_altova_CCompactCalculationResult);
		this->populateXmlNode(xmlCompactCalcResult, *pCalcResult);
		this->populateXmlNode(xmlCompactCalcResult, *pCompactCalcResult);
	}
	else if (pExtendedCalcResult)
	{
		CExtendedCalculationResult xmlExtendedCalcResult = xmlParent.CalculationResult.appendSpecial(AIMXML::_altova_ti_altova_CExtendedCalculationResult);
		this->populateXmlNode(xmlExtendedCalcResult, *pCalcResult);
		this->populateXmlNode(xmlExtendedCalcResult, *pExtendedCalcResult);
	}
	else
		assert(false);
}

void XmlModelInternal::populateXmlNode(AIMXML::CCalculationResult& xmlCalcResult, const CalculationResult& calcResult)
{
	CREATE_ST(xmlCalcResult.unitOfMeasure, calcResult.GetUnitOfMeasure());
	CREATE_CD(xmlCalcResult.dataType, calcResult.GetDataType());
	const DimensionVector& dimensions = calcResult.GetDimensionCollection();
	xmlCalcResult.type = _T(CalculationResult::CalculationResultTypeToString(calcResult.GetType()));
	if (dimensions.size() > 0)
	{
		CdimensionCollectionType xmlDimensions = xmlCalcResult.dimensionCollection.append();
		for (DimensionVector::const_iterator iter = dimensions.begin(); iter < dimensions.end(); iter++)
			this->createXmlNode(xmlDimensions, *iter);
	}
}

void XmlModelInternal::populateXmlNode(AIMXML::CCompactCalculationResult& xmlCompactCalcResult, const CompactCalculationResult& compactCalcResult)
{
	CREATE_ST(xmlCompactCalcResult.value2, compactCalcResult.GetValue());
	if (compactCalcResult.GetEncoding())
		CREATE_CD(xmlCompactCalcResult.encoding, *compactCalcResult.GetEncoding());
	if (compactCalcResult.GetCompression())
		CREATE_CD(xmlCompactCalcResult.compression, *compactCalcResult.GetCompression());
}

void XmlModelInternal::populateXmlNode(AIMXML::CExtendedCalculationResult& xmlExtCalcResult, const ExtendedCalculationResult& extCalcResult)
{
	if (extCalcResult.GetCalculationDataCollection().size() > 0)
	{
		CcalculationDataCollectionType xmlCalculations = xmlExtCalcResult.calculationDataCollection.append();
		for (CalculationDataVector::const_iterator iter = extCalcResult.GetCalculationDataCollection().begin(); iter < extCalcResult.GetCalculationDataCollection().end(); iter++)
			this->createXmlNode(xmlCalculations, *iter);
	}
}

void XmlModelInternal::createXmlNode(AIMXML::CdimensionCollectionType& xmlParent, const Dimension& dimension)
{
	CDimension xmlDimension = xmlParent.Dimension.append();

	CREATE_INT(xmlDimension.index, dimension.GetIndex());
	CREATE_INT(xmlDimension.size, dimension.GetSize());
	CREATE_ST(xmlDimension.label, dimension.GetLabel());
}

void XmlModelInternal::createXmlNode(AIMXML::CcalculationDataCollectionType& xmlParent, const CalculationData& data)
{
	CCalculationData xmlCalcData = xmlParent.CalculationData.append();

	CREATE_ST(xmlCalcData.value2, data.GetValue());
	if (data.GetCoordinateCollection().size() > 0)
	{
		CcoordinateCollectionType xmlCoordinates = xmlCalcData.coordinateCollection.append();
		for (CoordinateVector::const_iterator iter = data.GetCoordinateCollection().begin(); iter < data.GetCoordinateCollection().end(); iter++)
			this->createXmlNode(xmlCoordinates, *iter);
	}
}

void XmlModelInternal::createXmlNode(AIMXML::CcoordinateCollectionType& xmlParent, const Coordinate& coordinate)
{
	CCoordinate xmlCoord = xmlParent.Coordinate.append();

	CREATE_INT(xmlCoord.dimensionIndex, coordinate.GetDimensionIndex());
	CREATE_INT(xmlCoord.position, coordinate.GetPosition());
}

void XmlModelInternal::populateXmlNode(AIMXML::CTaskContextEntity& xmlTaskContextEntity, const TaskContextEntity& taskContextEntity)
{
	CREATE_II(xmlTaskContextEntity.uniqueIdentifier, taskContextEntity.GetUniqueIdentifier());
	CREATE_II(xmlTaskContextEntity.worklistTaskUid, taskContextEntity.GetWorklistTaskUid());
	CREATE_ST(xmlTaskContextEntity.worklistTaskName, taskContextEntity.GetWorklistTaskName());
	CREATE_ST(xmlTaskContextEntity.worklistTaskDescription, taskContextEntity.GetWorklistTaskDescription());
	CREATE_CD(xmlTaskContextEntity.worklistTaskCategory, taskContextEntity.GetWorklistTaskCategory());
	CREATE_CD(xmlTaskContextEntity.worklistTaskLevel, taskContextEntity.GetWorklistTaskLevel());
	CREATE_CD(xmlTaskContextEntity.worklistTaskType, taskContextEntity.GetWorklistTaskType());
	if (taskContextEntity.GetWorklistTaskRepeatType())
		CREATE_CD(xmlTaskContextEntity.worklistTaskRepeatType, *taskContextEntity.GetWorklistTaskRepeatType());
	if (taskContextEntity.GetWorklistTaskVariabilityType())
		CREATE_CD(xmlTaskContextEntity.worklistTaskVariabilityType, *taskContextEntity.GetWorklistTaskVariabilityType());
	CREATE_ST(xmlTaskContextEntity.worklistTaskVersion, taskContextEntity.GetWorklistTaskVersion());
	CREATE_II(xmlTaskContextEntity.worklistSubtaskUid, taskContextEntity.GetWorklistSubtaskUid());
	CREATE_ST(xmlTaskContextEntity.worklistSubtaskName, taskContextEntity.GetWorklistSubtaskName());
	CREATE_TS(xmlTaskContextEntity.worklistSubtaskStartDateTime, taskContextEntity.GetWorklistSubtaskStartDateTime());
	CREATE_TS(xmlTaskContextEntity.worklistSubtaskClosedDateTime, taskContextEntity.GetWorklistSubtaskClosedDateTime());

	const TaskContextEntityVector& taskContextEntities = taskContextEntity.GetTaskContextEntityCollection();
	if (taskContextEntities.size() > 0)
	{
		CtaskContextEntityCollectionType2 xmlTaskContextEntities = xmlTaskContextEntity.taskContextEntityCollection.append();
		for (TaskContextEntityVector::const_iterator iter = taskContextEntities.begin(); iter < taskContextEntities.end(); iter++)
		{
			CTaskContextEntity xmlChildTaskContextEntity = xmlTaskContextEntities.TaskContextEntity.append();
			this->populateXmlNode(xmlChildTaskContextEntity, *iter); // recusive!
		}
	}
}

void XmlModelInternal::createXmlNode(AIMXML::ClesionObservationEntityCollectionType& xmlParent, const LesionObservationEntity* pLesionObsEntity)
{
	if (!pLesionObsEntity)
		return;

	const GeneralLesionObservationEntity* pGenLesionObsEntity = dynamic_cast<const GeneralLesionObservationEntity*>(pLesionObsEntity);
	const TimePointLesionObservationEntity* pTimePointLesionObsEntity = dynamic_cast<const TimePointLesionObservationEntity*>(pLesionObsEntity);

	assert(pGenLesionObsEntity || pTimePointLesionObsEntity);

	if (pGenLesionObsEntity)
	{
		assert(!pTimePointLesionObsEntity);
		CGeneralLesionObservationEntity xmlGenLesionObsEntity = xmlParent.LesionObservationEntity.appendSpecial(AIMXML::_altova_ti_altova_CGeneralLesionObservationEntity);
		this->populateXmlNode(xmlGenLesionObsEntity, *pLesionObsEntity);
		this->populateXmlNode(xmlGenLesionObsEntity, *pGenLesionObsEntity);
	}
	else if (pTimePointLesionObsEntity)
	{
		CTimePointLesionObservationEntity xmlTimePointObsEntity = xmlParent.LesionObservationEntity.appendSpecial(AIMXML::_altova_ti_altova_CTimePointLesionObservationEntity);
		this->populateXmlNode(xmlTimePointObsEntity, *pLesionObsEntity);
		this->populateXmlNode(xmlTimePointObsEntity, *pTimePointLesionObsEntity);
	}
	else
		assert(false);
}

void XmlModelInternal::populateXmlNode(AIMXML::CLesionObservationEntity& xmlLesionObsEntity, const LesionObservationEntity& lesionObsEntity)
{
	CREATE_II(xmlLesionObsEntity.uniqueIdentifier, lesionObsEntity.GetUniqueIdentifier());
	CREATE_II(xmlLesionObsEntity.lesionUniqueIdentifier, lesionObsEntity.GetLesionUniqueIdentifier());
	if (lesionObsEntity.GetIsAdditionalObservation())
		CREATE_BL(xmlLesionObsEntity.isAdditionalObservation, *lesionObsEntity.GetIsAdditionalObservation());
}

void XmlModelInternal::populateXmlNode(AIMXML::CGeneralLesionObservationEntity& xmlGenLesionObsEnt, const GeneralLesionObservationEntity& genLesionObsEntity)
{
	CREATE_ST(xmlGenLesionObsEnt.trackingIdentifier, genLesionObsEntity.GetTrackingIdentifier());
	CREATE_CD(xmlGenLesionObsEnt.lesionType, genLesionObsEntity.GetLesionType());
	if (genLesionObsEntity.GetReconstructionInterval())
		CREATE_CD(xmlGenLesionObsEnt.reconstructionInterval, *genLesionObsEntity.GetReconstructionInterval());
	if (genLesionObsEntity.GetLaterality())
		CREATE_CD(xmlGenLesionObsEnt.laterality, *genLesionObsEntity.GetLaterality());
}

void XmlModelInternal::populateXmlNode(AIMXML::CTimePointLesionObservationEntity& xmlTimePointLesionObsEnt, const TimePointLesionObservationEntity& timepointLesionObsEntity)
{
	CREATE_BL(xmlTimePointLesionObsEnt.calibration, timepointLesionObsEntity.GetCalibration());
	if (timepointLesionObsEntity.GetPredecessorLesionTrackingUid())
		CREATE_II(xmlTimePointLesionObsEnt.predecessorLesionTrackingUid, *timepointLesionObsEntity.GetPredecessorLesionTrackingUid());
	if (!timepointLesionObsEntity.GetComment().empty())
		CREATE_ST(xmlTimePointLesionObsEnt.comment, timepointLesionObsEntity.GetComment());
	if (timepointLesionObsEntity.GetTherapeuticResponse())
		CREATE_CD(xmlTimePointLesionObsEnt.therapeuticResponse, *timepointLesionObsEntity.GetTherapeuticResponse());
	if (timepointLesionObsEntity.GetQualitativeAssessment())
		CREATE_CD(xmlTimePointLesionObsEnt.qualitativeAssessment, *timepointLesionObsEntity.GetQualitativeAssessment());
	if (timepointLesionObsEntity.GetCanEvaluateLesion())
		CREATE_BL(xmlTimePointLesionObsEnt.canEvaluateLesion, *timepointLesionObsEntity.GetCanEvaluateLesion());
	if (timepointLesionObsEntity.GetReasonUnableToEvaluate())
		CREATE_CD(xmlTimePointLesionObsEnt.reasonUnableToEvaluate, *timepointLesionObsEntity.GetReasonUnableToEvaluate());
	if (timepointLesionObsEntity.GetCanMeasureLesion())
		CREATE_BL(xmlTimePointLesionObsEnt.canMeasureLesion, *timepointLesionObsEntity.GetCanMeasureLesion());
	if (timepointLesionObsEntity.GetReasonUnableToMeasure())
		CREATE_CD(xmlTimePointLesionObsEnt.reasonUnableToMeasure, *timepointLesionObsEntity.GetReasonUnableToMeasure());
	if (timepointLesionObsEntity.GetIsUnequivocalProgression())
		CREATE_BL(xmlTimePointLesionObsEnt.isUnequivocalProgression, *timepointLesionObsEntity.GetIsUnequivocalProgression());
}

void XmlModelInternal::createXmlNode(AIMXML::CannotationRoleEntityCollectionType& xmlParent, const AnnotationRoleEntity& annRoleEntity)
{
	CAnnotationRoleEntity xmlAnnotaionRole = xmlParent.AnnotationRoleEntity.append();

	CREATE_II(xmlAnnotaionRole.uniqueIdentifier, annRoleEntity.GetUniqueIdentifier());
	CREATE_CD(xmlAnnotaionRole.roleCode, annRoleEntity.GetRoleCode());
	for (iso_21090::CDVector::const_iterator iter = annRoleEntity.GetQuestionTypeCode().begin(); iter < annRoleEntity.GetQuestionTypeCode().end(); iter++)
		CREATE_CD(xmlAnnotaionRole.questionTypeCode, *iter);
	CREATE_INT(xmlAnnotaionRole.roleSequenceNumber, annRoleEntity.GetRoleSequenceNumber());
}

void XmlModelInternal::createXmlNode(AIMXML::CauditTrailCollectionType& xmlParent, const AuditTrail& auditTrail)
{
	CAuditTrail xmlAuditTrail = xmlParent.AuditTrail.append();

	CREATE_CD(xmlAuditTrail.statusCode, auditTrail.GetStatusCode());
	CREATE_TS(xmlAuditTrail.dateTime, auditTrail.GetDateTime());
	CREATE_CD(xmlAuditTrail.changeReason, auditTrail.GetChangeReason());
	if (auditTrail.GetWorklistSubtaskUid())
		CREATE_II(xmlAuditTrail.worklistSubtaskUid, *auditTrail.GetWorklistSubtaskUid());
	if (!auditTrail.GetComment().empty())
		CREATE_ST(xmlAuditTrail.comment, auditTrail.GetComment());
}

void XmlModelInternal::createXmlNode(AIMXML::CsegmentationEntityCollectionType& xmlParent, const SegmentationEntity* pSegmentationEntity)
{
	if (!pSegmentationEntity)
		return;

	const DicomSegmentationEntity* pDicomSegEntity = dynamic_cast<const DicomSegmentationEntity*>(pSegmentationEntity);

	if (pDicomSegEntity)
	{
		CDicomSegmentationEntity xmlDicomSegEntity = xmlParent.SegmentationEntity.appendSpecial(AIMXML::_altova_ti_altova_CDicomSegmentationEntity);
		CREATE_II(xmlDicomSegEntity.uniqueIdentifier, pDicomSegEntity->GetUniqueIdentifier());
		CREATE_II(xmlDicomSegEntity.sopInstanceUid, pDicomSegEntity->GetSopInstanceUid());
		CREATE_II(xmlDicomSegEntity.sopClassUid, pDicomSegEntity->GetSopClassUid());
		CREATE_II(xmlDicomSegEntity.referencedSopInstanceUid, pDicomSegEntity->GetReferencedSopInstanceUid());
		CREATE_INT(xmlDicomSegEntity.segmentNumber, pDicomSegEntity->GetSegmentNumber());		
	}
	else
		assert(false); // Unknown segmenation type
}

void XmlModelInternal::createXmlNode(AIMXML::CmarkupEntityCollectionType& xmlParent, const MarkupEntity* pMarkupEntity)
{
	if (!pMarkupEntity)
		return;

	const TextAnnotationEntity* pTextAnnEntity = dynamic_cast<const TextAnnotationEntity*>(pMarkupEntity);
	const GeometricShapeEntity* pGeoShapeEntity = dynamic_cast<const GeometricShapeEntity*>(pMarkupEntity);

	assert(!pTextAnnEntity || !pGeoShapeEntity);

	if (pTextAnnEntity)
	{
		CTextAnnotationEntity xmlTextAnnEntity = xmlParent.MarkupEntity.appendSpecial(AIMXML::_altova_ti_altova_CTextAnnotationEntity);
		this->populateXmlNode(xmlTextAnnEntity, *pTextAnnEntity);
	}
	else if (pGeoShapeEntity)
	{
		const TwoDimensionGeometricShapeEntity* pGeoShapeEntity2D = dynamic_cast<const TwoDimensionGeometricShapeEntity*>(pGeoShapeEntity);
		const ThreeDimensionGeometricShapeEntity* pGeoShapeEntity3D = dynamic_cast<const ThreeDimensionGeometricShapeEntity*>(pGeoShapeEntity);

		assert(!pGeoShapeEntity2D || !pGeoShapeEntity3D);

		if (pGeoShapeEntity2D)
		{
			AIMXML::_altova_typeinfo_indices geoTypeIndex = this->getShapeNodeType(pGeoShapeEntity2D);
			if (geoTypeIndex != AIMXML::_altova_tif)
			{
				// NOTE: we can do this because all data is in the base classes
				CTwoDimensionGeometricShapeEntity xmlGeoShape2D = xmlParent.MarkupEntity.appendSpecial(geoTypeIndex);
				this->populateXmlNode(xmlGeoShape2D, *pGeoShapeEntity);
				this->populateXmlNode(xmlGeoShape2D, *pGeoShapeEntity2D);
			}
		}
		else if (pGeoShapeEntity3D)
		{
			AIMXML::_altova_typeinfo_indices geoTypeIndex = this->getShapeNodeType(pGeoShapeEntity3D);
			if (geoTypeIndex != AIMXML::_altova_tif)
			{
				// NOTE: we can do this because all data is in the base classes
				CThreeDimensionGeometricShapeEntity xmlGeoShape3D = xmlParent.MarkupEntity.appendSpecial(geoTypeIndex);
				this->populateXmlNode(xmlGeoShape3D, *pGeoShapeEntity);
				this->populateXmlNode(xmlGeoShape3D, *pGeoShapeEntity3D);
			}
		}
		else assert(false); // Unknown Geo Shape type
	}
	else
		assert(false);
}

AIMXML::_altova_typeinfo_indices XmlModelInternal::getShapeNodeType(const TwoDimensionGeometricShapeEntity* pGeoShapeEntity2D)
{
	AIMXML::_altova_typeinfo_indices retVal = AIMXML::_altova_tif;

	if (pGeoShapeEntity2D)
	{
		switch(pGeoShapeEntity2D->GetShapeType())
		{
		case TwoDimensionGeometricShapeEntity::Point_2D:
			retVal = AIMXML::_altova_ti_altova_CTwoDimensionPoint;
			break;
		case TwoDimensionGeometricShapeEntity::Circle_2D:
			retVal = AIMXML::_altova_ti_altova_CTwoDimensionCircle;
			break;
		case TwoDimensionGeometricShapeEntity::Ellipse_2D:
			retVal = AIMXML::_altova_ti_altova_CTwoDimensionEllipse;
			break;
		case TwoDimensionGeometricShapeEntity::Polyline_2D:
			retVal = AIMXML::_altova_ti_altova_CTwoDimensionPolyline;
			break;
		case TwoDimensionGeometricShapeEntity::Multipoint_2D:
			retVal = AIMXML::_altova_ti_altova_CTwoDimensionMultiPoint;
			break;
		default:
			assert(false); // unexpected shape type
		}
	}

	return retVal;
}

AIMXML::_altova_typeinfo_indices XmlModelInternal::getShapeNodeType(const ThreeDimensionGeometricShapeEntity* pGeoShapeEntity3D)
{
	AIMXML::_altova_typeinfo_indices retVal = AIMXML::_altova_tif;

	if (pGeoShapeEntity3D)
	{
		switch(pGeoShapeEntity3D->GetShapeType())
		{
		case ThreeDimensionGeometricShapeEntity::Point_3D:
			retVal = AIMXML::_altova_ti_altova_CThreeDimensionPoint;
			break;
		case ThreeDimensionGeometricShapeEntity::Ellipse_3D:
			retVal = AIMXML::_altova_ti_altova_CThreeDimensionEllipse;
			break;
		case ThreeDimensionGeometricShapeEntity::Ellipsoid_3D:
			retVal = AIMXML::_altova_ti_altova_CThreeDimensionEllipsoid;
			break;
		case ThreeDimensionGeometricShapeEntity::Polyline_3D:
			retVal = AIMXML::_altova_ti_altova_CThreeDimensionPolyline;
			break;
		case ThreeDimensionGeometricShapeEntity::Polygon_3D:
			retVal = AIMXML::_altova_ti_altova_CThreeDimensionPolygon;
			break;
		case ThreeDimensionGeometricShapeEntity::Multipoint_3D:
			retVal = AIMXML::_altova_ti_altova_CThreeDimensionMultiPoint;
			break;
		default:
			assert(false); // unexpected shape type
		}
	}

	return retVal;
}

void XmlModelInternal::populateXmlNode(AIMXML::CTextAnnotationEntity& xmlTextAnnEntity, const TextAnnotationEntity& textAnnEntity)
{
	CREATE_II(xmlTextAnnEntity.uniqueIdentifier, textAnnEntity.GetUniqueIdentifier());
	CREATE_ST(xmlTextAnnEntity.text, textAnnEntity.GetText());
	if (!textAnnEntity.GetFont().empty())
		CREATE_ST(xmlTextAnnEntity.font, textAnnEntity.GetFont());
	if (!textAnnEntity.GetFontColor().empty())
		CREATE_ST(xmlTextAnnEntity.fontColor, textAnnEntity.GetFontColor());
	if (!textAnnEntity.GetFontEffect().empty())
		CREATE_ST(xmlTextAnnEntity.fontEffect, textAnnEntity.GetFontEffect());
	if (!textAnnEntity.GetFontSize().empty())
		CREATE_ST(xmlTextAnnEntity.fontSize, textAnnEntity.GetFontSize());
	if (!textAnnEntity.GetFontStyle().empty())
		CREATE_ST(xmlTextAnnEntity.fontStyle, textAnnEntity.GetFontStyle());
	if (!textAnnEntity.GetTextJustify().empty())
		CREATE_ST(xmlTextAnnEntity.textJustify, textAnnEntity.GetTextJustify());
	if (!textAnnEntity.GetFontOpacity().empty())
		CREATE_ST(xmlTextAnnEntity.fontOpacity, textAnnEntity.GetFontOpacity());

	if (textAnnEntity.GetGeometricShapeEntity())
	{
		const GeometricShapeEntity* pGeoShapeEntity = textAnnEntity.GetGeometricShapeEntity();
		const TwoDimensionGeometricShapeEntity* pGeoShapeEntity2D = dynamic_cast<const TwoDimensionGeometricShapeEntity*>(pGeoShapeEntity);
		const ThreeDimensionGeometricShapeEntity* pGeoShapeEntity3D = dynamic_cast<const ThreeDimensionGeometricShapeEntity*>(pGeoShapeEntity);

		assert(!pGeoShapeEntity2D || !pGeoShapeEntity3D);

		if (pGeoShapeEntity2D)
		{
			AIMXML::_altova_typeinfo_indices geoTypeIndex = this->getShapeNodeType(pGeoShapeEntity2D);
			if (geoTypeIndex != AIMXML::_altova_tif)
			{
				// NOTE: we can do this because all data is in the base classes
				CTwoDimensionGeometricShapeEntity xmlGeoShape2D = xmlTextAnnEntity.geometricShapeEntity.appendSpecial(geoTypeIndex);
				this->populateXmlNode(xmlGeoShape2D, *pGeoShapeEntity);
				this->populateXmlNode(xmlGeoShape2D, *pGeoShapeEntity2D);
			}
		}
		else if (pGeoShapeEntity3D)
		{
			AIMXML::_altova_typeinfo_indices geoTypeIndex = this->getShapeNodeType(pGeoShapeEntity3D);
			if (geoTypeIndex != AIMXML::_altova_tif)
			{
				// NOTE: we can do this because all data is in the base classes
				CThreeDimensionGeometricShapeEntity xmlGeoShape3D = xmlTextAnnEntity.geometricShapeEntity.appendSpecial(geoTypeIndex);
				this->populateXmlNode(xmlGeoShape3D, *pGeoShapeEntity);
				this->populateXmlNode(xmlGeoShape3D, *pGeoShapeEntity3D);
			}
		}
		else assert(false); // Unknown Geo Shape type
	}
}

void XmlModelInternal::populateXmlNode(AIMXML::CGeometricShapeEntity& xmlGeoShapeEntity, const GeometricShapeEntity& geoShapeEntity)
{
	CREATE_II(xmlGeoShapeEntity.uniqueIdentifier, geoShapeEntity.GetUniqueIdentifier());
	for (iso_21090::CDVector::const_iterator iter = geoShapeEntity.GetQuestionTypeCode().begin(); iter < geoShapeEntity.GetQuestionTypeCode().end(); iter++)
		CREATE_CD(xmlGeoShapeEntity.questionTypeCode, *iter);
	CREATE_INT(xmlGeoShapeEntity.shapeIdentifier, geoShapeEntity.GetShapeIdentifier());
	if (!geoShapeEntity.GetLabel().empty())
		CREATE_ST(xmlGeoShapeEntity.label, geoShapeEntity.GetLabel());
	if (!geoShapeEntity.GetDescription().empty())
		CREATE_ST(xmlGeoShapeEntity.description, geoShapeEntity.GetDescription());
	CREATE_BL(xmlGeoShapeEntity.includeFlag, geoShapeEntity.GetIncludeFlag());
	if (!geoShapeEntity.GetComment().empty())
		CREATE_ST(xmlGeoShapeEntity.comment, geoShapeEntity.GetComment());
	if (!geoShapeEntity.GetLineColor().empty())
		CREATE_ST(xmlGeoShapeEntity.lineColor, geoShapeEntity.GetLineColor());
	if (!geoShapeEntity.GetLineOpacity().empty())
		CREATE_ST(xmlGeoShapeEntity.lineOpacity, geoShapeEntity.GetLineOpacity());
	if (!geoShapeEntity.GetLineStyle().empty())
		CREATE_ST(xmlGeoShapeEntity.lineStyle, geoShapeEntity.GetLineStyle());
	if (!geoShapeEntity.GetLineThickness().empty())
		CREATE_ST(xmlGeoShapeEntity.lineThickness, geoShapeEntity.GetLineThickness());
	if (geoShapeEntity.GetQuestionIndex() != -1)
		CREATE_INT(xmlGeoShapeEntity.questionIndex, geoShapeEntity.GetQuestionIndex());
	if (geoShapeEntity.GetInterpolationMethod())
		CREATE_CD(xmlGeoShapeEntity.interpolationMethod, *geoShapeEntity.GetInterpolationMethod());
}

void XmlModelInternal::populateXmlNode(AIMXML::CTwoDimensionGeometricShapeEntity& xmlGeoShapeEntity2D, const TwoDimensionGeometricShapeEntity& geoShapeEntity2D)
{
	if (geoShapeEntity2D.GetImageReferenceUid())
		CREATE_II(xmlGeoShapeEntity2D.imageReferenceUid, *geoShapeEntity2D.GetImageReferenceUid());
	if (geoShapeEntity2D.GetReferencedFrameNumber() != -1)
		CREATE_INT(xmlGeoShapeEntity2D.referencedFrameNumber, geoShapeEntity2D.GetReferencedFrameNumber());
	if (!geoShapeEntity2D.GetUri().empty())
		CREATE_ST(xmlGeoShapeEntity2D.uri, geoShapeEntity2D.GetUri());

	CtwoDimensionSpatialCoordinateCollectionType xmlSpatialCoords = xmlGeoShapeEntity2D.twoDimensionSpatialCoordinateCollection.append();
	const TwoDimensionSpatialCoordinateVector& spatialCoords = geoShapeEntity2D.GetTwoDimensionSpatialCoordinateCollection();
	for (TwoDimensionSpatialCoordinateVector::const_iterator iter = spatialCoords.begin(); iter < spatialCoords.end(); iter++)
	{
		CTwoDimensionSpatialCoordinate xmlSpatialCoord = xmlSpatialCoords.TwoDimensionSpatialCoordinate.append();
		CREATE_INT(xmlSpatialCoord.coordinateIndex, (int)iter->GetCoordinateIndex());
		CREATE_REAL(xmlSpatialCoord.x, iter->GetX());
		CREATE_REAL(xmlSpatialCoord.y, iter->GetY());
	}
}

void XmlModelInternal::populateXmlNode(AIMXML::CThreeDimensionGeometricShapeEntity& xmlGeoShapeEntity3D, const ThreeDimensionGeometricShapeEntity& geoShapeEntity3D)
{
	if (geoShapeEntity3D.GetFrameOfReferenceUid())
		CREATE_II(xmlGeoShapeEntity3D.frameOfReferenceUid, *geoShapeEntity3D.GetFrameOfReferenceUid());
	if (geoShapeEntity3D.GetFiducialUid())
		CREATE_II(xmlGeoShapeEntity3D.fiducialUid, *geoShapeEntity3D.GetFiducialUid());

	CthreeDimensionSpatialCoordinateCollectionType xmlSpatialCoords = xmlGeoShapeEntity3D.threeDimensionSpatialCoordinateCollection.append();
	const ThreeDimensionSpatialCoordinateVector& spatialCoords = geoShapeEntity3D.GetThreeDimensionSpatialCoordinateCollection();
	for (ThreeDimensionSpatialCoordinateVector::const_iterator iter = spatialCoords.begin(); iter < spatialCoords.end(); iter++)
	{
		CThreeDimensionSpatialCoordinate xmlSpatialCoord = xmlSpatialCoords.ThreeDimensionSpatialCoordinate.append();
		CREATE_INT(xmlSpatialCoord.coordinateIndex, iter->GetCoordinateIndex());
		CREATE_REAL(xmlSpatialCoord.x, iter->GetX());
		CREATE_REAL(xmlSpatialCoord.y, iter->GetY());
		CREATE_REAL(xmlSpatialCoord.z, iter->GetZ());
	}	
}

void XmlModelInternal::createXmlNode(AIMXML::CimageAnnotationStatementCollectionType& xmlParent, const AnnotationStatement* pAnnStmt)
{
	if (!pAnnStmt)
		return;

	AIMXML::_altova_typeinfo_indices stmtTypeIdx = this->getAnnotationStatementNodeType(pAnnStmt);

	if (stmtTypeIdx != AIMXML::_altova_tif)
	{
		CAnnotationStatement xmlStmt = xmlParent.ImageAnnotationStatement.appendSpecial(stmtTypeIdx);
		CREATE_II(xmlStmt.subjectUniqueIdentifier, pAnnStmt->GetSubjectUniqueIdentifier());
		CREATE_II(xmlStmt.objectUniqueIdentifier, pAnnStmt->GetObjectUniqueIdentifier());
	}
	else
		assert(false); // failed to find proper XML type for the statement
}

void XmlModelInternal::createXmlNode(AIMXML::CannotationOfAnnotationStatementCollectionType& xmlParent, const AnnotationStatement* pAnnStmt)
{
	if (!pAnnStmt)
		return;

	AIMXML::_altova_typeinfo_indices stmtTypeIdx = this->getAnnotationStatementNodeType(pAnnStmt);

	if (stmtTypeIdx != AIMXML::_altova_tif)
	{
		CAnnotationStatement xmlStmt = xmlParent.AnnotationOfAnnotationStatement.appendSpecial(stmtTypeIdx);
		CREATE_II(xmlStmt.subjectUniqueIdentifier, pAnnStmt->GetSubjectUniqueIdentifier());
		CREATE_II(xmlStmt.objectUniqueIdentifier, pAnnStmt->GetObjectUniqueIdentifier());
	}
	else
		assert(false); // failed to find proper XML type for the statement
}

#define RETURN_MATCHED_TYPE(typeName, ptrObj) if (typeid(*ptrObj) == typeid(typeName)) return AIMXML::_altova_ti_altova_C##typeName;
AIMXML::_altova_typeinfo_indices XmlModelInternal::getAnnotationStatementNodeType(const AnnotationStatement* pAnnStmt)
{
	// Annotation Statements
	RETURN_MATCHED_TYPE(AnnotationEntityHasPerformedTaskContextEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(AnnotationEntityHasPlannedTaskContextEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(CalculationEntityReferencesCalculationEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(CalculationEntityUsesCalculationEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(ImagingObservationEntityHasCalculationEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(ImagingObservationEntityIsFoundInImagingPhysicalEntityStatement , pAnnStmt)
	RETURN_MATCHED_TYPE(ImagingPhysicalEntityHasCalculationEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(ImagingPhysicalEntityHasImagingObservationEntityStatement, pAnnStmt)

	// Image Annotation Statements
	RETURN_MATCHED_TYPE(DicomImageReferenceEntityHasCalculationEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(DicomImageReferenceEntityHasImagingObservationEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(DicomImageReferenceEntityHasImagingPhysicalEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(DicomSegmentationEntityHasImagingObservationEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(GeneralLesionObservationEntityHasImagingPhysicalEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(ImageAnnotationHasCalculationEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(ImageAnnotationHasChildImageAnnotationStatement, pAnnStmt)
	
	RETURN_MATCHED_TYPE(ImageAnnotationHasDicomImageReferenceEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(ImageAnnotationHasDicomSegmentationEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(ImageAnnotationHasGeneralLesionObservationEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(ImageAnnotationHasImagingObservationEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(ImageAnnotationHasImagingPhysicalEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(ImageAnnotationHasInferenceEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(ImageAnnotationHasTextAnnotationEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(ImageAnnotationHasThreeDimensionGeometricShapeEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(ImageAnnotationHasTwoDimensionGeometricShapeEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(ImageAnnotationHasTimePointLesionObservationEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(ImageAnnotationHasUriImageReferenceEntityStatement, pAnnStmt)
	
	RETURN_MATCHED_TYPE(ImagingObservationEntityIsIdentifiedByThreeDimensionGeometricShapeEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(ImagingObservationEntityIsIdentifiedByTwoDimensionGeometricShapeEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(ImagingObservationEntityIsIdentifiedByTextAnnotationEntityStatement, pAnnStmt)
	
	RETURN_MATCHED_TYPE(ImagingPhysicalEntityHasThreeDimensionGeometricShapeEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(ImagingPhysicalEntityHasTwoDimensionGeometricShapeEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(ImagingPhysicalEntityHasTextAnnotationEntityStatement, pAnnStmt)
	
	RETURN_MATCHED_TYPE(ThreeDimensionGeometricShapeEntityIsComprisedOfThreeDimensionGeometricShapeEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(ThreeDimensionGeometricShapeEntityExcludesThreeDimensionGeometricShapeEntityStatement, pAnnStmt)
	
	RETURN_MATCHED_TYPE(TimePointLesionObservationEntityHasImagingPhysicalEntityStatement, pAnnStmt)

	RETURN_MATCHED_TYPE(TwoDimensionGeometricShapeEntityIsComprisedOfTwoDimensionGeometricShapeEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(TwoDimensionGeometricShapeEntityExcludesTwoDimensionGeometricShapeEntityStatement, pAnnStmt)
	
	RETURN_MATCHED_TYPE(UriImageReferenceEntityHasImagingObservationEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(UriImageReferenceEntityHasImagingPhysicalEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(UriImageReferenceEntityHasCalculationEntityStatement, pAnnStmt)

	// Annotation of Annotation Statements
	RETURN_MATCHED_TYPE(AnnotationOfAnnotationHasAnnotationOfAnnotationStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(AnnotationOfAnnotationHasAnnotationRoleEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(AnnotationOfAnnotationHasCalculationEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(AnnotationOfAnnotationHasGeneralLesionObservationEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(AnnotationOfAnnotationHasImageAnnotationStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(AnnotationOfAnnotationHasImagingObservationEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(AnnotationOfAnnotationHasImagingPhysicalEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(AnnotationOfAnnotationHasInferenceEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(AnnotationOfAnnotationHasTimePointLesionObservationEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(AnnotationOfAnnotationIsComparedWithAnnotationOfAnnotationStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(AnnotationOfAnnotationIsComparedWithImageAnnotationStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(CalculationEntityIsComparedWithCalculationEntityStatement, pAnnStmt)

	RETURN_MATCHED_TYPE(ImageAnnotationHasAnnotationRoleEntityStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(ImageAnnotationIsComparedWithImageAnnotationStatement, pAnnStmt)
	RETURN_MATCHED_TYPE(ImageAnnotationIsComparedWithAnnotationOfAnnotationStatement, pAnnStmt)

	return AIMXML::_altova_tif;
}

void XmlModelInternal::createXmlNode(AIMXML::CimageReferenceEntityCollectionType& xmlParent, const ImageReferenceEntity* pImageRefEntity)
{
	if (!pImageRefEntity)
		return;

	const DicomImageReferenceEntity* pDicomImageRefEntity = dynamic_cast<const DicomImageReferenceEntity*>(pImageRefEntity);
	const UriImageReferenceEntity* pUriImageRefEntity = dynamic_cast<const UriImageReferenceEntity*>(pImageRefEntity);

	assert(!pDicomImageRefEntity || !pUriImageRefEntity);

	if (pDicomImageRefEntity)
	{
		CDicomImageReferenceEntity xmlImageRefEntity = xmlParent.ImageReferenceEntity.appendSpecial(AIMXML::_altova_ti_altova_CDicomImageReferenceEntity);
		CREATE_II(xmlImageRefEntity.uniqueIdentifier, pDicomImageRefEntity->GetUniqueIdentifier());
		CImageStudy xmlImageStudy = xmlImageRefEntity.imageStudy.append();
		this->populateXmlNode(xmlImageStudy, pDicomImageRefEntity->GetImageStudy());
	}
	else if (pUriImageRefEntity)
	{
		CUriImageReferenceEntity xmlUriImageRefEntity = xmlParent.ImageReferenceEntity.appendSpecial(AIMXML::_altova_ti_altova_CUriImageReferenceEntity);
		CREATE_II(xmlUriImageRefEntity.uniqueIdentifier, pUriImageRefEntity->GetUniqueIdentifier());
		CREATE_ST(xmlUriImageRefEntity.uri, pUriImageRefEntity->GetUri());
		CREATE_ST(xmlUriImageRefEntity.mimeType, pUriImageRefEntity->GetMimeType());
	}
	else
		assert(false);
}

void XmlModelInternal::populateXmlNode(AIMXML::CImageStudy& xmlImageStudy, const ImageStudy& imageStudy)
{
	CREATE_II(xmlImageStudy.instanceUid, imageStudy.GetInstanceUid());
	CREATE_TS(xmlImageStudy.startDate, imageStudy.GetStartDate());
	CREATE_TS(xmlImageStudy.startTime, imageStudy.GetStartTime());
	if (!imageStudy.GetProceduDescription().empty())
		CREATE_ST(xmlImageStudy.procedureDescription, imageStudy.GetProceduDescription());
	CImageSeries xmlImageSeries = xmlImageStudy.imageSeries.append();
	this->populateXmlNode(xmlImageSeries, imageStudy.GetImageSeries());

	const ReferencedDicomObjectVector& refDicomObjects = imageStudy.GetReferencedDicomObjectCollection();
	if (refDicomObjects.size() > 0)
	{
		CreferencedDicomObjectCollectionType xmlRefDicomObjects = xmlImageStudy.referencedDicomObjectCollection.append();
		for (ReferencedDicomObjectVector::const_iterator iter = refDicomObjects.begin(); iter < refDicomObjects.end(); iter++)
			this->createXmlNode(xmlRefDicomObjects, *iter);
	}
}

void XmlModelInternal::populateXmlNode(AIMXML::CImageSeries& xmlImageSeries, const ImageSeries& imageSeries)
{
	CREATE_II(xmlImageSeries.instanceUid, imageSeries.GetInstanceUid());
	CREATE_CD(xmlImageSeries.modality, imageSeries.GetModality());

	const ImageVector& images = imageSeries.GetImageCollection();
	CimageCollectionType xmlImages = xmlImageSeries.imageCollection.append();
	for (ImageVector::const_iterator iter = images.begin(); iter < images.end(); iter++)
		this->createXmlNode(xmlImages, *iter);
}

void XmlModelInternal::createXmlNode(AIMXML::CimageCollectionType& xmlParent, const Image& image)
{
	CImage xmlImage = xmlParent.Image.append();

	CREATE_II(xmlImage.sopClassUid, image.GetSopClassUid());
	CREATE_II(xmlImage.sopInstanceUid, image.GetSopInstanceUid());

	const ImagePlane* pImagePlane = image.GetImagePlane();
	if (pImagePlane)
	{
		CImagePlane xmlImagePlane = xmlImage.imagePlane.append();

		if (pImagePlane->GetRowImageOrientationX())
			CREATE_REAL(xmlImagePlane.rowImageOrientationX, *pImagePlane->GetRowImageOrientationX());
		if (pImagePlane->GetRowImageOrientationY())
			CREATE_REAL(xmlImagePlane.rowImageOrientationY, *pImagePlane->GetRowImageOrientationY());
		if (pImagePlane->GetRowImageOrientationZ())
			CREATE_REAL(xmlImagePlane.rowImageOrientationZ, *pImagePlane->GetRowImageOrientationZ());
		if (pImagePlane->GetColumnImageOrientationX())
			CREATE_REAL(xmlImagePlane.columnImageOrientationX, *pImagePlane->GetColumnImageOrientationX());
		if (pImagePlane->GetColumnImageOrientationY())
			CREATE_REAL(xmlImagePlane.columnImageOrientationY, *pImagePlane->GetColumnImageOrientationY());
		if (pImagePlane->GetColumnImageOrientationZ())
			CREATE_REAL(xmlImagePlane.columnImageOrientationZ, *pImagePlane->GetColumnImageOrientationZ());
		if (pImagePlane->GetVerticalPixelSpacing())
			CREATE_REAL(xmlImagePlane.verticalPixelSpacing, *pImagePlane->GetVerticalPixelSpacing());
		if (pImagePlane->GetHorizontalPixelSpacing())
			CREATE_REAL(xmlImagePlane.horizontalPixelSpacing, *pImagePlane->GetHorizontalPixelSpacing());
		if (pImagePlane->GetSliceThickness())
			CREATE_REAL(xmlImagePlane.sliceThickness, *pImagePlane->GetSliceThickness());
		if (pImagePlane->GetImagePositionX())
			CREATE_REAL(xmlImagePlane.imagePositionX, *pImagePlane->GetImagePositionX());
		if (pImagePlane->GetImagePositionY())
			CREATE_REAL(xmlImagePlane.imagePositionY, *pImagePlane->GetImagePositionY());
		if (pImagePlane->GetImagePositionZ())
			CREATE_REAL(xmlImagePlane.imagePositionZ, *pImagePlane->GetImagePositionZ());
	}
	const GeneralImage* pGenImage = image.GetGeneralImage();
	if (pGenImage)
	{
		CGeneralImage xmlGenImage = xmlImage.generalImage.append();

		if (!pGenImage->GetPatientOrientationColumn().empty())
			CREATE_ST(xmlGenImage.patientOrientationColumn, pGenImage->GetPatientOrientationColumn());
		if (!pGenImage->GetPatientOrientationRow().empty())
			CREATE_ST(xmlGenImage.patientOrientationRow, pGenImage->GetPatientOrientationRow());
	}
}

void XmlModelInternal::createXmlNode(AIMXML::CreferencedDicomObjectCollectionType& xmlParent, const ReferencedDicomObject& refDicomObj)
{
	CReferencedDicomObject xmlRefDicomObj = xmlParent.ReferencedDicomObject.append();

	CREATE_CD(xmlRefDicomObj.modality, refDicomObj.GetModality());
	CREATE_II(xmlRefDicomObj.sopInstanceUid, refDicomObj.GetSopInstanceUid());
}

void XmlModelInternal::populateXmlNode(AIMXML::CAdjudicationObservation& xmlAdjudicationObs, const AdjudicationObservation& adjudicationObs)
{
	CREATE_II(xmlAdjudicationObs.observationUid, adjudicationObs.GetObservationUid());
	CREATE_CD(xmlAdjudicationObs.observationScope, adjudicationObs.GetObservationScope());
	if (adjudicationObs.GetPersonObserversRoleInThisProcedure())
		CREATE_CD(xmlAdjudicationObs.personObserversRoleInThisProcedure, *adjudicationObs.GetPersonObserversRoleInThisProcedure());
	for (std::vector<std::string>::const_iterator iter = adjudicationObs.GetIdentifierWithinAcceptedPersonObserversRole().begin(); iter < adjudicationObs.GetIdentifierWithinAcceptedPersonObserversRole().end(); iter++)
		CREATE_ST(xmlAdjudicationObs.identifierWithinAcceptedPersonObserversRole, *iter);
	for (std::vector<std::string>::const_iterator iter = adjudicationObs.GetIdentifierWithinRejectedPersonObserversRole().begin(); iter < adjudicationObs.GetIdentifierWithinRejectedPersonObserversRole().end(); iter++)
		CREATE_ST(xmlAdjudicationObs.identifierWithinRejectedPersonObserversRole, *iter);
	CREATE_CD(xmlAdjudicationObs.reasonForChoice, adjudicationObs.GetReasonForChoice());
	if (adjudicationObs.GetReasonForDiscordance())
		CREATE_CD(xmlAdjudicationObs.reasonForDiscordance, *adjudicationObs.GetReasonForDiscordance());
	if (!adjudicationObs.GetComment().empty())
		CREATE_ST(xmlAdjudicationObs.comment, adjudicationObs.GetComment());
	CREATE_BL(xmlAdjudicationObs.imageQualityIssuesDiscordance, adjudicationObs.GetImageQualityIssuesDiscordance());
}

void XmlModelInternal::populateXmlNode(AIMXML::CUser& xmlParent, const User& user)
{
	CREATE_ST(xmlParent.name, user.GetName())
	CREATE_ST(xmlParent.loginName, user.GetLoginName())
	if (!user.GetRoleInTrial().empty())
		CREATE_ST(xmlParent.roleInTrial, user.GetRoleInTrial())
	if (user.GetNumberWithinRoleOfClinicalTrial() != -1)
		CREATE_INT(xmlParent.numberWithinRoleOfClinicalTrial, user.GetNumberWithinRoleOfClinicalTrial())
}

void XmlModelInternal::populateXmlNode(AIMXML::CEquipment& xmlParent, const Equipment& equipment)
{
	CREATE_ST(xmlParent.manufacturerName, equipment.GetManufacturerName())
	if (!equipment.GetManufacturerModelName().empty())
		CREATE_ST(xmlParent.manufacturerModelName, equipment.GetManufacturerModelName())
	if (!equipment.GetDeviceSerialNumber().empty())
		CREATE_ST(xmlParent.deviceSerialNumber, equipment.GetDeviceSerialNumber())
	if (!equipment.GetSoftwareVersion().empty())
		CREATE_ST(xmlParent.softwareVersion, equipment.GetSoftwareVersion())
}

void XmlModelInternal::populateXmlNode(AIMXML::CPerson& xmlParent, const Person& person)
{
	CREATE_ST(xmlParent.name, person.GetName());
	CREATE_ST(xmlParent.id, person.GetId());
	if (!person.GetBirthDate().IsEmpty())
		CREATE_TS(xmlParent.birthDate, person.GetBirthDate());
	if (!person.GetSex().empty())
		CREATE_ST(xmlParent.sex, person.GetSex());
	if (!person.GetEthnicGroup().empty())
		CREATE_ST(xmlParent.ethnicGroup, person.GetEthnicGroup());
}

/*
* ISO21090 Helpers
*/
void XmlModelInternal::populateXmlNode(AIMXML::iso::CST& isoStr, const std::string& strVal)
{
	isoStr.value2 = _T(strVal);
}

void XmlModelInternal::populateXmlNode(AIMXML::iso::CBL& isoBool, const bool boolVal)
{
	isoBool.value2 = boolVal;
}

void XmlModelInternal::populateXmlNode(AIMXML::iso::CINT& isoInt, const int intVal)
{
	isoInt.value2 = intVal;
}

void XmlModelInternal::populateXmlNode(AIMXML::iso::CREAL& isoReal, const double dblVal)
{
	isoReal.value2 = dblVal;
}

void XmlModelInternal::populateXmlNode(AIMXML::iso::CTS& isoTs, const aim_lib::DateTime& dtVal)
{
	isoTs.value2 = _T(dtVal.GetDicomFormatedDateTime());
}

void XmlModelInternal::populateXmlNode(AIMXML::iso::CTS& isoTs, const aim_lib::Date& dateVal)
{
	isoTs.value2 = _T(dateVal.GetDicomFormatedDate());
}

void XmlModelInternal::populateXmlNode(AIMXML::iso::CTS& isoTs, const aim_lib::Time& timeVal)
{
	isoTs.value2 = _T(timeVal.GetDicomFormatedTime());
}

void XmlModelInternal::populateXmlNode(AIMXML::iso::CCD& isoCd, const iso_21090::CD& cdVal)
{
	isoCd.code				= _T(cdVal.GetCodeValue());
	isoCd.codeSystemName	= _T(cdVal.GetCodingSchemeDesignator());
	CST xmlCodeMeaning		= isoCd.displayName.append();
	xmlCodeMeaning.value2	= _T(cdVal.GetCodeMeaning());
	if (!cdVal.GetCodingSchemeVersion().empty())
		isoCd.codeSystemVersion = _T(cdVal.GetCodingSchemeVersion());
}

void XmlModelInternal::populateXmlNode(AIMXML::iso::CII& isoII, const iso_21090::II& iiVal)
{
	isoII.root = _T(iiVal.toString());
}
