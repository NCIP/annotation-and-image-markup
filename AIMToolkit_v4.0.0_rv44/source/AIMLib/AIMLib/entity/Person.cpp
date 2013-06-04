/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
