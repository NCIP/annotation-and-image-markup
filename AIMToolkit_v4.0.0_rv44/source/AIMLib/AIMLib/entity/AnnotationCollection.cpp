/*
*  Copyright Northwestern University
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

#include "../memdebug.h"

using std::string;
using namespace aim_lib;
using iso_21090::II;

AnnotationCollection::AnnotationCollection(void) : _aimVersion(AIMv4_0) {
}

AnnotationCollection::AnnotationCollection(const AnnotationCollection& annotationCollection){
	_uniqueIdentifier	= annotationCollection._uniqueIdentifier;
	_aimVersion			= annotationCollection._aimVersion;
	_description		= annotationCollection._description;
	_dateTime			= annotationCollection._dateTime;
	SetUser(annotationCollection.GetUser());
	SetEquipment(annotationCollection.GetEquipment());
}

AnnotationCollection::~AnnotationCollection(void){
}

const II& AnnotationCollection::GetUniqueIdentifier() const{
	return _uniqueIdentifier;
}

AimVersion AnnotationCollection::GetAimVersion() const{
	return _aimVersion;
}

const string& AnnotationCollection::GetDescription() const{
	return _description;
}

const DateTime& AnnotationCollection::GetDateTime() const{
	return _dateTime;
}

const User* AnnotationCollection::GetUser() const{
	return _user.get();
}

const Equipment* AnnotationCollection::GetEquipment() const{
	return _equipment.get();
}

void AnnotationCollection::SetUniqueIdentifier(const II& newVal){
	_uniqueIdentifier = newVal;
}

void AnnotationCollection::SetAimVersion(AimVersion newVal){
	_aimVersion = newVal;
}

void AnnotationCollection::SetDescription(const string& newVal){
	_description = newVal;
}

void AnnotationCollection::SetDateTime(const DateTime& newVal){
	_dateTime = newVal;
}

void AnnotationCollection::SetUser(const User* newVal){
	_user.reset(newVal ? new User(*newVal) : NULL);
}

void AnnotationCollection::SetEquipment(const Equipment* newVal){
	_equipment.reset(newVal ? new Equipment(*newVal) : NULL);
}
