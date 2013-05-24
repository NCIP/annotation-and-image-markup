/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"
#include <limits.h>

#include "../model/AimHeaders.h"

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
#define RETURN_IF_STR_EMPTY(testStr, paramName) if (testStr.empty()) RETURN_WITH_ERROR(std::string(paramName).append(" is empty"))
#define RETURN_IF_STR_LENGTH(testStr, minLen, maxLen, paramName) if (testStr.length() < minLen || testStr.length() > maxLen) { std::stringstream errStream; errStream << paramName << " value must be between " << minLen << " and " << maxLen << " in length"; std::string errMsg = errStream.str(); RETURN_WITH_ERROR(errMsg) }
//#define RETURN_IF_STR_LENGTH(str, minLen, maxLen, paramName) if (str.length() < minLen || str.length() > maxLen) RETURN_WITH_ERROR(std::string(paramName).append(" value has must be between ").append(AIMUtil::IntToString(minLen)).append(" and ").append(AIMUtil::IntToString(maxLen)).append(" in length"))
#define RETURN_IF_UID_NOT_VALID(uid, paramName) if (!isUIDValid(uid)) { std::stringstream errStream; errStream << paramName << " value is not a valid UID"; std::string errMsg = errStream.str(); RETURN_WITH_ERROR(errMsg) }


ModelValidator::ModelValidator(void)
{
}

ModelValidator::~ModelValidator(void)
{
}

bool ModelValidator::isValid(const ImageAnnotation& imgAnnotation)
{
	//if (imgAnnotation.GetPatient() != NULL)
		RETURN_IF_NOT_VALID1(imgAnnotation.GetPatient(), true, "Patient is invalid");

	for(TextAnnotationVector::const_iterator iter = imgAnnotation.GetTextAnnotationCollection().begin();
		iter < imgAnnotation.GetTextAnnotationCollection().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, true, "Text Annotation instance is invalid");

	for (ImageReferencePtrVector::const_iterator iter = imgAnnotation.GetImageReferenceCollection().begin();
		iter < imgAnnotation.GetImageReferenceCollection().end(); iter++)
	{
		if (*iter != NULL)
			RETURN_IF_NOT_VALID1(**iter, true, "Image Reference is invalid");
	}

	for (SegmentationVector::const_iterator iter = imgAnnotation.GetSegmentationCollection().begin();
		iter < imgAnnotation.GetSegmentationCollection().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, true, "Segmentation instance is invalid");

	for (GeoShapePtrVector::const_iterator iter = imgAnnotation.GetGeometricShapeCollection().begin();
		iter < imgAnnotation.GetGeometricShapeCollection().end(); iter++)
	{
		if (*iter != NULL)
			RETURN_IF_NOT_VALID1(**iter, true, "Geometic Shape is invalid");
	}

	for(InferenceVector::const_iterator iter = imgAnnotation.GetInferenceCollection().begin();
		iter < imgAnnotation.GetInferenceCollection().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, true, "Inference instance is invalid");

	RETURN_IF_NOT_VALID1((const Annotation&)imgAnnotation, true, "Annotation is invalid");

	return true;
}

bool ModelValidator::isValid(const AnnotationOfAnnotation& annOfAnnotation)
{
	if (annOfAnnotation.GetReferencedAnnotationCollection().size() < 1)
		RETURN_WITH_ERROR("Annotation of Annotations must have at least one Referenced annotation");

	for (ReferencedAnnotationVector::const_iterator iter = annOfAnnotation.GetReferencedAnnotationCollection().begin();
		iter < annOfAnnotation.GetReferencedAnnotationCollection().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, true, "Referenced Annotation is invalid");

	RETURN_IF_NOT_VALID1((const Annotation&)annOfAnnotation, true, "Annotation is invalid");

	return true;
}

