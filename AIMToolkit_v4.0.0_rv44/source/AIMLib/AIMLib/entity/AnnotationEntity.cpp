/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"
#include "../util/DateTime.h"
#include "../AimEnum.h"
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
#include "TaskContextEntity.h"
#include "AnnotationEntity.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;
using namespace iso_21090;

AnnotationEntity::AnnotationEntity(){
}

AnnotationEntity::AnnotationEntity(const AnnotationEntity& annotationEntity) : Entity(annotationEntity){
	*this = annotationEntity;
}

AnnotationEntity& AnnotationEntity::operator=(const AnnotationEntity& annotationEntity){
	if (this != &annotationEntity)
	{
		Entity::operator=(annotationEntity);
		SetTypeCode(annotationEntity._typeCode);
		_dateTime	= annotationEntity._dateTime;
		_name		= annotationEntity._name;
		_comment	= annotationEntity._comment;
		SetPrecedentReferencedAnnotationUid(annotationEntity.GetPrecedentReferencedAnnotationUid());
		SetTemplateUid(annotationEntity.GetTemplateUid());

		SetImagingPhysicalEntityCollection(annotationEntity.GetImagingPhysicalEntityCollection());
		SetImagingObservationEntityCollection(annotationEntity.GetImagingObservationEntityCollection());
		SetInferenceEntityCollection(annotationEntity.GetInferenceEntityCollection());
		SetCalculationEntityCollection(annotationEntity.GetCalculationEntityCollection());
		SetAnnotationRoleEntityCollection(annotationEntity.GetAnnotationRoleEntityCollection());
		SetLesionOservationEntityCollection(annotationEntity.GetLesionObservationEntityCollection());
		SetAuditTrailCollection(annotationEntity.GetAuditTrailCollection());
		SetTaskContextEntityCollection(annotationEntity.GetTaskContextEntityCollection());
	}
	return *this;
}

AnnotationEntity::~AnnotationEntity(void){
	this->FreePtrVector<LesionObservationEntity>(_lesionObservationEntityCollection);
}

const CDVector& AnnotationEntity::GetTypeCode() const{
	return _typeCode;
}

const DateTime& AnnotationEntity::GetDateTime() const{
	return _dateTime;
}

const string& AnnotationEntity::GetName() const{
	return _name;
}

const string& AnnotationEntity::GetComment() const{
	return _comment;
}

II* AnnotationEntity::GetPrecedentReferencedAnnotationUid() const{
	return _precedentReferencedAnnotationUid.get();
}

II* AnnotationEntity::GetTemplateUid() const{
	return _templateUid.get();
}

const ImagingPhysicalEntityVector& AnnotationEntity::GetImagingPhysicalEntityCollection() const{
	return _imagingPhysicalEntityCollection;
}

const ImagingObservationEntityVector& AnnotationEntity::GetImagingObservationEntityCollection() const{
	return _imagingObservationEntityCollection;
}

const InferenceEntityVector& AnnotationEntity::GetInferenceEntityCollection() const{
	return _inferenceEntityCollection;
}

const CalculationEntityVector& AnnotationEntity::GetCalculationEntityCollection() const{
	return _calculationEntityCollection;
}

const AnnotationRoleEntityVector& AnnotationEntity::GetAnnotationRoleEntityCollection() const{
	return _annotationRoleEntityCollection;
}
const LesionObservationEntityPtrVector& AnnotationEntity::GetLesionObservationEntityCollection() const{
	return _lesionObservationEntityCollection;
}

const AuditTrailVector& AnnotationEntity::GetAuditTrailCollection() const{
	return _auditTrailCollection;
}

const TaskContextEntityVector& AnnotationEntity::GetTaskContextEntityCollection() const{
	return _taskContextEntityCollection;
}


void AnnotationEntity::SetTypeCode(const CDVector& typeCode){
	_typeCode.assign(typeCode.begin(), typeCode.end());
}

void AnnotationEntity::SetDateTime(const DateTime& dateTime){
	_dateTime = dateTime;
}

void AnnotationEntity::SetName(const string& name){
	_name = name;
}

void AnnotationEntity::SetComment(const string& comment){
	_comment = comment;
}

void AnnotationEntity::SetPrecedentReferencedAnnotationUid(II* precedentAnnotationUid){
	_precedentReferencedAnnotationUid.reset(precedentAnnotationUid ? new II(*precedentAnnotationUid) : NULL);
}

void AnnotationEntity::SetTemplateUid(II* templateUid){
	_templateUid.reset(templateUid ? new II(*templateUid) : NULL);
}

void AnnotationEntity::SetImagingPhysicalEntityCollection(const ImagingPhysicalEntityVector& imagingPhysicalEntities){
	_imagingPhysicalEntityCollection.assign(imagingPhysicalEntities.begin(), imagingPhysicalEntities.end());
}

void AnnotationEntity::SetImagingObservationEntityCollection(const ImagingObservationEntityVector& imagingObservationEntities){
	_imagingObservationEntityCollection.assign(imagingObservationEntities.begin(), imagingObservationEntities.end());
}

void AnnotationEntity::SetInferenceEntityCollection(const InferenceEntityVector& inferenceEntities){
	_inferenceEntityCollection.assign(inferenceEntities.begin(), inferenceEntities.end());
}

void AnnotationEntity::SetCalculationEntityCollection(const CalculationEntityVector& calculationEntities){
	_calculationEntityCollection.assign(calculationEntities.begin(), calculationEntities.end());
}

void AnnotationEntity::SetAnnotationRoleEntityCollection(const AnnotationRoleEntityVector& annotationRoleEntities){
	_annotationRoleEntityCollection.assign(annotationRoleEntities.begin(), annotationRoleEntities.end());
}

void AnnotationEntity::SetAuditTrailCollection(const AuditTrailVector& auditTrails){
	_auditTrailCollection.assign(auditTrails.begin(), auditTrails.end());
}

void AnnotationEntity::SetTaskContextEntityCollection(const TaskContextEntityVector& taskContextEntities) {
	_taskContextEntityCollection.assign(taskContextEntities.begin(), taskContextEntities.end());
}

void AnnotationEntity::SetLesionOservationEntityCollection(const LesionObservationEntityPtrVector& lesionObservationEntities) {
	this->FreePtrVector<LesionObservationEntity>(_lesionObservationEntityCollection);

	this->ClonePtrVector<LesionObservationEntity>(lesionObservationEntities, _lesionObservationEntityCollection);
}
