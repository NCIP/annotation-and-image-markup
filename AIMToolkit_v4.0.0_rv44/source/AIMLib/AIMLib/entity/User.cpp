/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "User.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;

User::User() : _numberWithinRoleOfClinicalTrial(-1){
}

User::User(const User& user){
	_name								= user._name;
	_loginName							= user._loginName;
	_roleInTrial						= user._roleInTrial;
	_numberWithinRoleOfClinicalTrial	= user._numberWithinRoleOfClinicalTrial;
}

User::~User(){
}

User* User::Clone() const{
	return new User(*this);
}

const string& User::GetName() const{
	return _name;
}

const string& User::GetLoginName() const{
	return _loginName;
}

const string& User::GetRoleInTrial() const{
	return _roleInTrial;
}

int User::GetNumberWithinRoleOfClinicalTrial() const{
	return _numberWithinRoleOfClinicalTrial;
}

void User::SetName(const string& newVal){
	_name = newVal;
}

void User::SetLoginName(const string& newVal){
	_loginName = newVal;
}

void User::SetRoleInTrial(const string& newVal){
	_roleInTrial = newVal;
}

void User::SetNumberWithinRoleOfClinicalTrial(int newVal){
	_numberWithinRoleOfClinicalTrial = newVal;
}
