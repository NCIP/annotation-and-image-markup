/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
