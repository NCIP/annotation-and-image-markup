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