bool ModelValidator::isValid(const Annotation& annotation, bool allowDefaults/* = false*/)
{
	RETURN_IF_STR_EMPTY(annotation.GetAimVersion(), "AIM Version");
	RETURN_IF_STR_EMPTY(annotation.GetName(), "Annotation Name");
	RETURN_IF_UID_NOT_VALID(annotation.GetUniqueIdentifier(), "Annotation Unique Identifier");
	RETURN_IF_NOT_VALID1(annotation.GetDateTime(), false, "Annotation DateTime is invalid");

	RETURN_IF_STR_EMPTY(annotation.GetCodeValue(), "Annotation Code Value");
	RETURN_IF_STR_EMPTY(annotation.GetCodeMeaning(), "Annotation Code Meaning");
	RETURN_IF_STR_EMPTY(annotation.GetCodingSchemeDesignator(), "Annotation Coding Scheme Designator");

	if (!allowDefaults)
	{
		RETURN_IF_STR_EMPTY(annotation.GetCodingSchemeVersion(), "Annotation Coding Scheme Version");
		RETURN_IF_STR_EMPTY(annotation.GetComment(), "Annotation Comment");
		RETURN_IF_UID_NOT_VALID(annotation.GetPrecedentReferencedAnnotationUID(), "Precedent Referenced Annotation UID");
	}

	if (annotation.GetEquipment() != NULL)
		RETURN_IF_NOT_VALID1(*annotation.GetEquipment(), allowDefaults, "Equipment is invalid");

	if (annotation.GetUser() != NULL)
		RETURN_IF_NOT_VALID1(*annotation.GetUser(), allowDefaults, "User is invalid");

	if (annotation.GetAimStatus() != NULL)
		RETURN_IF_NOT_VALID1(*annotation.GetAimStatus(), allowDefaults, "AimStatus is invalid");

	for (CalculationVector::const_iterator iter = annotation.GetCalculationCollection().begin(); iter < annotation.GetCalculationCollection().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Calculation is invalid");

	for (AnatomicEntityVector::const_iterator iter = annotation.GetAnatomicEntityCollection().begin(); iter < annotation.GetAnatomicEntityCollection().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Anatomic Entity is invalid");

	for (ImagingObservationVector::const_iterator iter = annotation.GetImagingObservationCollection().begin(); iter < annotation.GetImagingObservationCollection().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Imaging Observation is invalid");

	return true;
}

bool ModelValidator::isValid(const AnatomicEntity& anatomicEntity, bool allowDefaults/* = false*/)
{
	RETURN_IF_STR_EMPTY(anatomicEntity.GetCodeValue(), "Anatomic Entity Code Value");
	RETURN_IF_STR_EMPTY(anatomicEntity.GetCodeMeaning(), "Anatomic Entity Code Meaning");
	RETURN_IF_STR_EMPTY(anatomicEntity.GetCodingSchemeDesignator(), "Anatomic Entity Coding Scheme Designator");
	RETURN_IF_STR_EMPTY(anatomicEntity.GetLabel(), "Label");

	for (AnatomicEntityCharacteristicVector::const_iterator iter = anatomicEntity.GetAnatomicEntityCharacteristicCollection().begin(); iter < anatomicEntity.GetAnatomicEntityCharacteristicCollection().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Anatomic Entity Characteristic is invalid");

	if (!allowDefaults)
	{
		RETURN_IF_STR_EMPTY(anatomicEntity.GetCodingSchemeVersion(), "Anatomic Entity Coding Scheme Version");

		if (anatomicEntity.GetAnnotatorConfidence() == NULL)
			RETURN_WITH_ERROR("Anatomic Enity's Confidence is not set");
	}

	// Call protege for validation
	// VK: 2012/05/03 - no more Protege
	//aim_protege_jni::CJniProtegeBridge protegeBridge;
	//std::string result = protegeBridge.getValidationResult(anatomicEntity.GetCodeValue(), anatomicEntity.GetCodingSchemeDesignator(), anatomicEntity.GetCodeMeaning());

	//// Validation fails if result begins with "ERROR:"
	//if (result.find("ERROR") == 0)
	//	RETURN_WITH_ERROR(result);

	return true;
}

bool ModelValidator::isValid(const AnatomicEntityCharacteristic& anatomicEntityChar, bool allowDefaults/* = false*/)
{
	RETURN_IF_STR_EMPTY(anatomicEntityChar.GetCodeValue(), "Anatomic Entity Characteristic Code Value");
	RETURN_IF_STR_EMPTY(anatomicEntityChar.GetCodeMeaning(), "Anatomic Entity Characteristic Code Meaning");
	RETURN_IF_STR_EMPTY(anatomicEntityChar.GetCodingSchemeDesignator(), "Anatomic Entity Characteristic Coding Scheme Designator");
	RETURN_IF_STR_EMPTY(anatomicEntityChar.GetLabel(), "Label");

	if (!allowDefaults)
	{
		RETURN_IF_STR_EMPTY(anatomicEntityChar.GetCodingSchemeVersion(), "Anatomic Entity Characteristic Coding Scheme Version");

		if (anatomicEntityChar.GetAnnotatorConfidence() == NULL)
			RETURN_WITH_ERROR("Anatomic Enity Characteristic's Confidence is not set");
	}

	for (CharacteristicQuantificationPtrVector::const_iterator iter = anatomicEntityChar.GetCharacteristicQuantificationCollection().begin();
		iter < anatomicEntityChar.GetCharacteristicQuantificationCollection().end(); iter++)
	{
		if (*iter != NULL)
			RETURN_IF_NOT_VALID1(**iter, allowDefaults, "Characteristic Quantification is invalid");
	}

	// Call protege for validation
	// VK: 2012/05/03 - no more Protege
	//aim_protege_jni::CJniProtegeBridge protegeBridge;
	//std::string result = protegeBridge.getValidationResult(anatomicEntityChar.GetCodeValue(), anatomicEntityChar.GetCodingSchemeDesignator(), anatomicEntityChar.GetCodeMeaning());

	//// Validation fails if result begins with "ERROR:"
	//if (result.find("ERROR") == 0)
	//	RETURN_WITH_ERROR(result);

	return true;
}

bool ModelValidator::isValid(const ImagingObservation& imagingObservation, bool allowDefaults/* = false*/)
{
	RETURN_IF_STR_EMPTY(imagingObservation.GetCodeValue(), "Imaging Observation Code Value");
	RETURN_IF_STR_EMPTY(imagingObservation.GetCodeMeaning(), "Imaging Observation Code Meaning");
	RETURN_IF_STR_EMPTY(imagingObservation.GetCodingSchemeDesignator(), "Imaging Observation Coding Scheme Designator");
	RETURN_IF_STR_EMPTY(imagingObservation.GetLabel(), "Label");

	if (imagingObservation.GetReferencedGeometricShape() != NULL)
		RETURN_IF_NOT_VALID1(*imagingObservation.GetReferencedGeometricShape(), allowDefaults, "Referenced Geomentric Shape is invalid");

	for (ImagingObservationCharacteristicVector::const_iterator iter = imagingObservation.GetImagingObservationCharacteristicCollection().begin(); iter < imagingObservation.GetImagingObservationCharacteristicCollection().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Imaging Observation Characteristic is invalid");

	if (!allowDefaults)
	{
		RETURN_IF_STR_EMPTY(imagingObservation.GetCodingSchemeVersion(), "Imaging Observation Coding Scheme Version");
		RETURN_IF_STR_EMPTY(imagingObservation.GetComment(), "Imaging Observation Comment");

		if (imagingObservation.GetAnnotatorConfidence() == NULL)
			RETURN_WITH_ERROR("Imaging Observation's Confidence is not set");
	}

	// Call protege for validation
	// 2012/05/03 - no more Protege
	//aim_protege_jni::CJniProtegeBridge protegeBridge;
	//std::string result = protegeBridge.getValidationResult(imagingObservation.GetCodeValue(), imagingObservation.GetCodingSchemeDesignator(), imagingObservation.GetCodeMeaning());

	//// Validation fails if result begins with "ERROR:"
	//if (result.find("ERROR") == 0)
	//	RETURN_WITH_ERROR(result);

	return true;
}

bool ModelValidator::isValid(const ImagingObservationCharacteristic& imagingObsChar, bool allowDefaults/* = false*/)
{
	RETURN_IF_STR_EMPTY(imagingObsChar.GetCodeValue(), "Imaging Observation Characteristic Code Value");
	RETURN_IF_STR_EMPTY(imagingObsChar.GetCodeMeaning(), "Imaging Observation Characteristic Code Meaning");
	RETURN_IF_STR_EMPTY(imagingObsChar.GetCodingSchemeDesignator(), "Imaging Observation Characteristic Coding Scheme Designator");
	RETURN_IF_STR_EMPTY(imagingObsChar.GetLabel(), "Label");

	for (CharacteristicQuantificationPtrVector::const_iterator iter = imagingObsChar.GetCharacteristicQuantificationCollection().begin();
		iter < imagingObsChar.GetCharacteristicQuantificationCollection().end(); iter++)
	{
		if (*iter != NULL)
			RETURN_IF_NOT_VALID1(**iter, allowDefaults, "Characteristic Quantification is invalid");
	}

	if (!allowDefaults)
	{
		RETURN_IF_STR_EMPTY(imagingObsChar.GetCodingSchemeVersion(), "Imaging Observation Characteristic Coding Scheme Version");
		RETURN_IF_STR_EMPTY(imagingObsChar.GetComment(), "Imaging Observation Characteristic Comment");

		if (imagingObsChar.GetAnnotatorConfidence() == NULL)
			RETURN_WITH_ERROR("Imaging Observation Characteristic's Confidence is not set");
	}

	// Call protege for validation
	// 2012/05/03 - no more Protege
	//aim_protege_jni::CJniProtegeBridge protegeBridge;
	//std::string result = protegeBridge.getValidationResult(imagingObsChar.GetCodeValue(), imagingObsChar.GetCodingSchemeDesignator(), imagingObsChar.GetCodeMeaning());

	//// Validation fails if result begins with "ERROR:"
	//if (result.find("ERROR") == 0)
	//	RETURN_WITH_ERROR(result);

	return true;
}

bool ModelValidator::isValid(const Equipment& equipment, bool allowDefaults/* = false*/)
{
	RETURN_IF_STR_EMPTY(equipment.GetManufacturerName(), "Equipment Manufacturer Name");
	RETURN_IF_STR_EMPTY(equipment.GetManufacturerModelName(), "Equipment Manufacturer Model");

	if (!allowDefaults)
	{
		RETURN_IF_STR_EMPTY(equipment.GetManufacturerModelName(), "Manafacturer Model Name");
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
	RETURN_IF_STR_EMPTY(patient.GetName(), "Patient Name");
//	RETURN_IF_STR_EMPTY(patient.GetPatientID(), "Patient ID");

	if (allowDefaults)
	{
		RETURN_IF_NOT_VALID1(patient.GetBirthDate(), true, "Patient Birth Date");
	}
	else
	{
		RETURN_IF_NOT_VALID1(patient.GetBirthDate(), false, "Patient Birth Date");
		RETURN_IF_STR_EMPTY(patient.GetSex(), "Sex");
	}

	return true;
}

bool ModelValidator::isValid(const Inference& inference, bool allowDefaults/* = false*/)
{
	RETURN_IF_STR_EMPTY(inference.GetCodeValue(), "Inference Code Value");
	RETURN_IF_STR_EMPTY(inference.GetCodeMeaning(), "Inference Code Meaning");
	RETURN_IF_STR_EMPTY(inference.GetCodingSchemeDesignator(), "Inference Coding Scheme Designator");

	if (!allowDefaults)
	{
		RETURN_IF_STR_EMPTY(inference.GetCodingSchemeVersion(), "Inference Coding Scheme Version");

		if (inference.GetAnnotatorConfidence() == NULL)
			RETURN_WITH_ERROR("Inference's Confidence is not set");
	}

	return true;
}

bool ModelValidator::isValid(const Segmentation& segmentation, bool allowDefaults/* = false*/)
{
	RETURN_IF_UID_NOT_VALID(segmentation.GetSopInstanceUID(), "SOP Instance UID");
	RETURN_IF_UID_NOT_VALID(segmentation.GetSopClassUID(), "SOP Class UID");
	RETURN_IF_UID_NOT_VALID(segmentation.GetReferencedSopInstanceUID(), "Referenced SOP Instance UID");
	if (segmentation.GetImagingObservation() != NULL)
		RETURN_IF_NOT_VALID1(*segmentation.GetImagingObservation(), allowDefaults, "Segmentation's Imaging Observation is invalid");

	return true;
}

bool ModelValidator::isValid(const AimStatus& aimStatus, bool allowDefaults/* = false*/)
{
	if (aimStatus.GetAnnotationVersion() == 0.0)
		RETURN_WITH_ERROR("AimStatus Annotation Version is Invalid");

	RETURN_IF_STR_EMPTY(aimStatus.GetCodeValue(), "AimStatus Code Value");
	RETURN_IF_STR_EMPTY(aimStatus.GetCodeMeaning(), "AimStatus Code Meaning");
	RETURN_IF_STR_EMPTY(aimStatus.GetCodingSchemeDesignator(), "AimStatus Coding Scheme Designator");

	if (!allowDefaults)
	{
		RETURN_IF_STR_EMPTY(aimStatus.GetCodingSchemeVersion(), "AimStatus Coding Scheme Version");
		RETURN_IF_STR_EMPTY(aimStatus.GetAuthorizedBy(), "AimStatus Coding Scheme Version");
	}

	return true;
}

bool ModelValidator::isValid(const TextAnnotation& textAnnotation, bool allowDefaults/* = false*/)
{
	RETURN_IF_STR_EMPTY(textAnnotation.GetText(), "Annotation Text");

	if (textAnnotation.GetConnectorPoints() != NULL)
	{
		RETURN_IF_NOT_VALID1(*textAnnotation.GetConnectorPoints(), allowDefaults, "Text connection points are invalid");

		if (textAnnotation.GetConnectorPoints()->GetSpatialCoordinateCollection().size() > 2)
			RETURN_WITH_ERROR("No more than two text connection points are allowed");
	}

	if (!allowDefaults)
	{
		RETURN_IF_STR_EMPTY(textAnnotation.GetFont(), "Font");
		RETURN_IF_STR_EMPTY(textAnnotation.GetFontColor(), "Font Color");
		RETURN_IF_STR_EMPTY(textAnnotation.GetFontEffect(), "Font Effect");
		RETURN_IF_STR_EMPTY(textAnnotation.GetFontSize(), "Font Size");
		RETURN_IF_STR_EMPTY(textAnnotation.GetFontStyle(), "Font Style");
		RETURN_IF_STR_EMPTY(textAnnotation.GetFontOpacity(), "Font Opacity");
		RETURN_IF_STR_EMPTY(textAnnotation.GetTextJustify(), "Text Justify");
	}

	return true;
}

bool ModelValidator::isValid(const GeometricShape& geoShape, bool allowDefaults/* = false*/)
{
	//if (geoShape.GetShapeIdentifier() < 0)
	//	RETURN_WITH_ERROR("Shape Identifier should not be negative");

	if (geoShape.GetSpatialCoordinateCollection().size() < 1)
		RETURN_WITH_ERROR("Each Geometric Shape must have at least one Spatial Coordinate");

	if (geoShape.GetShapeType() == GeometricShape::SHT_Circle)
	{
		if (geoShape.GetSpatialCoordinateCollection().size() != 2)
			RETURN_WITH_ERROR("Circle must have two Spatial Coordinates associated with it.");
	}

	if (!allowDefaults)
	{
		RETURN_IF_STR_EMPTY(geoShape.GetLineColor(), "Line Color");
		RETURN_IF_STR_EMPTY(geoShape.GetLineOpacity(), "Line Opacity");
		RETURN_IF_STR_EMPTY(geoShape.GetLineStyle(), "Line Style");
		RETURN_IF_STR_EMPTY(geoShape.GetLineThickness(), "Line Thickness");
	}

	for (SpatialCoordPtrVector::const_iterator iter = geoShape.GetSpatialCoordinateCollection().begin(); iter < geoShape.GetSpatialCoordinateCollection().end(); iter++)
	{
		if (*iter == NULL)
		{
			RETURN_WITH_ERROR("Spatial Coordinate cannot be NULL");
		}
		else
		{
			RETURN_IF_NOT_VALID1(**iter, allowDefaults, "Spatial Coordinate is invalid");
		}
	}

	return true;
}

bool ModelValidator::isValid(const SpatialCoordinate& spatialCoordinate, bool allowDefaults/* = false*/)
{
	if (spatialCoordinate.GetCoordinateIndex() < 0)
		RETURN_WITH_ERROR("Spatial Coordinate index cannot be less that zero");

	if (spatialCoordinate.GetCoordinateType() == SpatialCoordinate::T_2D_SPCOORD)
	{
		const TwoDimensionSpatialCoordinate& twoDimensionSpatialCoord = dynamic_cast<const TwoDimensionSpatialCoordinate&>(spatialCoordinate);

		RETURN_IF_UID_NOT_VALID(twoDimensionSpatialCoord.GetImageReferenceUID(), "ImageReferenceUID");
		if (twoDimensionSpatialCoord.GetReferencedFrameNumber() < 0)
			RETURN_WITH_ERROR("Referenced Frame Number canont be negative");
		if (twoDimensionSpatialCoord.GetX() < 0)
			RETURN_WITH_ERROR("2D Spatial Coordinate (X) cannot be negative");
		if (twoDimensionSpatialCoord.GetY() < 0)
			RETURN_WITH_ERROR("2D Spatial Coordinate (Y) cannot be negative");
	}
	else if (spatialCoordinate.GetCoordinateType() == SpatialCoordinate::T_3D_SPCOORD)
	{
		const ThreeDimensionSpatialCoordinate& threeDimensionSpatialCoord = dynamic_cast<const ThreeDimensionSpatialCoordinate&>(spatialCoordinate);

		RETURN_IF_UID_NOT_VALID(threeDimensionSpatialCoord.GetFrameOfReferenceUID(), "FrameOfReferenceUID");
		if (threeDimensionSpatialCoord.GetX() < 0)
			RETURN_WITH_ERROR("3D Spatial Coordinate (X) cannot be negative");
		if (threeDimensionSpatialCoord.GetY() < 0)
			RETURN_WITH_ERROR("3D Spatial Coordinate (Y) cannot be negative");
		if (threeDimensionSpatialCoord.GetZ() < 0)
			RETURN_WITH_ERROR("3D Spatial Coordinate (Z) cannot be negative");
	}

	return true;
}

bool ModelValidator::isValid(const CharacteristicQuantification& characteristicQuantification, bool allowDefaults/* = false*/)
{
	RETURN_IF_STR_EMPTY(characteristicQuantification.GetName(), "Name");

	if (!allowDefaults)
	{
		if (characteristicQuantification.GetAnnotatorConfidence() == NULL)
			RETURN_WITH_ERROR("Characteristic Quantification's Confidence is not set");
	}

	if (characteristicQuantification.GetTypeName() == C_QUANTIFICATION_NUMERICAL_NAME)
		return isValid(dynamic_cast<const Numerical&>(characteristicQuantification), allowDefaults);
	else if(characteristicQuantification.GetTypeName() == C_QUANTIFICATION_QUANTILE_NAME)
		return isValid(dynamic_cast<const Quantile&>(characteristicQuantification), allowDefaults);
	else if(characteristicQuantification.GetTypeName() == C_QUANTIFICATION_NON_QUANTIFIABLE_NAME)
		return isValid(dynamic_cast<const NonQuantifiable&>(characteristicQuantification), allowDefaults);
	else if(characteristicQuantification.GetTypeName() == C_QUANTIFICATION_SCALE_NAME)
		return isValid(dynamic_cast<const Scale&>(characteristicQuantification), allowDefaults);
	else if(characteristicQuantification.GetTypeName() == C_QUANTIFICATION_INTERVAL_NAME)
		return isValid(dynamic_cast<const Interval&>(characteristicQuantification), allowDefaults);

	RETURN_WITH_ERROR("Unknown Quantification Type");
}

bool ModelValidator::isValid(const Numerical& numerical, bool allowDefaults/* = false*/)
{
	RETURN_IF_STR_EMPTY(numerical.GetUcumString(), "Numerical UCUM String");

	if (!allowDefaults)
	{
		if (numerical.GetOperator() == aim_lib::None || numerical.GetOperator() == aim_lib::InvalidComparisonOperatorType)
			RETURN_WITH_ERROR("Numerical's operator is not set to a valid value");
	}

	return true;
}

bool ModelValidator::isValid(const Quantile& quantile, bool allowDefaults/* = false*/)
{
	if (quantile.GetBin() == INT_MIN)
		RETURN_WITH_ERROR("Quantile's Bin is not set");

	return true;
}

bool ModelValidator::isValid(const NonQuantifiable& nonQuantifiable, bool allowDefaults/* = false*/)
{
	RETURN_IF_STR_EMPTY(nonQuantifiable.GetCodeValue(), "NonQuantifiable Code Value");
	RETURN_IF_STR_EMPTY(nonQuantifiable.GetCodeMeaning(), "NonQuantifiable Code Meaning");
	RETURN_IF_STR_EMPTY(nonQuantifiable.GetCodingSchemeDesignator(), "NonQuantifiable Coding Scheme Designator");

	if (!allowDefaults)
	{
		RETURN_IF_STR_EMPTY(nonQuantifiable.GetCodingSchemeVersion(), "NonQuantifiable Coding Scheme Version");
	}

	return true;
}

bool ModelValidator::isValid(const Scale& scale, bool allowDefaults/* = false*/)
{
	RETURN_IF_STR_EMPTY(scale.GetValue(), "Value");

	if (!allowDefaults)
	{
		RETURN_IF_STR_EMPTY(scale.GetComment(), "Comment");
		RETURN_IF_STR_EMPTY(scale.GetDescription(), "Description");
	}

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

bool ModelValidator::isValid(const Coordinate& coordinate, bool allowDefaults/* = false*/)
{
	if (coordinate.GetPosition() < 0)
		RETURN_WITH_ERROR("Coordinate position cannot be negative");
	if (coordinate.GetDimensionIndex() < 0)
		RETURN_WITH_ERROR("Coordinate's dimension index cannot be negative");

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

bool ModelValidator::isValid(const Dimension& dimension, bool allowDefaults/* = false*/)
{
	if (dimension.GetIndex() < 0)
		RETURN_WITH_ERROR("Dimension index cannot be negative");
	if (dimension.GetSize() < 0)
		RETURN_WITH_ERROR("Dimension side cannot be negative");

	RETURN_IF_STR_EMPTY(dimension.GetLabel(), "Dimension Label");

	return true;
}

bool ModelValidator::isValid(const CalculationResult& calcResult, bool allowDefaults/* = false*/)
{
	if (calcResult.GetNumberOfDimensions() < 1)
		RETURN_WITH_ERROR("Calculation Result's number of dimensions cannot be less that 1");
	if (calcResult.GetDimensionCollection().size() < 1)
		RETURN_WITH_ERROR("Calculation Result must have at least on dimension");

	if (calcResult.GetType() == InvalidCalculationResultType)
		RETURN_WITH_ERROR("Calculation Result type is not valid");

	RETURN_IF_STR_EMPTY(calcResult.GetUnitOfMeasure(), "Unit of Measure");

	for (DimensionVector::const_iterator iter = calcResult.GetDimensionCollection().begin(); iter < calcResult.GetDimensionCollection().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Calculation Result's dimension is invalid");

	for(CalculationDataVector::const_iterator iter = calcResult.GetCalculationDataCollection().begin(); iter < calcResult.GetCalculationDataCollection().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Calculation Result's data is invalid");

	return true;
}

bool ModelValidator::isValid(const ReferencedCalculation& referencedCalc, bool allowDefaults/* = false*/)
{
	RETURN_IF_UID_NOT_VALID(referencedCalc.GetUniqueIdentifier(), "Referenced Calculation Unique Identifier");

	return true;
}

bool ModelValidator::isValid(const ReferencedGeometricShape& referencedGeoShape, bool allowDefaults/* = false*/)
{
	// TODO: do we allow shape ID to be negative?

	return true;
}

bool ModelValidator::isValid(const Calculation& calculation, bool allowDefaults/* = false*/)
{
	RETURN_IF_UID_NOT_VALID(calculation.GetUID(), "Calculation UID");
	RETURN_IF_STR_EMPTY(calculation.GetDescription(), "Calculation Description");

	RETURN_IF_STR_EMPTY(calculation.GetCodeValue(), "Calculation Code Value");
	RETURN_IF_STR_EMPTY(calculation.GetCodeMeaning(), "Calculation Code Meaning");
	RETURN_IF_STR_EMPTY(calculation.GetCodingSchemeDesignator(), "Calculation Coding Scheme Designator");

	for (CalcResultVector::const_iterator iter = calculation.GetCalculationResultCollection().begin(); iter < calculation.GetCalculationResultCollection().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Calculation Result is invalid");

	for (ReferencedCalcVector::const_iterator iter = calculation.GetReferencedCalculationCollection().begin(); iter < calculation.GetReferencedCalculationCollection().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Referenced Calculation is invalid");

	for (ReferencedGeometricShapeVector::const_iterator iter = calculation.GetReferencedGeometricShapeCollection().begin(); iter < calculation.GetReferencedGeometricShapeCollection().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Referenced Geometric Shape is invalid");

	if (!allowDefaults)
	{
		RETURN_IF_STR_EMPTY(calculation.GetCodingSchemeVersion(), "Calculation Coding Scheme Version");
		RETURN_IF_STR_EMPTY(calculation.GetMathML(), "MathML");
		RETURN_IF_STR_EMPTY(calculation.GetAlgorithmName(), "AlgorithmName");
		RETURN_IF_STR_EMPTY(calculation.GetAlgorithmVersion(), "AlgorithmVersion");
	}

	return true;
}

bool ModelValidator::isValid(const ImageReference& imageRef, bool allowDefaults/* = false*/)
{
	if (imageRef.GetImageReferenceType() == ImageReference::T_DICOM_IMAGE_REF)
	{
		const DICOMImageReference& dicomImgRef = dynamic_cast<const DICOMImageReference&>(imageRef);

		for (PresentationStateVector::const_iterator iter = dicomImgRef.GetPresentationStateCollection().begin(); iter < dicomImgRef.GetPresentationStateCollection().end(); iter++)
			RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Presentation State is invalid");

		RETURN_IF_NOT_VALID1(dicomImgRef.GetStudy(), allowDefaults, "Study is invalid");
	}
	else if (imageRef.GetImageReferenceType() == ImageReference::T_WEB_IMAGE_REF)
	{
		// TODO - validate URI using regexp
	}

	return true;
}

bool ModelValidator::isValid(const ImageStudy& imageStudy, bool allowDefaults/* = false*/)
{
	RETURN_IF_UID_NOT_VALID(imageStudy.GetInstanceUID(), "Study Instance UID");
	RETURN_IF_NOT_VALID1(imageStudy.GetStartDate(), allowDefaults, "Start Date");
	RETURN_IF_NOT_VALID1(imageStudy.GetStartTime(), allowDefaults, "Start Time");
	RETURN_IF_NOT_VALID1(imageStudy.GetSeries(), allowDefaults, "Series");

	return true;
}

bool ModelValidator::isValid(const ImageSeries& series, bool allowDefaults/* = false*/)
{
	RETURN_IF_UID_NOT_VALID(series.GetInstanceUID(), "Series Instance UID");

	if (series.GetImageCollection().size() < 1)
		RETURN_WITH_ERROR("Image Series must include at least one image");

	for (ImageVector::const_iterator iter = series.GetImageCollection().begin(); iter < series.GetImageCollection().end(); iter++)
		RETURN_IF_NOT_VALID1(*iter, allowDefaults, "Image is invalid");

	return true;
}

bool ModelValidator::isValid(const Image& image, bool allowDefaults/* = false*/)
{
	RETURN_IF_UID_NOT_VALID(image.GetSopClassUID(), "Image SOP Class UID");
	RETURN_IF_UID_NOT_VALID(image.GetSopInstanceUID(), "Image SOP Instance UID");

	return true;
}

bool ModelValidator::isValid(const PresentationState& presentationState, bool allowDefaults/* = false*/)
{
	RETURN_IF_UID_NOT_VALID(presentationState.GetSopInstanceUID(), "SOP Instance UID");

	return true;
}

bool ModelValidator::isValid(const ReferencedAnnotation& referencedAnnotation, bool allowDefaults/* = false*/)
{
	RETURN_IF_UID_NOT_VALID(referencedAnnotation.GetReferencedAnnotationUID(), "Referenced Annotation UID");

	if (referencedAnnotation.GetAnnotationRole() != NULL)
		RETURN_IF_NOT_VALID1(*referencedAnnotation.GetAnnotationRole(), allowDefaults, "Annotation Role is invalid");

	return true;
}

bool ModelValidator::isValid(const AnnotationRole& annotationRole, bool allowDefaults/* = false*/)
{
	RETURN_IF_STR_EMPTY(annotationRole.GetCodeValue(), "Annotation Role Code Value");
	RETURN_IF_STR_EMPTY(annotationRole.GetCodeMeaning(), "Annotation Role Code Meaning");
	RETURN_IF_STR_EMPTY(annotationRole.GetCodingSchemeDesignator(), "Annotation Role Coding Scheme Designator");

	if (annotationRole.GetRoleSequenceNumber() == INT_MIN)
		RETURN_WITH_ERROR("Role Sequence Number is not set");

	if (!allowDefaults)
	{
		RETURN_IF_STR_EMPTY(annotationRole.GetCodingSchemeVersion(), "Annotation Role Coding Scheme Version");
	}

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