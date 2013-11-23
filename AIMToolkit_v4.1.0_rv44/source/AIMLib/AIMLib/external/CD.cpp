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

#include "CD.h"

using namespace aim_lib::iso_21090;
using std::string;

CD::CD(void){
}

CD::CD(const string& codeValue, const string& codeMeaning, const string& codingSchemeDesignator, const string& codingSchemeVersion){
	_codeValue				= codeValue;
	_codeMeaning			= codeMeaning;
	_codingSchemeDesignator	= codingSchemeDesignator;
	_codingSchemeVersion	= codingSchemeVersion;
}

CD::CD(const CD& cd){
	*this = cd;
}

CD::~CD(void){
}

CD& CD::operator=(const CD& cd){
	if (this != &cd) {
		_codeValue				= cd._codeValue;
		_codeMeaning			= cd._codeMeaning;
		_codingSchemeDesignator	= cd._codingSchemeDesignator;
		_codingSchemeVersion	= cd._codingSchemeVersion;
	}

	return *this;
}

bool CD::operator==(const CD& cd) const{
	return
		_codeValue				== cd._codeValue &&
		_codeMeaning			== cd._codeMeaning &&
		_codingSchemeDesignator	== cd._codingSchemeDesignator &&
		_codingSchemeVersion	== cd._codingSchemeVersion;
}

const string& CD::GetCodeValue() const{
	return _codeValue;
}

const string& CD::GetCodeMeaning() const{
	return _codeMeaning;
}

const string& CD::GetCodingSchemeDesignator() const{
	return _codingSchemeDesignator;
}

const string& CD::GetCodingSchemeVersion() const{
	return _codingSchemeVersion;
}

void CD::SetCodeValue(const string& newVal){
	_codeValue = newVal;
}

void CD::SetCodeMeaning(const string& newVal){
	_codeMeaning = newVal;
}

void CD::SetCodingSchemeDesignator(const string& newVal){
	_codingSchemeDesignator = newVal;
}

void CD::SetCodingSchemeVersion(const string& newVal){
	_codingSchemeVersion = newVal;
}
