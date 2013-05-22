/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
