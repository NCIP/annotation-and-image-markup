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

#include "Entity.h"
#include "CharacteristicQuantification.h"
#include "ImagingObservationCharacteristic.h"
#include "ImagingObservationEntity.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;
using iso_21090::CDVector;

ImagingObservationEntity::ImagingObservationEntity() : _questionIndex(-1){

}

ImagingObservationEntity::ImagingObservationEntity(const ImagingObservationEntity& imgObservationEntity) : Entity(imgObservationEntity){
	*this = imgObservationEntity;
}

ImagingObservationEntity& ImagingObservationEntity::operator= (const ImagingObservationEntity& imgObservationEntity){
	SetTypeCode(imgObservationEntity._typeCode);
	SetQuestionTypeCode(imgObservationEntity._questionTypeCode);
	_label				= imgObservationEntity._label;
	_comment			= imgObservationEntity._comment;
	_questionIndex		= imgObservationEntity._questionIndex;

	SetIsPresent(imgObservationEntity.GetIsPresent());
	SetAnnotatorConfidence(imgObservationEntity.GetAnnotatorConfidence());
	SetImagingObservationCharacteristicCollection(imgObservationEntity.GetImagingObservationCharacteristicCollection());

	return *this;
}

ImagingObservationEntity::~ImagingObservationEntity(){
}

ImagingObservationEntity* ImagingObservationEntity::Clone() const{
	return new ImagingObservationEntity(*this);
}

const CDVector& ImagingObservationEntity::GetTypeCode() const{
	return _typeCode;
}

const CDVector& ImagingObservationEntity::GetQuestionTypeCode() const{
	return _questionTypeCode;
}

double* ImagingObservationEntity::GetAnnotatorConfidence() const{
	return _annotatorConfidence.get();
}

const string& ImagingObservationEntity::GetLabel() const{
	return _label;
}

const string& ImagingObservationEntity::GetComment() const{
	return _comment;
}

bool* ImagingObservationEntity::GetIsPresent() const{
	return _isPresent.get();
}

int ImagingObservationEntity::GetQuestionIndex() const{
	return _questionIndex;
}

const ImagingObservationCharacteristicVector& ImagingObservationEntity::GetImagingObservationCharacteristicCollection() const{
	return _imagingObservationCharachteristicCollection;
}

void ImagingObservationEntity::SetTypeCode(const CDVector& newVal){
	_typeCode.assign(newVal.begin(), newVal.end());
}

void ImagingObservationEntity::SetQuestionTypeCode(const CDVector& newVal){
	_questionTypeCode.assign(newVal.begin(), newVal.end());
}

void ImagingObservationEntity::SetAnnotatorConfidence(double* pConfidence){
	_annotatorConfidence.reset(pConfidence ? new double(*pConfidence) : NULL);
}

void ImagingObservationEntity::SetLabel(const string& newVal){
	_label = newVal;
}

void ImagingObservationEntity::SetComment(const string& newVal){
	_comment = newVal;
}

void ImagingObservationEntity::SetIsPresent(bool* newVal){
	_isPresent.reset(newVal ? new bool(*newVal) : NULL);
}

void ImagingObservationEntity::SetQuestionIndex(int newVal){
	_questionIndex = newVal;
}

void ImagingObservationEntity::SetImagingObservationCharacteristicCollection(const aim_lib::ImagingObservationCharacteristicVector& newVal){
	_imagingObservationCharachteristicCollection.assign(newVal.begin(), newVal.end());
}
