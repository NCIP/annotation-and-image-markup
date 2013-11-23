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
#include "ImagingPhysicalEntityCharacteristic.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;
using namespace iso_21090;

ImagingPhysicalEntityCharacteristic::ImagingPhysicalEntityCharacteristic(void) : _questionIndex(-1){
}

ImagingPhysicalEntityCharacteristic::ImagingPhysicalEntityCharacteristic(const ImagingPhysicalEntityCharacteristic& imagingPhysEntCharacteristic){
	*this = imagingPhysEntCharacteristic;
}


ImagingPhysicalEntityCharacteristic& ImagingPhysicalEntityCharacteristic::operator= (const ImagingPhysicalEntityCharacteristic& imagingPhysEntCharacteristic){
	if (this != &imagingPhysEntCharacteristic)
	{
		SetTypeCode(imagingPhysEntCharacteristic._typeCode);
		SetQuestionTypeCode(imagingPhysEntCharacteristic._questionTypeCode);
		_label				= imagingPhysEntCharacteristic._label;
		_comment			= imagingPhysEntCharacteristic._comment;
		_questionIndex		= imagingPhysEntCharacteristic._questionIndex;
		SetAnnotatorConfidence(imagingPhysEntCharacteristic.GetAnnotatorConfidence());
		SetCharacteristicQuantificationCollection(imagingPhysEntCharacteristic.GetCharacteristicQuantificationCollection());
	}

	return *this;
}

ImagingPhysicalEntityCharacteristic::~ImagingPhysicalEntityCharacteristic(void){
	this->FreeAllCharacteristicQuantifications();
}

ImagingPhysicalEntityCharacteristic* ImagingPhysicalEntityCharacteristic::Clone() const{
	return new ImagingPhysicalEntityCharacteristic(*this);
}

const CDVector& ImagingPhysicalEntityCharacteristic::GetTypeCode() const{
	return _typeCode;
}

const CDVector& ImagingPhysicalEntityCharacteristic::GetQuestionTypeCode() const{
	return _questionTypeCode;
}

double* ImagingPhysicalEntityCharacteristic::GetAnnotatorConfidence() const{
	return _annotatorConfidence.get();
}

const string& ImagingPhysicalEntityCharacteristic::GetLabel() const{
	return _label;
}

const string& ImagingPhysicalEntityCharacteristic::GetComment() const{
	return _comment;
}

int ImagingPhysicalEntityCharacteristic::GetQuestionIndex() const{
	return _questionIndex;
}

const CharacteristicQuantificationPtrVector& ImagingPhysicalEntityCharacteristic::GetCharacteristicQuantificationCollection() const{
	return _characteristicQuantificationCollection;
}

void ImagingPhysicalEntityCharacteristic::SetTypeCode(const CDVector& newVal){
	_typeCode.assign(newVal.begin(), newVal.end());
}

void ImagingPhysicalEntityCharacteristic::SetQuestionTypeCode(const CDVector& newVal){
	_questionTypeCode.assign(newVal.begin(), newVal.end());
}

void ImagingPhysicalEntityCharacteristic::SetAnnotatorConfidence(double* pConfidence){
	_annotatorConfidence.reset(pConfidence ? new double(*pConfidence) : NULL);
}

void ImagingPhysicalEntityCharacteristic::SetLabel(const string& newVal){
	_label = newVal;
}

void ImagingPhysicalEntityCharacteristic::SetComment(const string& newVal){
	_comment = newVal;
}

void ImagingPhysicalEntityCharacteristic::SetQuestionIndex(int newVal){
	_questionIndex = newVal;
}

void ImagingPhysicalEntityCharacteristic::SetCharacteristicQuantificationCollection(const CharacteristicQuantificationPtrVector& newVal){
	this->FreeAllCharacteristicQuantifications();

//	_characteristicQuantificationCollection.reserve(newVal.size());
	for(CharacteristicQuantificationPtrVector::size_type i=0; i < newVal.size(); i++)
		if (newVal[i] != NULL)
			_characteristicQuantificationCollection.push_back(newVal[i]->Clone());
}

void ImagingPhysicalEntityCharacteristic::FreeAllCharacteristicQuantifications(){
	CharacteristicQuantificationPtrVector::iterator iter;
	for(iter = _characteristicQuantificationCollection.begin(); iter < _characteristicQuantificationCollection.end(); iter++)
	{
		delete *iter;
		*iter = NULL;
	}
	_characteristicQuantificationCollection.clear();
}
