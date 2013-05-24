/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
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
#include "AdjudicationObservation.h"

//ImageAnnotation includes
#include "ReferencedDicomObject.h"
#include "GeneralImage.h"
#include "ImagePlane.h"
#include "Image.h"
#include "ImageSeries.h"
#include "ImageStudy.h"
#include "ImageReferenceEntity.h"
#include "DicomImageReferenceEntity.h"
#include "MarkupEntity.h"
#include "SegmentationEntity.h"
#include "DicomSegmentationEntity.h"
#include "ImageReferenceEntity.h"
#include "UriImageReferenceEntity.h"
#include "GeometricShapeEntity.h"
#include "TextAnnotationEntity.h"
#include "TwoDimensionSpatialCoordinate.h"
#include "TwoDimensionGeometricShapeEntity.h"
#include "ThreeDimensionSpatialCoordinate.h"
#include "ThreeDimensionGeometricShapeEntity.h"

#include "../statement/AnnotationStatement.h"
#include "../statement/AbstractAnnotationStatement.h"
#include "../statement/AnnotationOfAnnotationStatement.h"
#include "../statement/ImageAnnotationStatement.h"
#include "ImageAnnotation.h"
#include "AnnotationOfAnnotation.h"

#include "AnnotationOfAnnotationCollection.h"

#include "../memdebug.h"

using namespace aim_lib;

AnnotationOfAnnotationCollection::AnnotationOfAnnotationCollection(void){
}

AnnotationOfAnnotationCollection::AnnotationOfAnnotationCollection(const AnnotationOfAnnotationCollection& annotationCollection) : AnnotationCollection(annotationCollection){
	SetAnnotationOfAnnotations(annotationCollection.GetAnnotationOfAnnotations());                                        
}

AnnotationOfAnnotationCollection* AnnotationOfAnnotationCollection::Clone(void) const{
	return new AnnotationOfAnnotationCollection(*this);
}

AnnotationOfAnnotationCollection::~AnnotationOfAnnotationCollection(void){
}

AnnotationCollection::AnnotationCollectionType AnnotationOfAnnotationCollection::GetAnnotationCollectionType() const{
	return ACT_AnnotationOfAnnotationCollection;
}

void AnnotationOfAnnotationCollection::ClearAnnotations(){
	_annotationOfAnnotationCollection.clear();
}

const AnnotationOfAnnotationVector& AnnotationOfAnnotationCollection::GetAnnotationOfAnnotations() const{
	return _annotationOfAnnotationCollection;                          
}

void AnnotationOfAnnotationCollection::SetAnnotationOfAnnotations(const AnnotationOfAnnotationVector& newVal){
	_annotationOfAnnotationCollection.assign(newVal.begin(), newVal.end());                                                                               
}
