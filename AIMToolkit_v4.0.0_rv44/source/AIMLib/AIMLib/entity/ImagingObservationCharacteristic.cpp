/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
