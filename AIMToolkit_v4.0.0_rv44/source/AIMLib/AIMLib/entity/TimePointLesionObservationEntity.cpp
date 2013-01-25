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
