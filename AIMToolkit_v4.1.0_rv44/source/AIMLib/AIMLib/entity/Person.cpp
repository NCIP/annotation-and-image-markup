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
#include "../util/DateTime.h"
#include "Person.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;

Person::Person(){
}

Person::Person(const Person& person){
	_id				= person._id;
	_name			= person._name;
	_birthDate		= person._birthDate;
	_sex			= person._sex;
	_ethnicGroup	= person._ethnicGroup;
}

Person::~Person(){
}

Person* Person::Clone() const {
	return new Person(*this);
}

const string& Person::GetId() const {
	return _id;
}

const string& Person::GetName() const {
	return _name;
}

const Date& Person::GetBirthDate() const {
	return _birthDate;
}

const string& Person::GetSex() const {
	return _sex;
}

const string& Person::GetEthnicGroup() const {
	return _ethnicGroup;
}

void Person::SetId(const string& newVal) {
	_id = newVal;
}

void Person::SetName(const string& newVal) {
	_name = newVal;
}

void Person::SetBirthDate(const Date& newVal) {
	_birthDate = newVal;
}

void Person::SetSex(const string& newVal) {
	_sex = newVal;
}

void Person::SetEthnicGroup(const string& newVal) {
	_ethnicGroup = newVal;
}
