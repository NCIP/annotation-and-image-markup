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
#include "ImagingPhysicalEntityCharacteristic.h"
#include "ImagingPhysicalEntity.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;
using iso_21090::CDVector;

ImagingPhysicalEntity::ImagingPhysicalEntity() : _questionIndex(-1){
}

ImagingPhysicalEntity::ImagingPhysicalEntity(const ImagingPhysicalEntity& imagingPhysicalEntity) : Entity(imagingPhysicalEntity){
	*this = imagingPhysicalEntity;
}

ImagingPhysicalEntity& ImagingPhysicalEntity::operator= (const ImagingPhysicalEntity& imagingPhysicalEntity){
	SetTypeCode(imagingPhysicalEntity._typeCode);
	SetQuestionTypeCode(imagingPhysicalEntity._questionTypeCode);
	_label				= imagingPhysicalEntity._label;
	_comment			= imagingPhysicalEntity._comment;
	_questionIndex		= imagingPhysicalEntity._questionIndex;
	SetAnnotatorConfidence(imagingPhysicalEntity.GetAnnotatorConfidence());
	SetIsPresent(imagingPhysicalEntity.GetIsPresent());
	SetImagingObservationCharacteristicCollection(imagingPhysicalEntity.GetImagingObservationCharacteristicCollection());
	SetImagingPhysicalEntityCharacteristicCollection(imagingPhysicalEntity.GetImagingPhysicalEntityCharacteristicCollection());

	return *this;
}

ImagingPhysicalEntity::~ImagingPhysicalEntity(){
}

ImagingPhysicalEntity* ImagingPhysicalEntity::Clone() const{
	return new ImagingPhysicalEntity(*this);
}

const CDVector& ImagingPhysicalEntity::GetTypeCode() const{
	return _typeCode;
}

const CDVector& ImagingPhysicalEntity::GetQuestionTypeCode() const{
	return _questionTypeCode;
}

double* ImagingPhysicalEntity::GetAnnotatorConfidence() const{
	return _annotatorConfidence.get();
}

const string& ImagingPhysicalEntity::GetLabel() const{
	return _label;
}

const string& ImagingPhysicalEntity::GetComment() const{
	return _comment;
}

bool* ImagingPhysicalEntity::GetIsPresent() const{
	return _isPresent.get();
}

int ImagingPhysicalEntity::GetQuestionIndex() const{
	return _questionIndex;
}

const ImagingObservationCharacteristicVector& ImagingPhysicalEntity::GetImagingObservationCharacteristicCollection() const{
	return _imagingObservationCharachteristicCollection;
}

const ImagingPhysicalEntityCharacteristicVector& ImagingPhysicalEntity::GetImagingPhysicalEntityCharacteristicCollection() const{
	return _imagingPhysicalEntityCharacteristicCollection;
}

void ImagingPhysicalEntity::SetTypeCode(const CDVector& newVal){
	_typeCode.assign(newVal.begin(), newVal.end());
}

void ImagingPhysicalEntity::SetQuestionTypeCode(const CDVector& newVal){
	_questionTypeCode.assign(newVal.begin(), newVal.end());
}

void ImagingPhysicalEntity::SetAnnotatorConfidence(double* pConfidence){
	_annotatorConfidence.reset(pConfidence ? new double(*pConfidence) : NULL);
}

void ImagingPhysicalEntity::SetLabel(const string& newVal){
	_label = newVal;
}

void ImagingPhysicalEntity::SetComment(const string& newVal){
	_comment = newVal;
}

void ImagingPhysicalEntity::SetIsPresent(bool* newVal){
	_isPresent.reset(newVal ? new bool(*newVal) : NULL);
}

void ImagingPhysicalEntity::SetQuestionIndex(int newVal){
	_questionIndex = newVal;
}

void ImagingPhysicalEntity::SetImagingObservationCharacteristicCollection(const aim_lib::ImagingObservationCharacteristicVector& newVal){
	_imagingObservationCharachteristicCollection.assign(newVal.begin(), newVal.end());
}

void ImagingPhysicalEntity::SetImagingPhysicalEntityCharacteristicCollection(const ImagingPhysicalEntityCharacteristicVector &newVal){
	_imagingPhysicalEntityCharacteristicCollection.assign(newVal.begin(), newVal.end());
}
