/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "../stdafx.h"
#include "Entity.h"
#include "../util/DateTime.h"
#include "AuditTrail.h"
#include "CharacteristicQuantification.h"
#include "ImagingObservationCharacteristic.h"
#include "ImagingPhysicalEntityCharacteristic.h"
#include "ImagingPhysicalEntity.h"
#include "ImagingObservationEntity.h"
#include "InferenceEntity.h"
#include "../AimEnum.h"
#include "Parameter.h"
#include "Algorithm.h"
#include "Dimension.h"
#include "CalculationResult.h"
#include "CalculationEntity.h"
#include "AnnotationRoleEntity.h"
#include "LesionObservationEntity.h"
#include "GeneralLesionObservationEntity.h"
#include "TimepointLesionObservationEntity.h"
#include "TaskContextEntity.h"
#include "AnnotationEntity.h"
//ImageAnnotation includes
#include "ReferencedDicomObject.h"
#include "GeneralImage.h"
#include "ImagePlane.h"
#include "Image.h"
#include "ImageSeries.h"
#include "ImageStudy.h"
#include "ImageReferenceEntity.h"
#include "DicomImageReferenceEntity.h"
#include "UriImageReferenceEntity.h"
#include "MarkupEntity.h"
#include "GeometricShapeEntity.h"
#include "TextAnnotationEntity.h"
#include "SegmentationEntity.h"
#include "DicomSegmentationEntity.h"
#include "TwoDimensionSpatialCoordinate.h"
#include "TwoDimensionGeometricShapeEntity.h"
#include "ThreeDimensionSpatialCoordinate.h"
#include "ThreeDimensionGeometricShapeEntity.h"

#include "../statement/AnnotationStatement.h"
#include "../statement/AbstractAnnotationStatement.h"
#include "../statement/ImageAnnotationStatement.h"
#include "ImageAnnotation.h"

#include "../memdebug.h"

using namespace aim_lib;

ImageAnnotation::ImageAnnotation(void){
}

ImageAnnotation::ImageAnnotation(const ImageAnnotation& imageAnnotation) : AnnotationEntity(imageAnnotation){
	*this = imageAnnotation;
}

ImageAnnotation& ImageAnnotation::operator=(const ImageAnnotation& imageAnnotation){
	if (this != &imageAnnotation)
	{
		AnnotationEntity::operator=(imageAnnotation);
		SetImageAnnotationStatementCollection(imageAnnotation.GetImageAnnotationStatementCollection());
		SetImageReferenceEntityCollection(imageAnnotation.GetImageReferenceEntityCollection());
		SetMarkupEntityCollection(imageAnnotation.GetMarkupEntityCollection());
		SetSegmentationEntityCollection(imageAnnotation.GetSegmentationEntityCollection());
	}
	return *this;
}

ImageAnnotation::~ImageAnnotation(void){
	this->FreePtrVector<AnnotationStatement>(_imageAnnotationStatementCollection);
	this->FreePtrVector<ImageReferenceEntity>(_imageReferenceEntityCollection);
	this->FreePtrVector<MarkupEntity>(_markupEntityCollection);
	this->FreePtrVector<SegmentationEntity>(_segmentationEntityCollection);
}

AnnotationEntity::AnnotationType ImageAnnotation::GetAnnotationType() const{
	return AT_ImageAnnotation;
}

const ImageAnnotationStatementPtrVector& ImageAnnotation::GetImageAnnotationStatementCollection() const{
	return _imageAnnotationStatementCollection;
}

const ImageReferenceEntityPtrVector& ImageAnnotation::GetImageReferenceEntityCollection() const{
	return _imageReferenceEntityCollection;
}

const MarkupEntityPtrVector& ImageAnnotation::GetMarkupEntityCollection() const{
	return _markupEntityCollection;
}

const SegmentationEntityPtrVector& ImageAnnotation::GetSegmentationEntityCollection() const{
	return _segmentationEntityCollection;
}

void ImageAnnotation::SetImageAnnotationStatementCollection(const ImageAnnotationStatementPtrVector& newVal){
	this->FreePtrVector<AnnotationStatement>(_imageAnnotationStatementCollection);
	this->ClonePtrVector<AnnotationStatement>(newVal, _imageAnnotationStatementCollection);
}

void ImageAnnotation::SetImageReferenceEntityCollection(const ImageReferenceEntityPtrVector& newVal){
	this->FreePtrVector<ImageReferenceEntity>(_imageReferenceEntityCollection);
	this->ClonePtrVector<ImageReferenceEntity>(newVal, _imageReferenceEntityCollection);
}

void ImageAnnotation::SetMarkupEntityCollection(const MarkupEntityPtrVector& newVal){
	this->FreePtrVector<MarkupEntity>(_markupEntityCollection);
	this->ClonePtrVector<MarkupEntity>(newVal, _markupEntityCollection);
}

void ImageAnnotation::SetSegmentationEntityCollection(const SegmentationEntityPtrVector& newVal){
	this->FreePtrVector<SegmentationEntity>(_segmentationEntityCollection);
	this->ClonePtrVector<SegmentationEntity>(newVal, _segmentationEntityCollection);
}
