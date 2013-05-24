/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"
#include <limits.h>

#include "../external/CD.h"
#include "../external/II.h"
#include "../AimHeaders.h"

#include "ModelValidator.h"

#include "../AIMUtil.h"
//#include "../JniProtegeBridge/JniProtegeBridge.h"

#include <cctype>
//#include <sstream>

using namespace aim_lib;

#define RETURN_WITH_ERROR(errMsg) { if (errMsg != "") _errors.push_back(errMsg); return false; }
#define RETURN_IF_NOT_VALID1(x, allowDefaults, errMsg) if(!isValid(x, allowDefaults)) RETURN_WITH_ERROR(errMsg)
//#define RETURN_IF_NOT_VALID2(x, errMsg) if(!this.isValid(x)) RETURN_WITH_ERROR(errMsg)

//#define RETURN_IF_INT_RANGE_NOT_VALID(val, minVal, maxVal, paramName) if (val < minVal || val > maxVal) RETURN_WITH_ERROR(std::string(paramName).append(" value has must be between ").append(AIMUtil::IntToString(minVal)).append(" and ").append(AIMUtil::IntToString(maxVal)))
//#define RETURN_IF_DOUBLE_RANGE_NOT_VALID(val, minVal, maxVal, paramName) if (val < minVal || val > maxVal) RETURN_WITH_ERROR(std::string(paramName).append(" value has must be between ").append(AIMUtil::DoubleToString(minVal)).append(" and ").append(AIMUtil::DoubleToString(maxVal)))
#define RETURN_IF_RANGE_NOT_VALID(val, minVal, maxVal, paramName) if (val < minVal || val > maxVal) { std::stringstream errStream; errStream << paramName << " value must be between " << minVal << " and " << maxVal; std::string errMsg = errStream.str(); RETURN_WITH_ERROR(errMsg) }
#define RETURN_IF_STR_EMPTY(testStr, paramName) if ((testStr).empty()) RETURN_WITH_ERROR(std::string(paramName).append(" is empty"))
//#define RETURN_IF_NULL(testVal, paramName) if (testVal == NULL) RETURN_WITH_ERROR(std::string(paramName).append(" is missing"))
#define RETURN_IF_STR_LENGTH(testStr, minLen, maxLen, paramName) if (testStr.length() < minLen || testStr.length() > maxLen) { std::stringstream errStream; errStream << paramName << " value must be between " << minLen << " and " << maxLen << " in length"; std::string errMsg = errStream.str(); RETURN_WITH_ERROR(errMsg) }
//#define RETURN_IF_STR_LENGTH(str, minLen, maxLen, paramName) if (str.length() < minLen || str.length() > maxLen) RETURN_WITH_ERROR(std::string(paramName).append(" value has must be between ").append(AIMUtil::IntToString(minLen)).append(" and ").append(AIMUtil::IntToString(maxLen)).append(" in length"))
#define RETURN_IF_UID_NOT_VALID(uid, paramName) if (!isUIDValid(uid)) { std::stringstream errStream; errStream << paramName << " value is not a valid UID"; std::string errMsg = errStream.str(); RETURN_WITH_ERROR(errMsg) }


ModelValidator::ModelValidator(void)
{
}

ModelValidator::~ModelValidator(void)
{
}

bool ModelValidator::isValid(const AnnotationCollection& annotationColl, bool allowDefaults/* = false*/)
{
	if (annotationColl.GetAimVersion() != AIMv4_0)
		RETURN_WITH_ERROR("AIM Version is not 4.0");
	RETURN_IF_NOT_VALID1(annotationColl.GetUniqueIdentifier(), false, "Annotation Collection Unique Identifier");
	RETURN_IF_NOT_VALID1(annotationColl.GetDateTime(), false, "Annotation Collection DateTime is invalid");

	if (!allowDefaults)
		RETURN_IF_STR_EMPTY(annotationColl.GetDescription(), "Annotation Collection Description");

	if (annotationColl.GetEquipment())
		RETURN_IF_NOT_VALID1(*annotationColl.GetEquipment(), allowDefaults, "Equipment is invalid");

	if (annotationColl.GetUser())
		RETURN_IF_NOT_VALID1(*annotationColl.GetUser(), allowDefaults, "User is invalid");

	if (annotationColl.GetAnnotationCollectionType() == AnnotationCollection::ACT_ImageAnnotationCollection)
		return isValid(dynamic_cast<const ImageAnnotationCollection&>(annotationColl), allowDefaults);
	else if (annotationColl.GetAnnotationCollectionType() == AnnotationCollection::ACT_AnnotationOfAnnotationCollection)
		return isValid(dynamic_cast<const AnnotationOfAnnotationCollection&>(annotationColl), allowDefaults);

	RETURN_WITH_ERROR("Unknown Annotation Collection Type");
	//return true;
}

