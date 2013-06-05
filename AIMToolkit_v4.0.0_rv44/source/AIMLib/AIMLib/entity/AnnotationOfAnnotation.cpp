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
#include "TimepointLesionObservationEntity.h"
#include "TaskContextEntity.h"
#include "AnnotationEntity.h"

#include "AdjudicationObservation.h"

#include "../statement/AnnotationStatement.h"
#include "../statement/AbstractAnnotationStatement.h"
#include "../statement/AnnotationOfAnnotationStatement.h"
#include "AnnotationOfAnnotation.h"

#include "../memdebug.h"

using namespace aim_lib;

AnnotationOfAnnotation::AnnotationOfAnnotation(void){
}

AnnotationOfAnnotation::AnnotationOfAnnotation(const AnnotationOfAnnotation& annotationOfAnnotation) : AnnotationEntity(annotationOfAnnotation){
	*this = annotationOfAnnotation;
}

AnnotationOfAnnotation& AnnotationOfAnnotation::operator=(const AnnotationOfAnnotation& annotationOfAnnotation){
	if (this != &annotationOfAnnotation)
	{
		AnnotationEntity::operator=(annotationOfAnnotation);
		SetAdjudicationObservation(annotationOfAnnotation.GetAdjudicationObservation());
		SetAnnotationOfAnnotationStatementCollection(annotationOfAnnotation.GetAnnotationOfAnnotationStatementCollection());
	}
	return *this;
}

AnnotationOfAnnotation::~AnnotationOfAnnotation(void){
	this->FreePtrVector<AnnotationStatement>(_annotationOfAnnotationStatementCollection);
}

AnnotationEntity::AnnotationType AnnotationOfAnnotation::GetAnnotationType() const{
	return AT_AnnotationOfAnnotation;
}

const AdjudicationObservation* AnnotationOfAnnotation::GetAdjudicationObservation() const{
	return _adjudicationObservation.get();
}

const AnnotationOfAnnotationStatementPtrVector& AnnotationOfAnnotation::GetAnnotationOfAnnotationStatementCollection() const{
	return _annotationOfAnnotationStatementCollection;
}

void AnnotationOfAnnotation::SetAdjudicationObservation(const AdjudicationObservation* newVal){
	_adjudicationObservation.reset(newVal ? new AdjudicationObservation(*newVal) : NULL);
}

void AnnotationOfAnnotation::SetAnnotationOfAnnotationStatementCollection(const AnnotationOfAnnotationStatementPtrVector& newVal){
	this->FreePtrVector<AnnotationStatement>(_annotationOfAnnotationStatementCollection);
	this->ClonePtrVector<AnnotationStatement>(newVal, _annotationOfAnnotationStatementCollection);
}
