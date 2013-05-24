/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "Entity.h"
#include "LesionObservationEntity.h"

#include "../memdebug.h"

using namespace aim_lib;
using iso_21090::II;

LesionObservationEntity::LesionObservationEntity(void) : _isAdditionalObservation(false){
}

LesionObservationEntity::LesionObservationEntity(const LesionObservationEntity& lesionObservationEntity) : Entity(lesionObservationEntity){
	*this = lesionObservationEntity;
}

LesionObservationEntity& LesionObservationEntity::operator=(const LesionObservationEntity& lesionObservationEntity){
	if (this != &lesionObservationEntity)
	{
		_lesionUniqueIdentifier	= lesionObservationEntity._lesionUniqueIdentifier;
		SetIsAdditionalObservation(lesionObservationEntity.GetIsAdditionalObservation());
	}
	return *this;
}

LesionObservationEntity::~LesionObservationEntity(void){
}

const II& LesionObservationEntity::GetLesionUniqueIdentifier() const{
	return _lesionUniqueIdentifier;
}

bool* LesionObservationEntity::GetIsAdditionalObservation() const{
	return _isAdditionalObservation.get();
}

void LesionObservationEntity::SetLesionUniqueIdentifier(const II& newVal){
	_lesionUniqueIdentifier = newVal;
}

void LesionObservationEntity::SetIsAdditionalObservation(bool* newVal){
	_isAdditionalObservation.reset(newVal ? new bool(*newVal) : NULL);
}