bool ModelValidator::isValid(const ImageAnnotationCollection& imgAnnotationColl, bool allowDefaults/* = false*/)
{
	if (imgAnnotationColl.GetImageAnnotations().size() == 0)
		RETURN_WITH_ERROR("At least one Image Annotation must exist in the Image Annotation Collection");

	if (imgAnnotationColl.GetPerson())
		RETURN_IF_NOT_VALID1(*imgAnnotationColl.GetPerson(), allowDefaults, "Person is invalid");

	for (ImageAnnotationVector::const_iterator iter = imgAnnotationColl.GetImageAnnotations().begin();
		iter < imgAnnotationColl.GetImageAnnotations().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Image Annotation instance is invalid");

	return true;
}

bool ModelValidator::isValid(const AnnotationOfAnnotationCollection& annOfAnnotationColl, bool allowDefaults/* = false*/)
{
	if (annOfAnnotationColl.GetAnnotationOfAnnotations().size() == 0)
		RETURN_WITH_ERROR("At least one Annotation of Annotations must exist in the Annotation of Annotations Collection");

	for (AnnotationOfAnnotationVector::const_iterator iter = annOfAnnotationColl.GetAnnotationOfAnnotations().begin();
		iter < annOfAnnotationColl.GetAnnotationOfAnnotations().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Annotation Of Annotation instance is invalid");

	return true;
}

bool ModelValidator::isValid(const ImageAnnotation& imgAnnotation, bool allowDefaults/* = false*/)
{
	RETURN_IF_NOT_VALID1((const AnnotationEntity&)imgAnnotation, allowDefaults, "Annotation Entity is invalid");

	for (ImageReferenceEntityPtrVector::const_iterator iter = imgAnnotation.GetImageReferenceEntityCollection().begin();
		iter < imgAnnotation.GetImageReferenceEntityCollection().end(); iter++)
	{
		if (*iter)
			RETURN_IF_NOT_VALID1(**iter, allowDefaults, "Image Reference Entity is invalid");
	}

	for (SegmentationEntityPtrVector::const_iterator iter = imgAnnotation.GetSegmentationEntityCollection().begin();
		iter < imgAnnotation.GetSegmentationEntityCollection().end(); iter++)
	{
		if (*iter)
			RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Segmentation Entity instance is invalid");
	}

	for (MarkupEntityPtrVector::const_iterator iter = imgAnnotation.GetMarkupEntityCollection().begin();
		iter < imgAnnotation.GetMarkupEntityCollection().end(); iter++)
	{
		if (*iter)
			RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Markup Entity is invalid");
	}

	for (ImageAnnotationStatementPtrVector::const_iterator iter = imgAnnotation.GetImageAnnotationStatementCollection().begin();
		iter < imgAnnotation.GetImageAnnotationStatementCollection().end(); iter++)
	{
		if (*iter)
			RETURN_IF_NOT_VALID1(**iter, allowDefaults, "Image Annotation Statement is invalid");
	}

	return true;
}

bool ModelValidator::isValid(const AnnotationOfAnnotation& annOfAnnotation, bool allowDefaults/* = false*/)
{
	RETURN_IF_NOT_VALID1((const AnnotationEntity&)annOfAnnotation, allowDefaults, "Annotation Entity is invalid");

	if (annOfAnnotation.GetAdjudicationObservation())
		RETURN_IF_NOT_VALID1(*annOfAnnotation.GetAdjudicationObservation(), allowDefaults, "Adjudication Observation is invalid");

	for (AnnotationOfAnnotationStatementPtrVector::const_iterator iter = annOfAnnotation.GetAnnotationOfAnnotationStatementCollection().begin();
		iter < annOfAnnotation.GetAnnotationOfAnnotationStatementCollection().end(); iter++)
	{
		if (*iter)
			RETURN_IF_NOT_VALID1(**iter, allowDefaults, "Annotation Of Annotation Statement is invalid");
	}

	return true;
}

bool ModelValidator::isValid(const AnnotationEntity& annotationEntity, bool allowDefaults/* = false*/)
{
	RETURN_IF_NOT_VALID1(annotationEntity.GetUniqueIdentifier(), false, "Annotation Unique Identifier is invalid");
	RETURN_IF_NOT_VALID1(annotationEntity.GetTypeCode(), false, "Annotation Type Code is invalid");
	RETURN_IF_STR_EMPTY(annotationEntity.GetName(), "Annotation Name");
	RETURN_IF_NOT_VALID1(annotationEntity.GetDateTime(), false, "Annotation DateTime is invalid");

	if (!allowDefaults)
	{
		RETURN_IF_STR_EMPTY(annotationEntity.GetComment(), "Annotation Comment");
		if (!annotationEntity.GetTemplateUid())
			RETURN_WITH_ERROR("Template UID is missing");
		if (!annotationEntity.GetPrecedentReferencedAnnotationUid())
			RETURN_WITH_ERROR("Precedent Referenced Annotation UID is missing");
	}

	if (annotationEntity.GetTemplateUid())
		RETURN_IF_NOT_VALID1(*annotationEntity.GetTemplateUid(), allowDefaults, "Template UID is invalid");

	if (annotationEntity.GetPrecedentReferencedAnnotationUid())
		RETURN_IF_NOT_VALID1(*annotationEntity.GetPrecedentReferencedAnnotationUid(), allowDefaults, "Precedent Referenced Annotation UID is invalid");

	for (CalculationEntityVector::const_iterator iter = annotationEntity.GetCalculationEntityCollection().begin(); iter < annotationEntity.GetCalculationEntityCollection().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Calculation Entity is invalid");

	for (ImagingPhysicalEntityVector::const_iterator iter = annotationEntity.GetImagingPhysicalEntityCollection().begin(); iter < annotationEntity.GetImagingPhysicalEntityCollection().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Imaging Physical Entity is invalid");

	for (ImagingObservationEntityVector::const_iterator iter = annotationEntity.GetImagingObservationEntityCollection().begin(); iter < annotationEntity.GetImagingObservationEntityCollection().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Imaging Observation Entity is invalid");

	for(InferenceEntityVector::const_iterator iter = annotationEntity.GetInferenceEntityCollection().begin();
		iter < annotationEntity.GetInferenceEntityCollection().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Inference Entity is invalid");

	for (AnnotationRoleEntityVector::const_iterator iter = annotationEntity.GetAnnotationRoleEntityCollection().begin(); iter < annotationEntity.GetAnnotationRoleEntityCollection().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Annotation Role Entity is invalid");

	for (TaskContextEntityVector::const_iterator iter = annotationEntity.GetTaskContextEntityCollection().begin(); iter < annotationEntity.GetTaskContextEntityCollection().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Task Context Entity is invalid");

	for (LesionObservationEntityPtrVector::const_iterator iter = annotationEntity.GetLesionObservationEntityCollection().begin(); iter < annotationEntity.GetLesionObservationEntityCollection().end(); iter++)
		if (*iter)
			RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Lesion Observation Entity is invalid");

	for (AuditTrailVector::const_iterator iter = annotationEntity.GetAuditTrailCollection().begin(); iter < annotationEntity.GetAuditTrailCollection().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Audit Trail instance is invalid");

	return true;
}

bool ModelValidator::isValid(const ImagingPhysicalEntity& imagingPhysEntity, bool allowDefaults/* = false*/)
{
	RETURN_IF_NOT_VALID1(imagingPhysEntity.GetUniqueIdentifier(), false, "Unique Identifier is invalid");
	RETURN_IF_NOT_VALID1(imagingPhysEntity.GetTypeCode(), false, "Type Code is invalid");

	RETURN_IF_NOT_VALID1(imagingPhysEntity.GetQuestionTypeCode(), allowDefaults, "Question Type Code is invalid");

	if (!allowDefaults)
	{
		RETURN_IF_STR_EMPTY(imagingPhysEntity.GetLabel(), "Label");
		RETURN_IF_STR_EMPTY(imagingPhysEntity.GetComment(), "Comment");
		if (!imagingPhysEntity.GetIsPresent())
			RETURN_WITH_ERROR("IsPresent Flag is missing");
		if (!imagingPhysEntity.GetAnnotatorConfidence())
			RETURN_WITH_ERROR("Annotator Confidence is not set");
		if (imagingPhysEntity.GetQuestionIndex() == -1)
			RETURN_WITH_ERROR("Question Index is not set");
	}

	for (ImagingPhysicalEntityCharacteristicVector::const_iterator iter = imagingPhysEntity.GetImagingPhysicalEntityCharacteristicCollection().begin(); iter < imagingPhysEntity.GetImagingPhysicalEntityCharacteristicCollection().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Imaging Physical Entity Characteristic is invalid");

	for (ImagingObservationCharacteristicVector::const_iterator iter = imagingPhysEntity.GetImagingObservationCharacteristicCollection().begin(); iter < imagingPhysEntity.GetImagingObservationCharacteristicCollection().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Imaging Observation Entity Characteristic is invalid");

	return true;
}

bool ModelValidator::isValid(const ImagingPhysicalEntityCharacteristic& imgPhysEntityChar, bool allowDefaults/* = false*/)
{
	RETURN_IF_NOT_VALID1(imgPhysEntityChar.GetTypeCode(), false, "Type Code is invalid");

	RETURN_IF_NOT_VALID1(imgPhysEntityChar.GetQuestionTypeCode(), allowDefaults, "Question Type Code is invalid");

	if (!allowDefaults)
	{
		RETURN_IF_STR_EMPTY(imgPhysEntityChar.GetLabel(), "Label");
		RETURN_IF_STR_EMPTY(imgPhysEntityChar.GetComment(), "Comment");
		if (!imgPhysEntityChar.GetAnnotatorConfidence())
			RETURN_WITH_ERROR("Annotator Confidence is not set");
		if (imgPhysEntityChar.GetQuestionIndex() == -1)
			RETURN_WITH_ERROR("Question Index is not set");
	}

	for (CharacteristicQuantificationPtrVector::const_iterator iter = imgPhysEntityChar.GetCharacteristicQuantificationCollection().begin(); 
		iter < imgPhysEntityChar.GetCharacteristicQuantificationCollection().end(); iter++)
	{
		if (*iter)
			RETURN_IF_NOT_VALID1(**iter, allowDefaults, "Characteristic Quantification is invalid");
	}

	return true;
}

bool ModelValidator::isValid(const ImagingObservationEntity& imagingObsEntity, bool allowDefaults/* = false*/)
{
	RETURN_IF_NOT_VALID1(imagingObsEntity.GetUniqueIdentifier(), false, "Unique Identifier is invalid");
	RETURN_IF_NOT_VALID1(imagingObsEntity.GetTypeCode(), false, "Type Code is invalid");

	RETURN_IF_NOT_VALID1(imagingObsEntity.GetQuestionTypeCode(), allowDefaults, "Question Type Code is invalid");

	if (!allowDefaults)
	{
		RETURN_IF_STR_EMPTY(imagingObsEntity.GetLabel(), "Label");
		RETURN_IF_STR_EMPTY(imagingObsEntity.GetComment(), "Comment");
		if (!imagingObsEntity.GetIsPresent())
			RETURN_WITH_ERROR("IsPresent Flag is missing");
		if (!imagingObsEntity.GetAnnotatorConfidence())
			RETURN_WITH_ERROR("Annotator Confidence is not set");
		if (imagingObsEntity.GetQuestionIndex() == -1)
			RETURN_WITH_ERROR("Question Index is not set");
	}

	for (ImagingObservationCharacteristicVector::const_iterator iter = imagingObsEntity.GetImagingObservationCharacteristicCollection().begin(); iter < imagingObsEntity.GetImagingObservationCharacteristicCollection().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Imaging Observation Entity Characteristic is invalid");

	return true;
}

bool ModelValidator::isValid(const ImagingObservationCharacteristic& imagingObsChar, bool allowDefaults/* = false*/)
{
	RETURN_IF_NOT_VALID1(imagingObsChar.GetTypeCode(), false, "Type Code is invalid");

	RETURN_IF_NOT_VALID1(imagingObsChar.GetQuestionTypeCode(), allowDefaults, "Question Type Code is invalid");

	if (!allowDefaults)
	{
		RETURN_IF_STR_EMPTY(imagingObsChar.GetLabel(), "Label");
		RETURN_IF_STR_EMPTY(imagingObsChar.GetComment(), "Comment");
		if (!imagingObsChar.GetAnnotatorConfidence())
			RETURN_WITH_ERROR("Annotator Confidence is not set");
		if (imagingObsChar.GetQuestionIndex() == -1)
			RETURN_WITH_ERROR("Question Index is not set");
	}

	for (CharacteristicQuantificationPtrVector::const_iterator iter = imagingObsChar.GetCharacteristicQuantificationCollection().begin(); 
		iter < imagingObsChar.GetCharacteristicQuantificationCollection().end(); iter++)
	{
		if (*iter)
			RETURN_IF_NOT_VALID1(**iter, allowDefaults, "Characteristic Quantification is invalid");
	}

	return true;	
}

bool ModelValidator::isValid(const Equipment& equipment, bool allowDefaults/* = false*/)
{
	RETURN_IF_STR_EMPTY(equipment.GetManufacturerName(), "Equipment Manufacturer Name");

	if (!allowDefaults)
	{
		RETURN_IF_STR_EMPTY(equipment.GetManufacturerModelName(), "Equipment Manufacturer Model");
		RETURN_IF_STR_EMPTY(equipment.GetManufacturerModelName(), "Manufacturer Model Name");
		RETURN_IF_STR_EMPTY(equipment.GetSoftwareVersion(), "Software Version");
	}

	return true;
}

bool ModelValidator::isValid(const User& user, bool allowDefaults/* = false*/)
{
	RETURN_IF_STR_EMPTY(user.GetName(), "Name");
	RETURN_IF_STR_EMPTY(user.GetLoginName(), "Login Name");

	if (!allowDefaults)
	{
		RETURN_IF_STR_EMPTY(user.GetRoleInTrial(), "Role In Trial");
	}

	return true;
}

bool ModelValidator::isValid(const Person& patient, bool allowDefaults/* = false*/)
{
	RETURN_IF_STR_EMPTY(patient.GetName(), "Name");
	RETURN_IF_STR_EMPTY(patient.GetId(), "ID");

	RETURN_IF_NOT_VALID1(patient.GetBirthDate(), allowDefaults, "Birth Date is invalid");

	if (!allowDefaults)
	{
		RETURN_IF_STR_EMPTY(patient.GetSex(), "Sex");
		RETURN_IF_STR_EMPTY(patient.GetEthnicGroup(), "Ethnic Group");
	}

	return true;
}

bool ModelValidator::isValid(const InferenceEntity& inferenceEntity, bool allowDefaults/* = false*/)
{
	RETURN_IF_NOT_VALID1(inferenceEntity.GetUniqueIdentifier(), false, "Unique Identifier is invalid");
	RETURN_IF_NOT_VALID1(inferenceEntity.GetTypeCode(), false, "Type Code is invalid");

	RETURN_IF_NOT_VALID1(inferenceEntity.GetQuestionTypeCode(), allowDefaults, "Question Type Code is invalid");

	if (!allowDefaults)
	{
		RETURN_IF_STR_EMPTY(inferenceEntity.GetLabel(), "Label");
		RETURN_IF_STR_EMPTY(inferenceEntity.GetDescription(), "Description");
		RETURN_IF_STR_EMPTY(inferenceEntity.GetComment(), "Comment");
		if (!inferenceEntity.GetAnnotatorConfidence())
			RETURN_WITH_ERROR("Annotator Confidence is not set");
		if (inferenceEntity.GetQuestionIndex() == -1)
			RETURN_WITH_ERROR("Question Index is not set");
	}

	return true;
}

bool ModelValidator::isValid(const SegmentationEntity* const pSegmentationEntity, bool allowDefaults/* = false*/)
{
	if (!pSegmentationEntity)
		return true;

	RETURN_IF_NOT_VALID1(pSegmentationEntity->GetUniqueIdentifier(), false, "Unique Identifier is invalid");

	const DicomSegmentationEntity* const pDicomSegEntity = dynamic_cast<const DicomSegmentationEntity* const>(pSegmentationEntity);

	if (pDicomSegEntity)
	{
		RETURN_IF_NOT_VALID1(pDicomSegEntity->GetSopInstanceUid(), false, "SOP Instance UID");
		RETURN_IF_NOT_VALID1(pDicomSegEntity->GetSopClassUid(), false, "SOP Class UID");
		RETURN_IF_NOT_VALID1(pDicomSegEntity->GetReferencedSopInstanceUid(), false, "Referenced SOP Instance UID");
	}
	else
		RETURN_WITH_ERROR("Unexpected Segmentation Entity type");

	return true;
}

bool ModelValidator::isValid(const MarkupEntity* const pMarkupEntity, bool allowDefaults/* = false*/)
{
	if (!pMarkupEntity)
		return true;

	RETURN_IF_NOT_VALID1(pMarkupEntity->GetUniqueIdentifier(), false, "Unique Identifier is invalid");

	const GeometricShapeEntity* const pGeoShapeEntity = dynamic_cast<const GeometricShapeEntity* const>(pMarkupEntity);
	if (pGeoShapeEntity)
	{
		RETURN_IF_NOT_VALID1(pGeoShapeEntity, allowDefaults, "Geometric Shape is invalid");
	}
	else
	{
		const TextAnnotationEntity* const pTextAnnotation = dynamic_cast<const TextAnnotationEntity* const>(pMarkupEntity);
		if (pTextAnnotation)
		{
			RETURN_IF_NOT_VALID1(*pTextAnnotation, allowDefaults, "Text Annotation is invalid");
		}
		else
		{
			RETURN_WITH_ERROR("Unknown makrup type");
		}
	}

	return true;
}


bool ModelValidator::isValid(const TextAnnotationEntity& textAnnotationEntity, bool allowDefaults/* = false*/)
{
	RETURN_IF_STR_EMPTY(textAnnotationEntity.GetText(), "Text");

	if (textAnnotationEntity.GetGeometricShapeEntity())
	{
		RETURN_IF_NOT_VALID1(textAnnotationEntity.GetGeometricShapeEntity(), allowDefaults, "Text Annotation's Geometric Shape is invalid");

		//if (textAnnotationEntity.GetGeometricShapeEntity()->GetSpatialCoordinateCollection().size() > 2)
		//	RETURN_WITH_ERROR("No more than two text connection points are allowed");
	}

	if (!allowDefaults)
	{
		RETURN_IF_STR_EMPTY(textAnnotationEntity.GetFont(), "Font");
		RETURN_IF_STR_EMPTY(textAnnotationEntity.GetFontColor(), "Font Color");
		RETURN_IF_STR_EMPTY(textAnnotationEntity.GetFontEffect(), "Font Effect");
		RETURN_IF_STR_EMPTY(textAnnotationEntity.GetFontSize(), "Font Size");
		RETURN_IF_STR_EMPTY(textAnnotationEntity.GetFontStyle(), "Font Style");
		RETURN_IF_STR_EMPTY(textAnnotationEntity.GetFontOpacity(), "Font Opacity");
		RETURN_IF_STR_EMPTY(textAnnotationEntity.GetTextJustify(), "Text Justify");
	}

	return true;
}

bool ModelValidator::isValid(const GeometricShapeEntity* const pGeoShapeEntity, bool allowDefaults/* = false*/)
{
	if (!pGeoShapeEntity)
		return true;

	RETURN_IF_NOT_VALID1(pGeoShapeEntity->GetQuestionTypeCode(), allowDefaults, "Question Type Code is invalid");
	if (pGeoShapeEntity->GetInterpolationMethod())
		RETURN_IF_NOT_VALID1(*pGeoShapeEntity->GetInterpolationMethod(), allowDefaults, "Interpolation Method is invalid");

	//if (pGeoShapeEntity->GetShapeIdentifier() < 0)
	//	RETURN_WITH_ERROR("Shape Identifier should not be negative");

	//if (pGeoShapeEntity->GetSpatialCoordinateCollection().size() < 1)
	//	RETURN_WITH_ERROR("Each Geometric Shape must have at least one Spatial Coordinate");

	//if (pGeoShapeEntity->GetShapeType() == GeometricShape::SHT_Circle)
	//{
	//	if (pGeoShapeEntity->GetSpatialCoordinateCollection().size() != 2)
	//		RETURN_WITH_ERROR("Circle must have two Spatial Coordinates associated with it.");
	//}

	if (!allowDefaults)
	{
		RETURN_IF_STR_EMPTY(pGeoShapeEntity->GetLabel(), "Label");
		RETURN_IF_STR_EMPTY(pGeoShapeEntity->GetDescription(), "Description");
		RETURN_IF_STR_EMPTY(pGeoShapeEntity->GetLineColor(), "Line Color");
		RETURN_IF_STR_EMPTY(pGeoShapeEntity->GetLineOpacity(), "Line Opacity");
		RETURN_IF_STR_EMPTY(pGeoShapeEntity->GetLineStyle(), "Line Style");
		RETURN_IF_STR_EMPTY(pGeoShapeEntity->GetLineThickness(), "Line Thickness");
	}

	const TwoDimensionGeometricShapeEntity* const pTwoDGeoShape = dynamic_cast<const TwoDimensionGeometricShapeEntity* const>(pGeoShapeEntity);
	const ThreeDimensionGeometricShapeEntity* const pThreeDGeoShape = dynamic_cast<const ThreeDimensionGeometricShapeEntity* const>(pGeoShapeEntity);
	assert(pTwoDGeoShape || pThreeDGeoShape);

	if (pTwoDGeoShape)
	{
		if (pTwoDGeoShape->GetImageReferenceUid())
			RETURN_IF_NOT_VALID1(*pTwoDGeoShape->GetInterpolationMethod(), allowDefaults, "Image Reference UID is invalid");
		if (!allowDefaults)
			RETURN_IF_STR_EMPTY(pTwoDGeoShape->GetUri(), "URI");

		for (TwoDimensionSpatialCoordinateVector::const_iterator iter = pTwoDGeoShape->GetTwoDimensionSpatialCoordinateCollection().begin();
			iter < pTwoDGeoShape->GetTwoDimensionSpatialCoordinateCollection().end(); iter++)
		{
			RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Two Dimension Spatial Coordinate is invalid");
		}
	}
	else if (pThreeDGeoShape)
	{
		if (pThreeDGeoShape->GetFrameOfReferenceUid())
			RETURN_IF_NOT_VALID1(*pThreeDGeoShape->GetFrameOfReferenceUid(), allowDefaults, "Frame of Reference UID is invalid");

		if (pThreeDGeoShape->GetFiducialUid())
			RETURN_IF_NOT_VALID1(*pThreeDGeoShape->GetFiducialUid(), allowDefaults, "Fiducial UID is invalid");

		for (ThreeDimensionSpatialCoordinateVector::const_iterator iter = pThreeDGeoShape->GetThreeDimensionSpatialCoordinateCollection().begin();
			iter < pThreeDGeoShape->GetThreeDimensionSpatialCoordinateCollection().end(); iter++)
		{
			RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Three Dimension Spatial Coordinate is invalid");
		}
	}

	return true;
}

bool ModelValidator::isValid(const TwoDimensionSpatialCoordinate& twoDimensionSpatialCoord, bool allowDefaults/* = false*/)
{
	if (twoDimensionSpatialCoord.GetCoordinateIndex() < 0)
		RETURN_WITH_ERROR("Spatial Coordinate index cannot be less that zero");
	//if (twoDimensionSpatialCoord.GetX() < 0)
	//	RETURN_WITH_ERROR("2D Spatial Coordinate (X) cannot be negative");
	//if (twoDimensionSpatialCoord.GetY() < 0)
	//	RETURN_WITH_ERROR("2D Spatial Coordinate (Y) cannot be negative");

	return true;
}

bool ModelValidator::isValid(const ThreeDimensionSpatialCoordinate& threeDimensionSpatialCoord, bool allowDefaults/* = false*/)
{
	if (threeDimensionSpatialCoord.GetCoordinateIndex() < 0)
		RETURN_WITH_ERROR("Spatial Coordinate index cannot be less that zero");
	//if (threeDimensionSpatialCoord.GetX() < 0)
	//	RETURN_WITH_ERROR("3D Spatial Coordinate (X) cannot be negative");
	//if (threeDimensionSpatialCoord.GetY() < 0)
	//	RETURN_WITH_ERROR("3D Spatial Coordinate (Y) cannot be negative");
	//if (threeDimensionSpatialCoord.GetZ() < 0)
	//	RETURN_WITH_ERROR("3D Spatial Coordinate (Z) cannot be negative");

	return true;
}

bool ModelValidator::isValid(const CharacteristicQuantification& characteristicQuantification, bool allowDefaults/* = false*/)
{
	RETURN_IF_STR_EMPTY(characteristicQuantification.GetLabel(), "Label");

	if (!allowDefaults)
	{
		if (!characteristicQuantification.GetAnnotatorConfidence())
			RETURN_WITH_ERROR("Characteristic Quantification's Confidence is not set");
		RETURN_IF_STR_EMPTY(characteristicQuantification.GetValueLabel(), "Value Label");
		RETURN_IF_STR_EMPTY(characteristicQuantification.GetValueDescription(), "Value Description");
		RETURN_IF_STR_EMPTY(characteristicQuantification.GetComment(), "Comment");
	}

	if (characteristicQuantification.GetQuantificationType() == CharacteristicQuantification::QT_Numerical)
		return isValid(dynamic_cast<const Numerical&>(characteristicQuantification), allowDefaults);
	else if(characteristicQuantification.GetQuantificationType() == CharacteristicQuantification::QT_Quantile)
		return isValid(dynamic_cast<const Quantile&>(characteristicQuantification), allowDefaults);
	else if(characteristicQuantification.GetQuantificationType() == CharacteristicQuantification::QT_Non_Quantifiable)
		return isValid(dynamic_cast<const NonQuantifiable&>(characteristicQuantification), allowDefaults);
	else if(characteristicQuantification.GetQuantificationType() == CharacteristicQuantification::QT_Scale)
		return isValid(dynamic_cast<const Scale&>(characteristicQuantification), allowDefaults);
	else if(characteristicQuantification.GetQuantificationType() == CharacteristicQuantification::QT_Interval)
		return isValid(dynamic_cast<const Interval&>(characteristicQuantification), allowDefaults);

	RETURN_WITH_ERROR("Unknown Quantification Type");
}

bool ModelValidator::isValid(const Numerical& numerical, bool allowDefaults/* = false*/)
{
	RETURN_IF_STR_EMPTY(numerical.GetUcumString(), "Numerical UCUM String");

	if (numerical.GetOperator() == aim_lib::InvalidComparisonOperatorType)
		RETURN_WITH_ERROR("Numerical's operator is not set to a valid value");

	if (!allowDefaults)
	{
		if (numerical.GetOperator() == aim_lib::None)
			RETURN_WITH_ERROR("Numerical's operator is not set to a valid value [None]");
	}

	return true;
}

bool ModelValidator::isValid(const Quantile& quantile, bool allowDefaults/* = false*/)
{
	if (quantile.GetBins() == INT_MIN)
		RETURN_WITH_ERROR("Quantile's Bins is not set");
	if (quantile.GetSelectedBin() == INT_MIN)
		RETURN_WITH_ERROR("Quantile's SelectBin is not set");

	return true;
}

bool ModelValidator::isValid(const NonQuantifiable& nonQuantifiable, bool allowDefaults/* = false*/)
{
	RETURN_IF_NOT_VALID1(nonQuantifiable.GetTypeCode(), false, "Type Code is invalid");

	return true;
}

bool ModelValidator::isValid(const Scale& scale, bool allowDefaults/* = false*/)
{
	RETURN_IF_STR_EMPTY(scale.GetValue(), "Value");

	return true;
}

bool ModelValidator::isValid(const Interval& interval, bool allowDefaults/* = false*/)
{
	RETURN_IF_STR_EMPTY(interval.GetUcumString(), "UcumString");
	
	if (interval.GetMinValue() > interval.GetMaxValue())
		RETURN_WITH_ERROR("Interval MinValue is greater than MaxValue");

	switch(interval.GetMaxOperator())
	{
	case aim_lib::None:
	case aim_lib::InvalidComparisonOperatorType:
		RETURN_WITH_ERROR("Interval's Max Operator is not set to a valid value");
		break;
	}

	switch(interval.GetMinOperator())
	{
	case aim_lib::None:
	case aim_lib::InvalidComparisonOperatorType:
		RETURN_WITH_ERROR("Interval's Min Operator is not set to a valid value");
		break;
	}
	
	return true;
}

bool ModelValidator::isValid(const CalculationEntity& calculationEntity, bool allowDefaults/* = false*/)
{
	RETURN_IF_NOT_VALID1(calculationEntity.GetUniqueIdentifier(), false, "Calculation Unique Identifier is invalid");
	RETURN_IF_NOT_VALID1(calculationEntity.GetTypeCode(), false, "Calculation Type Code is invalid");
	RETURN_IF_STR_EMPTY(calculationEntity.GetDescription(), "Calculation Description");

	RETURN_IF_NOT_VALID1(calculationEntity.GetQuestionTypeCode(), allowDefaults, "Calculation Question Type Code is invalid");

	if (calculationEntity.GetAlgorithm())
		RETURN_IF_NOT_VALID1(*calculationEntity.GetAlgorithm(), allowDefaults, "Algorithm is invalid");

	if (!allowDefaults)
		RETURN_IF_STR_EMPTY(calculationEntity.GetMathML(), "MathML");

	for (CalculationResultPtrVector::const_iterator iter = calculationEntity.GetCalculationResultCollection().begin(); iter < calculationEntity.GetCalculationResultCollection().end(); iter++)
	{
		if (*iter)
			RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Calculation Result is invalid");
	}

	return true;
}

bool ModelValidator::isValid(const CalculationResult* const pCalcResult, bool allowDefaults/* = false*/)
{
	if (!pCalcResult)
		return true;

	RETURN_IF_STR_EMPTY(pCalcResult->GetUnitOfMeasure(), "Unit of Measure");
	RETURN_IF_NOT_VALID1(pCalcResult->GetDataType(), false, "Calculation Result Data Type is not valid");

	if (pCalcResult->GetDimensionCollection().size() < 1)
		RETURN_WITH_ERROR("Calculation Result must have at least on dimension");

	if (pCalcResult->GetType() == CalculationResult::InvalidCalculationResultType)
		RETURN_WITH_ERROR("Calculation Result type is not valid");

	for (DimensionVector::const_iterator iter = pCalcResult->GetDimensionCollection().begin(); iter < pCalcResult->GetDimensionCollection().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Calculation Result's dimension is invalid");

	const CompactCalculationResult* const pCompactCalcResult = dynamic_cast<const CompactCalculationResult* const>(pCalcResult);
	const ExtendedCalculationResult* const pExtendedCalcResult = dynamic_cast<const ExtendedCalculationResult* const>(pCalcResult);
	assert(pCompactCalcResult || pExtendedCalcResult);

	if (pCompactCalcResult)
	{
		RETURN_IF_NOT_VALID1(*pCompactCalcResult, allowDefaults, "Compact Calculation Result is invalid");
	}
	else if (pExtendedCalcResult)
	{
		RETURN_IF_NOT_VALID1(*pExtendedCalcResult, allowDefaults, "Extended Calculation Result is invalid");
	}

	return true;
}

bool ModelValidator::isValid(const CompactCalculationResult& compactCalcResult, bool allowDefaults/* = false*/)
{
	RETURN_IF_STR_EMPTY(compactCalcResult.GetValue(), "Value");

	if (compactCalcResult.GetEncoding())
		RETURN_IF_NOT_VALID1(*compactCalcResult.GetEncoding(), allowDefaults, "Compression is not valid");

	if (compactCalcResult.GetCompression())
		RETURN_IF_NOT_VALID1(*compactCalcResult.GetCompression(), allowDefaults, "Compression is not valid");

	return true;
}

bool ModelValidator::isValid(const ExtendedCalculationResult& extendedCalcResult, bool allowDefaults/* = false*/)
{
	if (extendedCalcResult.GetCalculationDataCollection().size() < 1)
		RETURN_WITH_ERROR("Extended Calculation Result is missing its data");
	for(CalculationDataVector::const_iterator iter = extendedCalcResult.GetCalculationDataCollection().begin(); iter < extendedCalcResult.GetCalculationDataCollection().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Extended Calculation Result's data is invalid");

	return true;
}

bool ModelValidator::isValid(const aim_lib::CalculationData& data, bool allowDefaults/* = false*/)
{
	if (data.GetCoordinateCollection().size() < 1)
		RETURN_WITH_ERROR("Data is missing its coordinate(s)");
	for (CoordinateVector::const_iterator iter = data.GetCoordinateCollection().begin(); iter < data.GetCoordinateCollection().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Data's coordinate is invalid");

	return true;
}

bool ModelValidator::isValid(const Coordinate& coordinate, bool allowDefaults/* = false*/)
{
	if (coordinate.GetPosition() < 0)
		RETURN_WITH_ERROR("Coordinate position cannot be negative");
	if (coordinate.GetDimensionIndex() < 0)
		RETURN_WITH_ERROR("Coordinate's dimension index cannot be negative");

	return true;
}

bool ModelValidator::isValid(const Dimension& dimension, bool allowDefaults/* = false*/)
{
	if (dimension.GetIndex() < 0)
		RETURN_WITH_ERROR("Dimension index cannot be negative");
	if (dimension.GetSize() < 0)
		RETURN_WITH_ERROR("Dimension side cannot be negative");

	RETURN_IF_STR_EMPTY(dimension.GetLabel(), "Dimension Label");

	return true;
}

bool ModelValidator::isValid(const Algorithm& algorithm, bool allowDefaults/* = false*/)
{
	RETURN_IF_STR_EMPTY(algorithm.GetName(), "Name");
	RETURN_IF_NOT_VALID1(algorithm.GetType(), false, "Algorithm Type is invalid");

	if (algorithm.GetUniqueIdentifier())
		RETURN_IF_NOT_VALID1(*algorithm.GetUniqueIdentifier(), allowDefaults, "Algorithm Unique Identifier is invalid");

	if (!allowDefaults)
	{
		RETURN_IF_STR_EMPTY(algorithm.GetVersion(), "Version");
		RETURN_IF_STR_EMPTY(algorithm.GetDescription(), "Description");
	}

	for (ParameterVector::const_iterator iter = algorithm.GetParameterCollection().begin(); iter < algorithm.GetParameterCollection().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Algorithm parameter is invalid");

	return true;
}

bool ModelValidator::isValid(const Parameter& parameter, bool allowDefaults/* = false*/)
{
	RETURN_IF_STR_EMPTY(parameter.GetName(), "Name");
	RETURN_IF_STR_EMPTY(parameter.GetValue(), "Value");
	RETURN_IF_NOT_VALID1(parameter.GetDataType(), false, "Parameter Data Type is invalid");

	return true;
}

bool ModelValidator::isValid(const ImageReferenceEntity& imageRefEntity, bool allowDefaults/* = false*/)
{
	RETURN_IF_NOT_VALID1(imageRefEntity.GetUniqueIdentifier(), false, "Image Reference Entity Unique Identifier is invalid");

	if (imageRefEntity.GetImageReferenceEntityType() == ImageReferenceEntity::T_DICOM_IMAGE_REF)
	{
		const DicomImageReferenceEntity& dicomImgRefEntity = dynamic_cast<const DicomImageReferenceEntity&>(imageRefEntity);

		RETURN_IF_NOT_VALID1(dicomImgRefEntity.GetImageStudy(), allowDefaults, "Image Study is invalid");
	}
	else if (imageRefEntity.GetImageReferenceEntityType() == ImageReferenceEntity::T_URI_IMAGE_REF)
	{
		const UriImageReferenceEntity& uriImgRefEntity = dynamic_cast<const UriImageReferenceEntity&>(imageRefEntity);

		RETURN_IF_STR_EMPTY(uriImgRefEntity.GetUri(), "URI");
		RETURN_IF_STR_EMPTY(uriImgRefEntity.GetMimeType(), "MIME Type");
	}

	return true;
}

bool ModelValidator::isValid(const ImageStudy& imageStudy, bool allowDefaults/* = false*/)
{
	RETURN_IF_NOT_VALID1(imageStudy.GetInstanceUid(), false, "Instance UID");
	RETURN_IF_NOT_VALID1(imageStudy.GetStartDate(), false, "Start Date");
	RETURN_IF_NOT_VALID1(imageStudy.GetStartTime(), false, "Start Time");

	RETURN_IF_NOT_VALID1(imageStudy.GetImageSeries(), allowDefaults, "Image Series is invalid");

	for (ReferencedDicomObjectVector::const_iterator iter = imageStudy.GetReferencedDicomObjectCollection().begin(); iter < imageStudy.GetReferencedDicomObjectCollection().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Referenced DICOM Object is invalid");

	if (!allowDefaults)
		RETURN_IF_STR_EMPTY(imageStudy.GetProceduDescription(), "Procedure Description");

	return true;
}

bool ModelValidator::isValid(const ImageSeries& series, bool allowDefaults/* = false*/)
{
	RETURN_IF_NOT_VALID1(series.GetInstanceUid(), false, "Instance UID");
	RETURN_IF_NOT_VALID1(series.GetModality(), false, "Modality");

	if (series.GetImageCollection().size() < 1)
		RETURN_WITH_ERROR("Image Series must include at least one image");

	for (ImageVector::const_iterator iter = series.GetImageCollection().begin(); iter < series.GetImageCollection().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Image is invalid");

	return true;
}

bool ModelValidator::isValid(const Image& image, bool allowDefaults/* = false*/)
{
	RETURN_IF_NOT_VALID1(image.GetSopClassUid(), false, "SOP Class UID is invalid");
	RETURN_IF_NOT_VALID1(image.GetSopInstanceUid(), false, "SOP Instance UID is invalid");

	if (image.GetGeneralImage())
		RETURN_IF_NOT_VALID1(*image.GetGeneralImage(), allowDefaults, "General Image is invalid");

	if (image.GetImagePlane())
		RETURN_IF_NOT_VALID1(*image.GetImagePlane(), allowDefaults, "Image Plane is invalid");

	return true;
}

bool ModelValidator::isValid(const ReferencedDicomObject& refDicomObj, bool allowDefaults/* = false*/)
{
	RETURN_IF_NOT_VALID1(refDicomObj.GetSopInstanceUid(), false, "SOP Instance UID is invalid");
	RETURN_IF_NOT_VALID1(refDicomObj.GetModality(), false, "Modality is invalid");

	return true;
}

bool ModelValidator::isValid(const GeneralImage& generalImage, bool allowDefaults/* = false*/)
{
	if (!allowDefaults)
	{
		RETURN_IF_STR_EMPTY(generalImage.GetPatientOrientationRow(), "Patient Orientation Row");
		RETURN_IF_STR_EMPTY(generalImage.GetPatientOrientationColumn(), "Patient Orientation Column");
	}

	return true;
}

bool ModelValidator::isValid(const ImagePlane& imagePlane, bool allowDefaults/* = false*/)
{
	if (!allowDefaults)
	{
		if (!imagePlane.GetRowImageOrientationX())
			RETURN_WITH_ERROR("Row Image Orientation X is missing");
		if (!imagePlane.GetRowImageOrientationY())
			RETURN_WITH_ERROR("Row Image Orientation Y is missing");
		if (!imagePlane.GetRowImageOrientationZ())
			RETURN_WITH_ERROR("Row Image Orientation Z is missing");
		if (!imagePlane.GetColumnImageOrientationX())
			RETURN_WITH_ERROR("Column Image Orientation X is missing");
		if (!imagePlane.GetColumnImageOrientationY())
			RETURN_WITH_ERROR("Column Image Orientation Y is missing");
		if (!imagePlane.GetColumnImageOrientationZ())
			RETURN_WITH_ERROR("Column Image Orientation Z is missing");
		if (!imagePlane.GetVerticalPixelSpacing())
			RETURN_WITH_ERROR("Vertical Pixel Spacing is missing");
		if (!imagePlane.GetHorizontalPixelSpacing())
			RETURN_WITH_ERROR("Horizontal Pixel Spacing is missing");
		if (!imagePlane.GetSliceThickness())
			RETURN_WITH_ERROR("Slice Thickness is missing");
		if (!imagePlane.GetImagePositionX())
			RETURN_WITH_ERROR("Image Position X is missing");
		if (!imagePlane.GetImagePositionY())
			RETURN_WITH_ERROR("Image Position Y is missing");
		if (!imagePlane.GetImagePositionZ())
			RETURN_WITH_ERROR("Image Position Z is missing");
	}

	return true;
}

bool ModelValidator::isValid(const TaskContextEntity& taskContextEntity, bool allowDefaults/* = false*/)
{
	RETURN_IF_NOT_VALID1(taskContextEntity.GetUniqueIdentifier(), false, "Unique Identifier is invalid");
	RETURN_IF_NOT_VALID1(taskContextEntity.GetWorklistTaskUid(), false, "Worklist Task Unique Identifier is invalid");
	RETURN_IF_STR_EMPTY(taskContextEntity.GetWorklistTaskName(), "Worklist Task Name");
	RETURN_IF_STR_EMPTY(taskContextEntity.GetWorklistTaskDescription(), "Worklist Description");
	RETURN_IF_STR_EMPTY(taskContextEntity.GetWorklistTaskVersion(), "Worklist Version");
	RETURN_IF_NOT_VALID1(taskContextEntity.GetWorklistTaskCategory(), false, "Worklist Task Category is invalid");
	RETURN_IF_NOT_VALID1(taskContextEntity.GetWorklistTaskLevel(), false, "Worklist Task Level is invalid");
	RETURN_IF_NOT_VALID1(taskContextEntity.GetWorklistTaskType(), false, "Worklist Task Type is invalid");
	if (taskContextEntity.GetWorklistTaskRepeatType())
		RETURN_IF_NOT_VALID1(*taskContextEntity.GetWorklistTaskRepeatType(), allowDefaults, "Worklist Task Repeat Type is invalid");
	if (taskContextEntity.GetWorklistTaskVariabilityType())
		RETURN_IF_NOT_VALID1(*taskContextEntity.GetWorklistTaskVariabilityType(), allowDefaults, "Worklist Task Variability Type is invalid");
	RETURN_IF_NOT_VALID1(taskContextEntity.GetWorklistSubtaskUid(), false, "Worklist Subtask Unique Identifier is invalid");
	RETURN_IF_STR_EMPTY(taskContextEntity.GetWorklistSubtaskName(), "Worklist Subtask Name");
	RETURN_IF_NOT_VALID1(taskContextEntity.GetWorklistSubtaskStartDateTime(), false, "Worklist Subtask Start DateTime is invalid");
	RETURN_IF_NOT_VALID1(taskContextEntity.GetWorklistSubtaskClosedDateTime(), false, "Worklist Subtask Close DateTime is invalid");

	return true;
}

bool ModelValidator::isValid(const AnnotationRoleEntity& annotationRoleEntity, bool allowDefaults/* = false*/)
{
	RETURN_IF_NOT_VALID1(annotationRoleEntity.GetUniqueIdentifier(), false, "Unique Identifier is invalid");
	RETURN_IF_NOT_VALID1(annotationRoleEntity.GetRoleCode(), false, "Role Code is invalid");

	RETURN_IF_NOT_VALID1(annotationRoleEntity.GetQuestionTypeCode(), allowDefaults, "Question Type Code is invalid");

	if (annotationRoleEntity.GetRoleSequenceNumber() == INT_MIN)
		RETURN_WITH_ERROR("Role Sequence Number is not set");

	return true;
}

bool ModelValidator::isValid(const LesionObservationEntity* const pLesionObsEntity, bool allowDefaults/* = false*/)
{
	if (!pLesionObsEntity)
		return true;

	RETURN_IF_NOT_VALID1(pLesionObsEntity->GetUniqueIdentifier(), false, "Unique Identifier is invalid");
	RETURN_IF_NOT_VALID1(pLesionObsEntity->GetLesionUniqueIdentifier(), false, "Lesion Unique Identifier is invalid");
	
	const GeneralLesionObservationEntity* const pGenLesionObsEntity = dynamic_cast<const GeneralLesionObservationEntity* const>(pLesionObsEntity);
	if (pGenLesionObsEntity)
	{
		RETURN_IF_NOT_VALID1(pGenLesionObsEntity->GetLesionType(), false, "Lesion Type is invalid");
		RETURN_IF_STR_EMPTY(pGenLesionObsEntity->GetTrackingIdentifier(), "Tracking Identifier");
		if (pGenLesionObsEntity->GetReconstructionInterval())
			RETURN_IF_NOT_VALID1(*pGenLesionObsEntity->GetReconstructionInterval(), allowDefaults, "Reconstruction Interval is invalid");
		if (pGenLesionObsEntity->GetLaterality())
			RETURN_IF_NOT_VALID1(*pGenLesionObsEntity->GetLaterality(), allowDefaults, "Laterality is invalid");
	}
	else
	{
		const TimePointLesionObservationEntity* const pTimePointLesionObsEntity = dynamic_cast<const TimePointLesionObservationEntity* const>(pLesionObsEntity);
		if (pTimePointLesionObsEntity)
		{
			if (pTimePointLesionObsEntity->GetPredecessorLesionTrackingUid())
				RETURN_IF_NOT_VALID1(*pTimePointLesionObsEntity->GetPredecessorLesionTrackingUid(), allowDefaults, "Predecessor Lesion Tracking Uid is invalid");
			if (pTimePointLesionObsEntity->GetQualitativeAssessment())
				RETURN_IF_NOT_VALID1(*pTimePointLesionObsEntity->GetQualitativeAssessment(), allowDefaults, "Qualitative Assessment is invalid");
			if (pTimePointLesionObsEntity->GetReasonUnableToEvaluate())
				RETURN_IF_NOT_VALID1(*pTimePointLesionObsEntity->GetReasonUnableToEvaluate(), allowDefaults, "Reason Unable To Evaluate is invalid");
			if (pTimePointLesionObsEntity->GetReasonUnableToMeasure())
				RETURN_IF_NOT_VALID1(*pTimePointLesionObsEntity->GetReasonUnableToMeasure(), allowDefaults, "Reason Unable To Measure is invalid");
			if (pTimePointLesionObsEntity->GetTherapeuticResponse())
				RETURN_IF_NOT_VALID1(*pTimePointLesionObsEntity->GetTherapeuticResponse(), allowDefaults, "Therapeutic Response is invalid");

			if (!allowDefaults)
			{
				if (!pTimePointLesionObsEntity->GetCanEvaluateLesion())
					RETURN_WITH_ERROR("Can Evaluate Lesion flag is required");
				if (!pTimePointLesionObsEntity->GetCanMeasureLesion())
					RETURN_WITH_ERROR("Can Measure Lesion flag is required");
				RETURN_IF_STR_EMPTY(pTimePointLesionObsEntity->GetComment(), "Comment");
				if (!pTimePointLesionObsEntity->GetIsUnequivocalProgression())
					RETURN_WITH_ERROR("Is Unequivocal Progression flag is required");
			}
		}
		else
		{
			RETURN_WITH_ERROR("Unknown Lesion Observation Entity type");
		}
	}

	return true;
}

bool ModelValidator::isValid(const AuditTrail& auditTrail, bool allowDefaults/* = false*/)
{
	RETURN_IF_NOT_VALID1(auditTrail.GetStatusCode(), false, "Status Code is invalid");
	RETURN_IF_NOT_VALID1(auditTrail.GetDateTime(), false, "Date Time is invalid");
	RETURN_IF_NOT_VALID1(auditTrail.GetChangeReason(), false, "Change Reason is invalid");

	if (auditTrail.GetWorklistSubtaskUid())
		RETURN_IF_NOT_VALID1(*auditTrail.GetWorklistSubtaskUid(), allowDefaults, "Worklist Subtask UID is invalid");

	if (!allowDefaults)
	{
		RETURN_IF_STR_EMPTY(auditTrail.GetComment(), "Comment");
	}

	return true;
}

bool ModelValidator::isValid(const AdjudicationObservation& adjudicationObs, bool allowDefaults/* = false*/)
{
	RETURN_IF_NOT_VALID1(adjudicationObs.GetObservationScope(), false, "Observation Scope is invalid");
	RETURN_IF_NOT_VALID1(adjudicationObs.GetObservationUid(), false, "Observation Unique Identifier is invalid");
	RETURN_IF_NOT_VALID1(adjudicationObs.GetReasonForChoice(), false, "Reason for Choice is invalid");
	if (adjudicationObs.GetReasonForDiscordance())
		RETURN_IF_NOT_VALID1(*adjudicationObs.GetReasonForDiscordance(), allowDefaults, "Reason for Discordance is invalid");
	if (adjudicationObs.GetPersonObserversRoleInThisProcedure())
		RETURN_IF_NOT_VALID1(*adjudicationObs.GetPersonObserversRoleInThisProcedure(), allowDefaults, "Person Observers Role In This Procedure is invalid");

	if (!allowDefaults)
	{
		RETURN_IF_STR_EMPTY(adjudicationObs.GetComment(), "Comment");
		for (std::vector<std::string>::const_iterator iter = adjudicationObs.GetIdentifierWithinAcceptedPersonObserversRole().begin();
			iter < adjudicationObs.GetIdentifierWithinAcceptedPersonObserversRole().end(); iter++)
		{
			RETURN_IF_STR_EMPTY(*iter, "Identifier Within Accepted Person Observers Role");
		}
		for (std::vector<std::string>::const_iterator iter = adjudicationObs.GetIdentifierWithinRejectedPersonObserversRole().begin();
			iter < adjudicationObs.GetIdentifierWithinRejectedPersonObserversRole().end(); iter++)
		{
			RETURN_IF_STR_EMPTY(*iter, "Identifier Within Rejected Person Observers Role");
		}
	}

	return true;
}

bool ModelValidator::isValid(const AnnotationStatement& annotationStatement, bool allowDefaults/* = false*/)
{
	RETURN_IF_NOT_VALID1(annotationStatement.GetSubjectUniqueIdentifier(), false, "Subject Unique Identifier is invalid[" + annotationStatement.GetStatementClassName() + "]");
	RETURN_IF_NOT_VALID1(annotationStatement.GetObjectUniqueIdentifier(), false, "Object Unique Identifier is invalid");

	return true;
}


bool ModelValidator::isValid(const DateTime& dateTime, bool allowDefaults/* = false*/)
{
	if (dateTime == DateTime() && !allowDefaults)
		RETURN_WITH_ERROR("DateTime is empty");

	// Check Date
	RETURN_IF_NOT_VALID1(dateTime.GetDate(), allowDefaults, "");

	// Check Time
	RETURN_IF_RANGE_NOT_VALID(dateTime.GetHour(), 0, 23, "Hour");
	RETURN_IF_RANGE_NOT_VALID(dateTime.GetMinute(), 0, 59, "Minute");
	RETURN_IF_RANGE_NOT_VALID(dateTime.GetSecond(), 0.0, 59.999999, "Seconds");

	return true;
}

// Checks if the given date is a valid date in Gregorian calendar
bool ModelValidator::isValid(const Date& date, bool allowDefaults /*= false*/)
{
	if (date == Date() && !allowDefaults)
		RETURN_WITH_ERROR("Date is empty");

	// Check month
	RETURN_IF_RANGE_NOT_VALID(date.GetMonth(), 1, 12, "Month");

	// Check year
	if (date.GetYear() == 0)
		RETURN_WITH_ERROR("There is no 0 year in Gregorian calendar");

	// Check day
	int day = date.GetDay();
	
	// 1582 - Gregorian calendar switch.
	// No dates exist between october 4 and October 15
	if (date.GetYear() == 1582 && date.GetMonth() == 10 && day > 4 && day < 15)
		RETURN_WITH_ERROR("The year 1582 does not have dates between October 4 and October 15");

	int maxDay = 31;
	switch (date.GetMonth())
	{
		case 4:
		case 6:
		case 9:
		case 11:
			maxDay = 30;
			break;
		case 2:
			maxDay = AIMUtil::isLeapYear(date.GetYear()) ? 29 : 28;
			break;
	}
	RETURN_IF_RANGE_NOT_VALID(day, 0, maxDay, "Day");

	return true;
}

bool ModelValidator::isValid(const Time& time, bool allowDefaults /*= false*/)
{
	if (time == Time() && !allowDefaults)
		RETURN_WITH_ERROR("Time is empty");

	RETURN_IF_RANGE_NOT_VALID(time.GetHour(), 0, 23, "Hours");
	RETURN_IF_RANGE_NOT_VALID(time.GetMinute(), 0, 59, "Minutes");
	if (time.GetSecond() < 0.0)
		RETURN_WITH_ERROR("Seconds cannot have negative value");
	
	return true;
}

bool ModelValidator::isValid(const iso_21090::CD& cd, bool allowDefaults /*= false*/)
{
	RETURN_IF_STR_EMPTY(cd.GetCodeValue(), "Code Value");
	RETURN_IF_STR_EMPTY(cd.GetCodeMeaning(), "Code Meaning");
	RETURN_IF_STR_EMPTY(cd.GetCodingSchemeDesignator(), "Coding Scheme Designator");

	// NOTE: Don't check this! This is not a model optional parameter - this is an optional parameter for the CD data type.
	//if (!allowDefaults)
	//	RETURN_IF_STR_EMPTY(cd.GetCodingSchemeVersion(), "Coding Scheme Version");

	return true;
}

bool ModelValidator::isValid(const iso_21090::CDVector& cdVector, bool allowDefaults /*= false*/)
{
	if (!allowDefaults)
	{
		if (cdVector.size() < 1)
			RETURN_WITH_ERROR("Code list may not be empty");
	}

	for (iso_21090::CDVector::const_iterator iter = cdVector.begin(); iter < cdVector.end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Code");

	return true;
}

bool ModelValidator::isValid(const iso_21090::II& ii, bool allowDefaults /*= false*/)
{
	RETURN_IF_UID_NOT_VALID(ii.toString(), "II");

	return true;
}

bool ModelValidator::isUIDValid(const std::string& uid)
{
	RETURN_IF_STR_LENGTH(uid, 0, 64, "UID"); // [0..64]

	if (uid[0] != '0' && uid[0] != '.' &&		// doesn't start with 0 or period
		uid.find(".0") == std::string::npos &&	// doesn't have padded numbers
		uid.find("..") == std::string::npos)	// doesn't have ".."
	{
		for (std::string::size_type i = 0; i < uid.length(); i++)
		{
			if (uid[i] != '.' && !std::isdigit(uid[i])) // should be periods or digits only
			{
				_errors.push_back("UID must constist of digits and periods(.) only");
				return false;
			}
		}
		return true;
	}
	else
	{
		_errors.push_back("UID cannot start with 0, period(.), have zero-padded values (ex: 12345.09.09) or have consecutive periods (..)");
	}

	return false;
}
const std::vector<std::string>& ModelValidator::GetValidationErrors()
{
	return _errors;
}