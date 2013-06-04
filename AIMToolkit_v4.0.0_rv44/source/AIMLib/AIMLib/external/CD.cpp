/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
