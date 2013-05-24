/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include <limits.h>

#include "AnnotationRole.h"

#include "../memdebug.h"

using namespace aim_lib;

AnnotationRole::AnnotationRole(void) : _roleSequenceNumber(INT_MIN) {
}

AnnotationRole::AnnotationRole(const AnnotationRole& annotationRole){
	*this = annotationRole;
}

AnnotationRole::~AnnotationRole(void){
}

AnnotationRole& AnnotationRole::operator= (const AnnotationRole& annotationRole){
	_cagridId				= annotationRole._cagridId;
	_codeMeaning			= annotationRole._codeMeaning;
	_codeValue				= annotationRole._codeValue;
	_codingSchemeDesignator	= annotationRole._codingSchemeDesignator;
	_codingSchemeVersion	= annotationRole._codingSchemeVersion;
	_roleSequenceNumber		= annotationRole._roleSequenceNumber;

	return *this;
}

AnnotationRole* AnnotationRole::Clone() const{

	return new AnnotationRole(*this);
}

const std::string& AnnotationRole::GetCodeMeaning() const{

	return _codeMeaning;
}

const std::string& AnnotationRole::GetCodeValue() const{

	return _codeValue;
}

const std::string& AnnotationRole::GetCodingSchemeDesignator() const{

	return _codingSchemeDesignator;
}

const std::string& AnnotationRole::GetCodingSchemeVersion() const{

	return _codingSchemeVersion;
}

int AnnotationRole::GetRoleSequenceNumber() const{
	return _roleSequenceNumber;
}

void AnnotationRole::SetCodeMeaning(const std::string& newVal){

	_codeMeaning = newVal;
}

void AnnotationRole::SetCodeValue(const std::string& newVal){

	_codeValue = newVal;
}

void AnnotationRole::SetCodingSchemeDesignator(const std::string& newVal){

	_codingSchemeDesignator = newVal;
}

void AnnotationRole::SetCodingSchemeVersion(const std::string& newVal){

	_codingSchemeVersion = newVal;
}

void AnnotationRole::SetRoleSequenceNumber(int newVal){
	_roleSequenceNumber = newVal;
}
