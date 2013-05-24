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
#include "AnatomicEntityCharacteristic.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;

AnatomicEntityCharacteristic::AnatomicEntityCharacteristic(void){
}

AnatomicEntityCharacteristic::AnatomicEntityCharacteristic(const AnatomicEntityCharacteristic& anatomicEntCharacteristic){
	*this = anatomicEntCharacteristic;
}


AnatomicEntityCharacteristic& AnatomicEntityCharacteristic::operator= (const AnatomicEntityCharacteristic& anatomicEntCharacteristic){
	if (this != &anatomicEntCharacteristic)
	{
		_cagridId				= anatomicEntCharacteristic._cagridId;
		_codeMeaning			= anatomicEntCharacteristic._codeMeaning;
		_codeValue				= anatomicEntCharacteristic._codeValue;
		_codingSchemeDesignator	= anatomicEntCharacteristic._codingSchemeDesignator;
		_codingSchemeVersion	= anatomicEntCharacteristic._codingSchemeVersion;
		_label					= anatomicEntCharacteristic._label;

		SetAnnotatorConfidence(anatomicEntCharacteristic.GetAnnotatorConfidence());
		SetCharacteristicQuantificationCollection(anatomicEntCharacteristic.GetCharacteristicQuantificationCollection());
	}

	return *this;
}

AnatomicEntityCharacteristic::~AnatomicEntityCharacteristic(void){

	// Characteristic Quantifications Collection
	this->FreeAllCharacteristicQuantifications();
}

AnatomicEntityCharacteristic* AnatomicEntityCharacteristic::Clone() const{

	return new AnatomicEntityCharacteristic(*this);
}

const string& AnatomicEntityCharacteristic::GetCodeMeaning() const{

	return _codeMeaning;
}

const string& AnatomicEntityCharacteristic::GetCodeValue() const{

	return _codeValue;
}

const string& AnatomicEntityCharacteristic::GetCodingSchemeDesignator() const{

	return _codingSchemeDesignator;
}

const string& AnatomicEntityCharacteristic::GetCodingSchemeVersion() const{

	return _codingSchemeVersion;
}

double* AnatomicEntityCharacteristic::GetAnnotatorConfidence() const{
	return _annotatorConfidence.get();
}

const string& AnatomicEntityCharacteristic::GetLabel() const{
	return _label;
}

const CharacteristicQuantificationPtrVector& AnatomicEntityCharacteristic::GetCharacteristicQuantificationCollection() const
{
	return _characteristicQuantificationCollection;
}

void AnatomicEntityCharacteristic::SetCodeMeaning(const string& newVal){

	_codeMeaning = newVal;
}

void AnatomicEntityCharacteristic::SetCodeValue(const string& newVal){

	_codeValue = newVal;
}

void AnatomicEntityCharacteristic::SetCodingSchemeDesignator(const string& newVal){

	_codingSchemeDesignator = newVal;
}

void AnatomicEntityCharacteristic::SetCodingSchemeVersion(const string& newVal){

	_codingSchemeVersion = newVal;
}

void AnatomicEntityCharacteristic::SetAnnotatorConfidence(double *pNewVal){
	if (pNewVal == NULL)
		_annotatorConfidence.reset();
	else
		_annotatorConfidence.reset(new double(*pNewVal));
}

void AnatomicEntityCharacteristic::SetLabel(const string& newVal){
	_label = newVal;
}

void AnatomicEntityCharacteristic::SetCharacteristicQuantificationCollection(const CharacteristicQuantificationPtrVector& newVal)
{
	this->FreeAllCharacteristicQuantifications();

	_characteristicQuantificationCollection.reserve(newVal.size());
	for(CharacteristicQuantificationPtrVector::size_type i=0; i < newVal.size(); i++)
		if (newVal[i] != NULL)
			_characteristicQuantificationCollection.push_back(newVal[i]->Clone());
}

void AnatomicEntityCharacteristic::FreeAllCharacteristicQuantifications()
{
	CharacteristicQuantificationPtrVector::iterator iter;
	for(iter = _characteristicQuantificationCollection.begin(); iter < _characteristicQuantificationCollection.end(); iter++)
	{
		delete *iter;
		*iter = NULL;
	}
	_characteristicQuantificationCollection.clear();
}
