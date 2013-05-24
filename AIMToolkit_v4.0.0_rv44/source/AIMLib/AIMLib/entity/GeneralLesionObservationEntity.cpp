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
