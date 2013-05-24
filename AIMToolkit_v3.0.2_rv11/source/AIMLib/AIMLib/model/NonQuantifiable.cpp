/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "AimBase.h"
#include "CharacteristicQuantification.h"
#include "NonQuantifiable.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;

NonQuantifiable::NonQuantifiable(void) : CharacteristicQuantification(C_QUANTIFICATION_NON_QUANTIFIABLE_NAME)
{
}

NonQuantifiable::NonQuantifiable(const NonQuantifiable& nonQuantifiable) : CharacteristicQuantification(nonQuantifiable)
{
	*this = nonQuantifiable;
}

NonQuantifiable::~NonQuantifiable(void)
{
}

NonQuantifiable& NonQuantifiable::operator=(const NonQuantifiable& nonQuantifiable)
{
	if (this != &nonQuantifiable)
	{
		CharacteristicQuantification::operator=(nonQuantifiable);
		_codeMeaning			= nonQuantifiable._codeMeaning;
		_codeValue				= nonQuantifiable._codeValue;
		_codingSchemeDesignator	= nonQuantifiable._codingSchemeDesignator;
		_codingSchemeVersion	= nonQuantifiable._codingSchemeVersion;
	}
	return *this;
}

NonQuantifiable* NonQuantifiable::Clone() const
{
	return new NonQuantifiable(*this);
}

const string& NonQuantifiable::GetCodeMeaning() const{

	return _codeMeaning;
}

const string& NonQuantifiable::GetCodeValue() const{

	return _codeValue;
}

const string& NonQuantifiable::GetCodingSchemeDesignator() const{

	return _codingSchemeDesignator;
}

const string& NonQuantifiable::GetCodingSchemeVersion() const{

	return _codingSchemeVersion;
}

void NonQuantifiable::SetCodeMeaning(const string& newVal){

	_codeMeaning = newVal;
}

void NonQuantifiable::SetCodeValue(const string& newVal){

	_codeValue = newVal;
}

void NonQuantifiable::SetCodingSchemeDesignator(const string& newVal){

	_codingSchemeDesignator = newVal;
}

void NonQuantifiable::SetCodingSchemeVersion(const string& newVal){

	_codingSchemeVersion = newVal;
}
