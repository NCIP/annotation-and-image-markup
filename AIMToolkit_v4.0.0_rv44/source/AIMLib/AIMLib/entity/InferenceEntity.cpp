/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
