/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "AimStatus.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;

AimStatus::AimStatus(void)
{
	_annotationVersion = 0.0;
}

AimStatus::AimStatus(const AimStatus& aimStatus)
{
	_cagridId				= aimStatus._cagridId;
	_annotationVersion		= aimStatus._annotationVersion;
	_codeMeaning			= aimStatus._codeMeaning;
	_codeValue				= aimStatus._codeValue;
	_codingSchemeDesignator	= aimStatus._codingSchemeDesignator;
	_codingSchemeVersion	= aimStatus._codingSchemeVersion;
	_authorizedBy			= aimStatus._authorizedBy;
}

AimStatus::~AimStatus(void)
{
}

AimStatus* AimStatus::Clone() const
{
	return new AimStatus(*this);
}

double AimStatus::GetAnnotationVersion() const
{
	return _annotationVersion;
}

const string& AimStatus::GetCodeMeaning() const
{
	return _codeMeaning;
}

const string& AimStatus::GetCodeValue() const
{
	return _codeValue;
}

const string& AimStatus::GetCodingSchemeDesignator() const
{
	return _codingSchemeDesignator;
}

const string& AimStatus::GetCodingSchemeVersion() const
{
	return _codingSchemeVersion;
}

const string& AimStatus::GetAuthorizedBy() const
{
	return _authorizedBy;
}

void AimStatus::SetAnnotationVersion(double newVal)
{
	_annotationVersion = newVal;
}

void AimStatus::SetCodeMeaning(const string& newVal)
{
	_codeMeaning = newVal;
}

void AimStatus::SetCodeValue(const string& newVal)
{
	_codeValue = newVal;
}

void AimStatus::SetCodingSchemeDesignator(const string& newVal)
{
	_codingSchemeDesignator = newVal;
}

void AimStatus::SetCodingSchemeVersion(const string& newVal)
{
	_codingSchemeVersion = newVal;
}

void AimStatus::SetAuthorizedBy(const string& newVal)
{
	_authorizedBy = newVal;
}
