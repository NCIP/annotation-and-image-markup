/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
