/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "Inference.h"

#include "../memdebug.h"

using namespace aim_lib;

Inference::Inference(void)
{
	_imageEvidence = true;
}

Inference::Inference(const Inference& inference)
{
	*this = inference;
}

Inference::~Inference(void)
{
}

Inference& Inference::operator= (const Inference& inference){
	_cagridId				= inference._cagridId;
	_codeValue				= inference._codeValue;
	_codeMeaning			= inference._codeMeaning;
	_codingSchemeDesignator	= inference._codingSchemeDesignator;
	_codingSchemeVersion	= inference._codingSchemeVersion;
	_imageEvidence			= inference._imageEvidence;

	SetAnnotatorConfidence(inference.GetAnnotatorConfidence());

	return *this;
}

const std::string& Inference::GetCodeMeaning() const{

	return _codeMeaning;
}

const std::string& Inference::GetCodeValue() const{

	return _codeValue;
}

const std::string& Inference::GetCodingSchemeDesignator() const{

	return _codingSchemeDesignator;
}

const std::string& Inference::GetCodingSchemeVersion() const{

	return _codingSchemeVersion;
}

double* Inference::GetAnnotatorConfidence() const{
	return _annotatorConfidence.get();
}

bool Inference::GetImageEvidence() const{
	return _imageEvidence;
}

void Inference::SetCodeMeaning(const std::string& newVal){

	_codeMeaning = newVal;
}

void Inference::SetCodeValue(const std::string& newVal){

	_codeValue = newVal;
}

void Inference::SetCodingSchemeDesignator(const std::string& newVal){

	_codingSchemeDesignator = newVal;
}

void Inference::SetCodingSchemeVersion(const std::string& newVal){

	_codingSchemeVersion = newVal;
}

void Inference::SetAnnotatorConfidence(double* pConfidence){

	if (pConfidence == NULL)
		_annotatorConfidence.reset();
	else
		_annotatorConfidence.reset(new double(*pConfidence));
}

void Inference::SetImageEvidence(bool newVal){

	_imageEvidence = newVal;
}
