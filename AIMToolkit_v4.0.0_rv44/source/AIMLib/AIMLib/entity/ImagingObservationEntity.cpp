/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
