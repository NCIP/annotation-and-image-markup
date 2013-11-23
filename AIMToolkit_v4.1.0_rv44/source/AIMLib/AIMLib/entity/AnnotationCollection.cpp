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
