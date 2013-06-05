/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"
#include "../AimEnum.h"
#include "../util/DateTime.h"
#include "User.h"
#include "Equipment.h"
#include "AnnotationCollection.h"

#include "Entity.h"
#include "AuditTrail.h"
#include "CharacteristicQuantification.h"
#include "ImagingObservationCharacteristic.h"
#include "ImagingPhysicalEntityCharacteristic.h"
#include "ImagingPhysicalEntity.h"
#include "ImagingObservationEntity.h"
#include "InferenceEntity.h"
#include "Parameter.h"
#include "Algorithm.h"
#include "Dimension.h"
#include "CalculationResult.h"
#include "CalculationEntity.h"
#include "AnnotationRoleEntity.h"
#include "LesionObservationEntity.h"
#include "GeneralLesionObservationEntity.h"
#include "TimePointLesionObservationEntity.h"
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
#include "UriImageReferenceEntity.h"
#include "DicomImageReferenceEntity.h"
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

#include "Person.h"
#include "ImageAnnotationCollection.h"

#include "../memdebug.h"

using namespace aim_lib;

ImageAnnotationCollection::ImageAnnotationCollection(void){
}

ImageAnnotationCollection::ImageAnnotationCollection(const ImageAnnotationCollection& annotationCollection){
	SetPerson(annotationCollection.GetPerson());
	SetImageAnnotations(annotationCollection.GetImageAnnotations());
}

ImageAnnotationCollection* ImageAnnotationCollection::Clone() const{
	return new ImageAnnotationCollection(*this);
}

ImageAnnotationCollection::~ImageAnnotationCollection(void){
}

AnnotationCollection::AnnotationCollectionType ImageAnnotationCollection::GetAnnotationCollectionType() const{
	return ACT_ImageAnnotationCollection;
}

void ImageAnnotationCollection::ClearAnnotations(){
	_imageAnnotationCollection.clear();
}

const Person* ImageAnnotationCollection::GetPerson() const{
	return _person.get();
}

const ImageAnnotationVector& ImageAnnotationCollection::GetImageAnnotations() const{
	return _imageAnnotationCollection;
}

void ImageAnnotationCollection::SetPerson(const Person* newVal){
	_person.reset(newVal ? new Person(*newVal) : NULL);
}

void ImageAnnotationCollection::SetImageAnnotations(const ImageAnnotationVector& newVal){
	_imageAnnotationCollection.assign(newVal.begin(), newVal.end());
}
