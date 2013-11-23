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
#include "GeneralLesionObservationEntity.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;
using iso_21090::CD;

GeneralLesionObservationEntity::GeneralLesionObservationEntity(void){
}

GeneralLesionObservationEntity::GeneralLesionObservationEntity(const GeneralLesionObservationEntity& lesionObservationEntity) : LesionObservationEntity(lesionObservationEntity){
	*this = lesionObservationEntity;
}

GeneralLesionObservationEntity& GeneralLesionObservationEntity::operator=(const GeneralLesionObservationEntity& lesionObservationEntity){
	if (this != &lesionObservationEntity)
	{
		LesionObservationEntity::operator=(lesionObservationEntity);
		_lesionType				= lesionObservationEntity._lesionType;
		_trackingIdentifier		= lesionObservationEntity._trackingIdentifier;
		SetLaterality(lesionObservationEntity.GetLaterality());
		SetReconstructionInterval(lesionObservationEntity.GetReconstructionInterval());
	}
	return *this;
}

GeneralLesionObservationEntity* GeneralLesionObservationEntity::Clone() const{
	return new GeneralLesionObservationEntity(*this);
}

GeneralLesionObservationEntity::~GeneralLesionObservationEntity(void){
}

const CD& GeneralLesionObservationEntity::GetLesionType() const{
	return _lesionType;
}

const string& GeneralLesionObservationEntity::GetTrackingIdentifier() const{
	return _trackingIdentifier;
}

const CD* GeneralLesionObservationEntity::GetLaterality() const{
	return _laterality.get();
}

const CD* GeneralLesionObservationEntity::GetReconstructionInterval() const{
	return _reconstructionInterval.get();
}

void GeneralLesionObservationEntity::SetLesionType(const CD& newVal){
	_lesionType = newVal;
}

void GeneralLesionObservationEntity::SetTrackingIdentifier(const string& newVal){
	_trackingIdentifier = newVal;
}

void GeneralLesionObservationEntity::SetLaterality(const CD* newVal){
	_laterality.reset(newVal ? new CD(*newVal) : NULL);
}

void GeneralLesionObservationEntity::SetReconstructionInterval(const CD* newVal){
	_reconstructionInterval.reset(newVal ? new CD(*newVal) : NULL);
}
