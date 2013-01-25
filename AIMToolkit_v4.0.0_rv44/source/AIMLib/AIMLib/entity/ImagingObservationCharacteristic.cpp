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
#include "ImagingObservationCharacteristic.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;
using iso_21090::CDVector;

ImagingObservationCharacteristic::ImagingObservationCharacteristic() : _questionIndex(-1){
}

ImagingObservationCharacteristic::ImagingObservationCharacteristic(const ImagingObservationCharacteristic& imgObsCharacteristics){
	*this = imgObsCharacteristics;
}

ImagingObservationCharacteristic& ImagingObservationCharacteristic::operator= (const ImagingObservationCharacteristic& imgObsCharacteristics){
	if (this != &imgObsCharacteristics)
	{
		SetTypeCode(imgObsCharacteristics._typeCode);
		SetQuestionTypeCode(imgObsCharacteristics._questionTypeCode);
		_label				= imgObsCharacteristics._label;
		_comment			= imgObsCharacteristics._comment;
		_questionIndex		= imgObsCharacteristics._questionIndex;

		SetAnnotatorConfidence(imgObsCharacteristics.GetAnnotatorConfidence());
		SetCharacteristicQuantificationCollection(imgObsCharacteristics.GetCharacteristicQuantificationCollection());
	}

	return *this;
}

ImagingObservationCharacteristic::~ImagingObservationCharacteristic(){
	this->FreeAllCharacteristicQuantifications();
}

ImagingObservationCharacteristic* ImagingObservationCharacteristic::Clone() const{
	return new ImagingObservationCharacteristic(*this);
}

const CDVector& ImagingObservationCharacteristic::GetTypeCode() const{
	return _typeCode;
}

const CDVector& ImagingObservationCharacteristic::GetQuestionTypeCode() const{
	return _questionTypeCode;
}

double* ImagingObservationCharacteristic::GetAnnotatorConfidence() const{
	return _annotatorConfidence.get();
}

const string& ImagingObservationCharacteristic::GetLabel() const{
	return _label;
}

const string& ImagingObservationCharacteristic::GetComment() const{

	return _comment;
}

int ImagingObservationCharacteristic::GetQuestionIndex() const{
	return _questionIndex;
}

const CharacteristicQuantificationPtrVector& ImagingObservationCharacteristic::GetCharacteristicQuantificationCollection() const{
	return _characteristicQuantificationCollection;
}


void ImagingObservationCharacteristic::SetTypeCode(const CDVector& newVal){
	_typeCode.assign(newVal.begin(), newVal.end());
}

void ImagingObservationCharacteristic::SetQuestionTypeCode(const CDVector& newVal){
	_questionTypeCode.assign(newVal.begin(), newVal.end());
}

void ImagingObservationCharacteristic::SetAnnotatorConfidence(double* pConfidence){
	_annotatorConfidence.reset(pConfidence ? new double(*pConfidence) : NULL);
}

void ImagingObservationCharacteristic::SetLabel(const string& newVal){
	_label = newVal;
}

void ImagingObservationCharacteristic::SetComment(const string& newVal){
	_comment = newVal;
}

void ImagingObservationCharacteristic::SetQuestionIndex(int newVal){
	_questionIndex = newVal;
}

void ImagingObservationCharacteristic::SetCharacteristicQuantificationCollection(const CharacteristicQuantificationPtrVector& newVal)
{
	this->FreeAllCharacteristicQuantifications();

//	_characteristicQuantificationCollection.reserve(newVal.size());
	for(CharacteristicQuantificationPtrVector::size_type i=0; i < newVal.size(); i++)
		if (newVal[i] != NULL)
			_characteristicQuantificationCollection.push_back(newVal[i]->Clone());
}

void ImagingObservationCharacteristic::FreeAllCharacteristicQuantifications()
{
	CharacteristicQuantificationPtrVector::iterator iter;
	for(iter = _characteristicQuantificationCollection.begin(); iter < _characteristicQuantificationCollection.end(); iter++)
	{
		delete *iter;
		*iter = NULL;
	}
	_characteristicQuantificationCollection.clear();
}
