/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "AimBase.h"
#include "CharacteristicQuantification.h"
#include "ImagingObservationCharacteristic.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;

ImagingObservationCharacteristic::ImagingObservationCharacteristic(){
}

ImagingObservationCharacteristic::ImagingObservationCharacteristic(const ImagingObservationCharacteristic& imgObsCharacteristics){
	*this = imgObsCharacteristics;
}

ImagingObservationCharacteristic& ImagingObservationCharacteristic::operator= (const ImagingObservationCharacteristic& imgObsCharacteristics){
	if (this != &imgObsCharacteristics)
	{
		_cagridId				= imgObsCharacteristics._cagridId;
		_codeValue				= imgObsCharacteristics._codeValue;
		_codeMeaning			= imgObsCharacteristics._codeMeaning;
		_codingSchemeDesignator	= imgObsCharacteristics._codingSchemeDesignator;
		_codingSchemeVersion	= imgObsCharacteristics._codingSchemeVersion;
		_comment				= imgObsCharacteristics._comment;
		_label					= imgObsCharacteristics._label;

		SetAnnotatorConfidence(imgObsCharacteristics.GetAnnotatorConfidence());
		SetCharacteristicQuantificationCollection(imgObsCharacteristics.GetCharacteristicQuantificationCollection());
	}

	return *this;
}

ImagingObservationCharacteristic::~ImagingObservationCharacteristic(){

	// Characteristic Quantifications Collection
	this->FreeAllCharacteristicQuantifications();
}

ImagingObservationCharacteristic* ImagingObservationCharacteristic::Clone() const{

	return new ImagingObservationCharacteristic(*this);
}

const string& ImagingObservationCharacteristic::GetCodeMeaning() const{

	return _codeMeaning;
}

const string& ImagingObservationCharacteristic::GetCodeValue() const{

	return _codeValue;
}

const string& ImagingObservationCharacteristic::GetCodingSchemeDesignator() const{

	return _codingSchemeDesignator;
}

const string& ImagingObservationCharacteristic::GetCodingSchemeVersion() const{

	return _codingSchemeVersion;
}

const string& ImagingObservationCharacteristic::GetComment() const{

	return _comment;
}

double* ImagingObservationCharacteristic::GetAnnotatorConfidence() const{
	return _annotatorConfidence.get();
}

const string& ImagingObservationCharacteristic::GetLabel() const{
	return _label;
}

const CharacteristicQuantificationPtrVector& ImagingObservationCharacteristic::GetCharacteristicQuantificationCollection() const
{
	return _characteristicQuantificationCollection;
}

void ImagingObservationCharacteristic::SetCodeMeaning(const string& newVal){

	_codeMeaning = newVal;
}

void ImagingObservationCharacteristic::SetCodeValue(const string& newVal){

	_codeValue = newVal;
}

void ImagingObservationCharacteristic::SetCodingSchemeDesignator(const string& newVal){

	_codingSchemeDesignator = newVal;
}

void ImagingObservationCharacteristic::SetCodingSchemeVersion(const string& newVal){

	_codingSchemeVersion = newVal;
}

void ImagingObservationCharacteristic::SetComment(const string& newVal){

	_comment = newVal;
}

void ImagingObservationCharacteristic::SetAnnotatorConfidence(double *pNewVal){
	if (pNewVal == NULL)
		_annotatorConfidence.reset();
	else
		_annotatorConfidence.reset(new double(*pNewVal));
}

void ImagingObservationCharacteristic::SetLabel(const string& newVal){
	_label = newVal;
}

void ImagingObservationCharacteristic::SetCharacteristicQuantificationCollection(const CharacteristicQuantificationPtrVector& newVal)
{
	this->FreeAllCharacteristicQuantifications();

	_characteristicQuantificationCollection.reserve(newVal.size());
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
