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
