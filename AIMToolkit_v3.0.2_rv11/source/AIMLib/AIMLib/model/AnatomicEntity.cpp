/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "../stdafx.h"

#include "AimBase.h"
#include "CharacteristicQuantification.h"
#include "AnatomicEntityCharacteristic.h"
#include "AnatomicEntity.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;

AnatomicEntity::AnatomicEntity() : _isPresent(true){
}

AnatomicEntity::AnatomicEntity(const AnatomicEntity& anatomicEntity){
	*this = anatomicEntity;
}

AnatomicEntity& AnatomicEntity::operator= (const AnatomicEntity& anatomicEntity){
	_cagridId				= anatomicEntity._cagridId;
	_codeMeaning			= anatomicEntity._codeMeaning;
	_codeValue				= anatomicEntity._codeValue;
	_codingSchemeDesignator	= anatomicEntity._codingSchemeDesignator;
	_codingSchemeVersion	= anatomicEntity._codingSchemeVersion;
	_label					= anatomicEntity._label;
	_isPresent				= anatomicEntity._isPresent;
	SetAnnotatorConfidence(anatomicEntity.GetAnnotatorConfidence());
	SetAnatomicEntityCharacteristicCollection(anatomicEntity.GetAnatomicEntityCharacteristicCollection());

	return *this;
}

AnatomicEntity::~AnatomicEntity(){
}

AnatomicEntity* AnatomicEntity::Clone() const{

	return new AnatomicEntity(*this);
}

const string& AnatomicEntity::GetCodeMeaning() const{

	return _codeMeaning;
}

const string& AnatomicEntity::GetCodeValue() const{

	return _codeValue;
}

const string& AnatomicEntity::GetCodingSchemeDesignator() const{

	return _codingSchemeDesignator;
}

const string& AnatomicEntity::GetCodingSchemeVersion() const{

	return _codingSchemeVersion;
}

double* AnatomicEntity::GetAnnotatorConfidence() const{
	return _annotatorConfidence.get();
}

const string& AnatomicEntity::GetLabel() const{
	return _label;
}

bool AnatomicEntity::GetIsPresent() const{
	return _isPresent;
}

const AnatomicEntityCharacteristicVector& AnatomicEntity::GetAnatomicEntityCharacteristicCollection() const{
	return _anatomicEntityCharacteristicCollection;
}

void AnatomicEntity::SetCodeMeaning(const string& newVal){

	_codeMeaning = newVal;
}

void AnatomicEntity::SetCodeValue(const string& newVal){

	_codeValue = newVal;
}

void AnatomicEntity::SetCodingSchemeDesignator(const string& newVal){

	_codingSchemeDesignator = newVal;
}

void AnatomicEntity::SetCodingSchemeVersion(const string& newVal){

	_codingSchemeVersion = newVal;
}

void AnatomicEntity::SetAnnotatorConfidence(double* pConfidence){

	if (pConfidence == NULL)
		_annotatorConfidence.reset();
	else
		_annotatorConfidence.reset(new double(*pConfidence));
}

void AnatomicEntity::SetLabel(const string& newVal){
	_label = newVal;
}

void AnatomicEntity::SetIsPresent(bool newVal){
	_isPresent = newVal;
}

void AnatomicEntity::SetAnatomicEntityCharacteristicCollection(const AnatomicEntityCharacteristicVector &newVal){

	_anatomicEntityCharacteristicCollection.assign(newVal.begin(), newVal.end());
}
