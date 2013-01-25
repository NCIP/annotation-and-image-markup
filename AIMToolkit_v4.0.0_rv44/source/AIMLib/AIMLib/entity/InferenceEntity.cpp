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
#include "InferenceEntity.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;
using iso_21090::CDVector;

InferenceEntity::InferenceEntity(void) : _questionIndex(-1){
}

InferenceEntity::InferenceEntity(const InferenceEntity& inferenceEntity) : Entity(inferenceEntity){
	*this = inferenceEntity;
}

InferenceEntity& InferenceEntity::operator=(const InferenceEntity& inferenceEntity){
	if (this != &inferenceEntity)
	{
		Entity::operator=(inferenceEntity);
		SetTypeCode(inferenceEntity._typeCode);
		SetQuestionTypeCode(inferenceEntity._questionTypeCode);
		_description		= inferenceEntity._description;
		_label				= inferenceEntity._label;
		_comment			= inferenceEntity._comment;
		_imageEvidence		= inferenceEntity._imageEvidence;
		_questionIndex		= inferenceEntity._questionIndex;
		SetIsPresent(inferenceEntity.GetIsPresent());
		SetAnnotatorConfidence(inferenceEntity.GetAnnotatorConfidence());
	}
	return *this;
}

InferenceEntity::~InferenceEntity(void){
	_isPresent.reset();
	_annotatorConfidence.reset();
}

const CDVector& InferenceEntity::GetTypeCode() const{
	return _typeCode;
}

const CDVector& InferenceEntity::GetQuestionTypeCode() const{
	return _questionTypeCode;
}

double* InferenceEntity::GetAnnotatorConfidence() const{
	return _annotatorConfidence.get();
}

const string& InferenceEntity::GetDescription() const{
	return _description;
}

const string& InferenceEntity::GetLabel() const{
	return _label;
}

const string& InferenceEntity::GetComment() const{
	return _comment;
}

bool InferenceEntity::GetIsImageEvidence() const{
	return _imageEvidence;
}

bool* InferenceEntity::GetIsPresent() const{
	return _isPresent.get();
}

int InferenceEntity::GetQuestionIndex() const{
	return _questionIndex;
}

void InferenceEntity::SetTypeCode(const CDVector& typeCode){
	_typeCode.assign(typeCode.begin(), typeCode.end());
}

void InferenceEntity::SetQuestionTypeCode(const CDVector& questionTypeCode){
	_questionTypeCode.assign(questionTypeCode.begin(), questionTypeCode.end());
}

void InferenceEntity::SetAnnotatorConfidence(double* annotatorConfidence){
	_annotatorConfidence.reset(annotatorConfidence ? new double(*annotatorConfidence) : NULL);
}

void InferenceEntity::SetDescription(const string& description){
	_description = description;
}

void InferenceEntity::SetLabel(const string& label){
	_label = label;
}

void InferenceEntity::SetComment(const string& newVal){
	_comment = newVal;
}

void InferenceEntity::SetImageEvidence(bool imageEvidence){
	_imageEvidence = imageEvidence;
}

void InferenceEntity::SetIsPresent(bool* isPresent){
	_isPresent.reset(isPresent ? new bool(*isPresent) : NULL);
}

void InferenceEntity::SetQuestionIndex(int questionIndex){
	_questionIndex = questionIndex;
}
