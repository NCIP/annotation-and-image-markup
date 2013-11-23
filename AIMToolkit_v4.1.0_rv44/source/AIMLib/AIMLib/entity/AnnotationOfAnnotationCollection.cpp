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
