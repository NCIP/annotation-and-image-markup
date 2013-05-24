/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "CharacteristicQuantification.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;

CharacteristicQuantification::CharacteristicQuantification(const string& typeName){
	_quantificationTypeName = typeName;
}

CharacteristicQuantification::CharacteristicQuantification(const CharacteristicQuantification& characteristicQuantification){
	*this = characteristicQuantification;
}

CharacteristicQuantification& CharacteristicQuantification::operator=(const CharacteristicQuantification& characteristicQuantification){
	if (this != &characteristicQuantification)
	{
		_label								= characteristicQuantification._label;
		_quantificationTypeName				= characteristicQuantification._quantificationTypeName;
		_characteristicQuantificationIndex	= characteristicQuantification._characteristicQuantificationIndex;
		_valueLabel							= characteristicQuantification._valueLabel;
		_valueDescription					= characteristicQuantification._valueDescription;
		_comment							= characteristicQuantification._comment;

		SetAnnotatorConfidence(characteristicQuantification.GetAnnotatorConfidence());
	}
	return *this;
}

CharacteristicQuantification::~CharacteristicQuantification(void){
}

const string& CharacteristicQuantification::GetLabel() const{
	return _label;
}

double* CharacteristicQuantification::GetAnnotatorConfidence() const{
	return _annotatorConfidence.get();
}

int CharacteristicQuantification::GetCharacteristicQuantificationIndex() const{
	return _characteristicQuantificationIndex;
}

const string& CharacteristicQuantification::GetValueLabel() const{
	return _valueLabel;
}

const string& CharacteristicQuantification::GetValueDescription() const{
	return _valueDescription;
}

const string& CharacteristicQuantification::GetComment() const{
	return _comment;
}

const string& CharacteristicQuantification::GetQuantificationTypeName() const{
	return _quantificationTypeName;
}

void CharacteristicQuantification::SetLabel(const string& newVal){
	_label = newVal;
}

void CharacteristicQuantification::SetAnnotatorConfidence(double* pConfidence){
	_annotatorConfidence.reset(pConfidence ? new double(*pConfidence) : NULL);
}

void CharacteristicQuantification::SetCharacteristicQuantificationIndex(int newVal){
	_characteristicQuantificationIndex = newVal;
}

void CharacteristicQuantification::SetValueLabel(const string& newVal){
	_valueLabel = newVal;
}

void CharacteristicQuantification::SetValueDescription(const string& newVal){
	_valueDescription = newVal;
}

void CharacteristicQuantification::SetComment(const string& newVal){
	_comment = newVal;
}
