/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "Entity.h"
#include "LesionObservationEntity.h"
#include "TimePointLesionObservationEntity.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;
using namespace iso_21090;

TimePointLesionObservationEntity::TimePointLesionObservationEntity(void){
}

TimePointLesionObservationEntity::TimePointLesionObservationEntity(const TimePointLesionObservationEntity& lesionObservationEntity) : LesionObservationEntity(lesionObservationEntity){
	*this = lesionObservationEntity;
}

TimePointLesionObservationEntity& TimePointLesionObservationEntity::operator=(const TimePointLesionObservationEntity& lesionObservationEntity){
	if (this != &lesionObservationEntity)
	{
		LesionObservationEntity::operator=(lesionObservationEntity);
		_calibration	= lesionObservationEntity._calibration;
		_comment		= lesionObservationEntity._comment;
		SetCanEvaluateLesion(lesionObservationEntity.GetCanEvaluateLesion());
		SetCanMeasureLesion(lesionObservationEntity.GetCanMeasureLesion());
		SetIsUnequivocalProgression(lesionObservationEntity.GetIsUnequivocalProgression());
		SetPredecessorLesionTrackingUid(lesionObservationEntity.GetPredecessorLesionTrackingUid());
		SetQualitativeAssessment(lesionObservationEntity.GetQualitativeAssessment());
		SetReasonUnableToEvaluate(lesionObservationEntity.GetReasonUnableToEvaluate());
		SetReasonUnableToMeasure(lesionObservationEntity.GetReasonUnableToMeasure());
		SetTherapeuticResponse(lesionObservationEntity.GetTherapeuticResponse());
	}
	return *this;
}

TimePointLesionObservationEntity* TimePointLesionObservationEntity::Clone() const{
	return new TimePointLesionObservationEntity(*this);
}

TimePointLesionObservationEntity::~TimePointLesionObservationEntity(void){
}

bool TimePointLesionObservationEntity::GetCalibration() const {
	return _calibration;
}

bool* TimePointLesionObservationEntity::GetCanEvaluateLesion() const{
	return _canEvaluateLesion.get();
}

bool* TimePointLesionObservationEntity::GetCanMeasureLesion() const{
	return _canMeasureLesion.get();
}

const string& TimePointLesionObservationEntity::GetComment() const{
	return _comment;
}

bool* TimePointLesionObservationEntity::GetIsUnequivocalProgression() const{
	return _isUnequivocalProgression.get();
}

const II* TimePointLesionObservationEntity::GetPredecessorLesionTrackingUid() const{
	return _predecessorLesionTrackingUid.get();
}

const CD* TimePointLesionObservationEntity::GetQualitativeAssessment() const{
	return _qualitativeAssessment.get();
}

const CD* TimePointLesionObservationEntity::GetReasonUnableToEvaluate() const{
	return _reasonUnableToEvaluate.get();
}

const CD* TimePointLesionObservationEntity::GetReasonUnableToMeasure() const{
	return _reasonUnableToMeasure.get();
}

const CD* TimePointLesionObservationEntity::GetTherapeuticResponse() const {
	return _therapeuticResponse.get();
}

void TimePointLesionObservationEntity::SetCalibration(bool newVal){
	_calibration = newVal;
}

void TimePointLesionObservationEntity::SetCanEvaluateLesion(bool* newVal){
	_canEvaluateLesion.reset(newVal ? new bool(*newVal) : NULL);
}

void TimePointLesionObservationEntity::SetCanMeasureLesion(bool* newVal){
	_canMeasureLesion.reset(newVal ? new bool(*newVal) : NULL);
}

void TimePointLesionObservationEntity::SetComment(const string& newVal){
	_comment = newVal;
}

void TimePointLesionObservationEntity::SetIsUnequivocalProgression(bool* newVal){
	_isUnequivocalProgression.reset(newVal ? new bool(*newVal) : NULL);
}

void TimePointLesionObservationEntity::SetPredecessorLesionTrackingUid(const II* newVal){
	_predecessorLesionTrackingUid.reset(newVal ? new II(*newVal) : NULL);
}

void TimePointLesionObservationEntity::SetQualitativeAssessment(const CD* newVal){
	_qualitativeAssessment.reset(newVal ? new CD(*newVal) : NULL);
}

void TimePointLesionObservationEntity::SetReasonUnableToEvaluate(const CD* newVal){
	_reasonUnableToEvaluate.reset(newVal ? new CD(*newVal) : NULL);
}

void TimePointLesionObservationEntity::SetReasonUnableToMeasure(const CD* newVal){
	_reasonUnableToMeasure.reset(newVal ? new CD(*newVal) : NULL);
}

void TimePointLesionObservationEntity::SetTherapeuticResponse(const CD* newVal){
	_therapeuticResponse.reset(newVal ? new CD(*newVal) : NULL);
}
