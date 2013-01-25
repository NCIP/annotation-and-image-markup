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

#include "../AimEnum.h"

#include "Entity.h"
#include "Parameter.h"
#include "Algorithm.h"
#include "Dimension.h"
#include "CalculationResult.h"
#include "CalculationEntity.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;
using iso_21090::CDVector;

CalculationEntity::CalculationEntity() : _questionIndex(-1){
}

CalculationEntity::CalculationEntity(const CalculationEntity& calculationEntity) : Entity(calculationEntity){
	*this = calculationEntity;
}

CalculationEntity& CalculationEntity::operator=(const CalculationEntity& calculationEntity){

	if (this != &calculationEntity)
	{
		Entity::operator=(calculationEntity);
		_description	= calculationEntity._description;
		_mathML			= calculationEntity._mathML;
		_questionIndex	= calculationEntity._questionIndex;
		SetTypeCode(calculationEntity.GetTypeCode());
		SetQuestionTypeCode(calculationEntity.GetQuestionTypeCode());
		SetAlgorithm(calculationEntity.GetAlgorithm());
		SetCalculationResultCollection(calculationEntity.GetCalculationResultCollection());
	}

	return *this;
}

CalculationEntity::~CalculationEntity(){
	this->FreePtrVector<CalculationResult>(_calculationResultCollection);
}

const CDVector& CalculationEntity::GetTypeCode() const{
	return _typeCode;
}

const CDVector& CalculationEntity::GetQuestionTypeCode() const{
	return _questionTypeCode;
}

const string& CalculationEntity::GetDescription() const {
	return _description;
}

const string& CalculationEntity::GetMathML() const{
	return _mathML;
}

int CalculationEntity::GetQuestionIndex() const{
	return _questionIndex;
}

const Algorithm* CalculationEntity::GetAlgorithm() const{
	return _algorithm.get();
}

const CalculationResultPtrVector& CalculationEntity::GetCalculationResultCollection() const{
	return _calculationResultCollection;
}

void CalculationEntity::SetTypeCode(const CDVector& newVal){
	_typeCode.assign(newVal.begin(), newVal.end());
}

void CalculationEntity::SetQuestionTypeCode(const CDVector& newVal){
	_questionTypeCode.assign(newVal.begin(), newVal.end());
}

void CalculationEntity::SetDescription(const string& newVal){
	_description = newVal;
}

void CalculationEntity::SetMathML(const string& newVal){
	_mathML = newVal;
}

void CalculationEntity::SetQuestionIndex(int newVal){
	_questionIndex = newVal;
}

void CalculationEntity::SetAlgorithm(const Algorithm* newVal){
	_algorithm.reset(newVal ? new Algorithm(*newVal) : NULL);
}

void CalculationEntity::SetCalculationResultCollection(const CalculationResultPtrVector& calculationResults){
	this->FreePtrVector<CalculationResult>(_calculationResultCollection);
	this->ClonePtrVector<CalculationResult>(calculationResults, _calculationResultCollection);
}
