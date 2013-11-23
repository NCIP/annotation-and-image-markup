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
#include "Parameter.h"
#include "Algorithm.h"

using std::string;
using namespace aim_lib;
using namespace iso_21090;

Algorithm::Algorithm(void){
}

Algorithm::Algorithm(const Algorithm& algorithm){
	_name			= algorithm._name;
	_version		= algorithm._version;
	_description	= algorithm._description;
	SetType(algorithm.GetType());
	SetUniqueIdentifier(algorithm.GetUniqueIdentifier());
	SetParameterCollection(algorithm.GetParameterCollection());
}

Algorithm::~Algorithm(void){
}

const string& Algorithm::GetName() const {
	return _name;
}

const CDVector& Algorithm::GetType() const {
	return _type;
}

const II* Algorithm::GetUniqueIdentifier() const {
	return _uniqueIdentifier.get();
}

const string& Algorithm::GetVersion() const {
	return _version;
}

const string& Algorithm::GetDescription() const{
	return _description;
}

const ParameterVector& Algorithm::GetParameterCollection() const{
	return _parameterCollection;
}

void Algorithm::SetName(const std::string& newVal){
	_name = newVal;
}

void Algorithm::SetType(const iso_21090::CDVector& newVal){
	_type.assign(newVal.begin(), newVal.end());
}

void Algorithm::SetUniqueIdentifier(const iso_21090::II* newVal){
	_uniqueIdentifier.reset(newVal ? new II(*newVal) : NULL);
}

void Algorithm::SetVersion(const std::string& newVal){
	_version = newVal;
}

void Algorithm::SetDescription(const std::string& newVal){
	_description = newVal;
}

void Algorithm::SetParameterCollection(const ParameterVector& parameters){
	_parameterCollection.assign(parameters.begin(), parameters.end());
}
