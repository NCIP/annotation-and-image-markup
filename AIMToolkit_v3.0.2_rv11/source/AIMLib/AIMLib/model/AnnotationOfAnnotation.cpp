/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "../AimEnum.h"

#include "AimBase.h"
#include "DateTime.h"
#include "User.h"
#include "Equipment.h"
#include "AimStatus.h"
#include "ReferencedGeometricShape.h"
#include "CharacteristicQuantification.h"
#include "AnatomicEntityCharacteristic.h"
#include "AnatomicEntity.h"
#include "ImagingObservationCharacteristic.h"
#include "ImagingObservation.h"
#include "ReferencedCalculation.h"
#include "Dimension.h"
#include "Coordinate.h"
#include "CalculationData.h"
#include "CalculationResult.h"
#include "Calculation.h"
#include "Inference.h"
#include "Annotation.h"
#include "AnnotationRole.h"
#include "ReferencedAnnotation.h"
#include "AnnotationOfAnnotation.h"

using std::string;
using namespace aim_lib;

AnnotationOfAnnotation::AnnotationOfAnnotation() : Annotation(C_ANNOTATATION_ANNOTATION_NAME){

}

AnnotationOfAnnotation::AnnotationOfAnnotation(const AnnotationOfAnnotation& annotationOfAnnotation) :
	Annotation(annotationOfAnnotation)
{
	this->SetReferencedAnnotationCollection(annotationOfAnnotation._referenceAnnotationCollection);
}

AnnotationOfAnnotation::~AnnotationOfAnnotation(){

}

Annotation::AnnotationKind AnnotationOfAnnotation::GetAnnotationKind() const
{
	return Annotation::AK_AnnotationOfAnnotation;
}

const ReferencedAnnotationVector& AnnotationOfAnnotation::GetReferencedAnnotationCollection() const{

	return  _referenceAnnotationCollection;;
}

void AnnotationOfAnnotation::SetReferencedAnnotationCollection(const ReferencedAnnotationVector& referencedAnnotationCollection){
	_referenceAnnotationCollection.assign(referencedAnnotationCollection.begin(), referencedAnnotationCollection.end());
}
