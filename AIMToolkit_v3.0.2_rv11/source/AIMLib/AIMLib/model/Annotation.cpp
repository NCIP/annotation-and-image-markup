/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "../AimEnum.h"

#include "AimBase.h"
#include "DateTime.h"
#include "User.h"
#include "Equipment.h"
#include "AimStatus.h"
#include "ReferencedGeometricShape.h"
#include "CharacteristicQuantification.h"
#include "AnatomicEntityCharacteristic.h"
#include "AnatomicEntity.h"
#include "ImagingObservationCharacteristic.h"
#include "ImagingObservation.h"
#include "ReferencedCalculation.h"
#include "Dimension.h"
#include "Coordinate.h"
#include "CalculationData.h"
#include "CalculationResult.h"
#include "Calculation.h"
#include "Inference.h"
#include "Annotation.h"

#include "../operations/BaseModel.h"

using std::string;
using namespace aim_lib;

Annotation::Annotation(const string& typeName) : AimBase(typeName){
	//TODO - uid
	_aimVersion = BaseModel::AIM_MODEL_VERSION;
	_dateTime = time(NULL);
}

Annotation::Annotation(const Annotation& annotation) : AimBase(annotation){
	_cagridId							= annotation._cagridId;
	_uniqueIdentifier					= annotation._uniqueIdentifier;
	_codeMeaning						= annotation._codeMeaning;
	_codeValue							= annotation._codeValue;
	_codingSchemeDesignator				= annotation._codingSchemeDesignator;
	_codingSchemeVersion				= annotation._codingSchemeVersion;
	_aimVersion							= annotation._aimVersion;
	_dateTime							= annotation._dateTime;
	_name								= annotation._name;
	_comment							= annotation._comment;
	_precedentReferencedAnnotationUID	= annotation._precedentReferencedAnnotationUID;

	SetUser(annotation.GetUser());
	SetEquipment(annotation.GetEquipment());
	SetAimStatus(annotation.GetAimStatus());
	SetAnatomicEntityCollection(annotation.GetAnatomicEntityCollection());
	SetImagingObservationCollection(annotation.GetImagingObservationCollection());
	SetCalculationCollection(annotation.GetCalculationCollection());
	SetInferenceCollection(annotation.GetInferenceCollection());
}

Annotation::~Annotation(){
}

const string& Annotation::GetUniqueIdentifier() const{

	return _uniqueIdentifier;
}

const string& Annotation::GetAimVersion() const{

	return _aimVersion;
}

const string& Annotation::GetCodeMeaning() const{

	return _codeMeaning;
}

const string& Annotation::GetCodeValue() const{

	return _codeValue;
}

const string& Annotation::GetCodingSchemeDesignator() const{

	return _codingSchemeDesignator;
}

const string& Annotation::GetCodingSchemeVersion() const{

	return _codingSchemeVersion;
}

/**
 * Human readble colloquial name of the annotation not guaranteed to be unique
 */
const string& Annotation::GetName() const{

	return _name;
}

const DateTime& Annotation::GetDateTime() const{

	return _dateTime;
}

const string& Annotation::GetComment() const{

	return _comment;
}

const string& Annotation::GetPrecedentReferencedAnnotationUID() const{

	return _precedentReferencedAnnotationUID;
}

const User* Annotation::GetUser() const{

	return  _user.get();
}

const Equipment* Annotation::GetEquipment() const{

	return  _equipment.get();
}

const AimStatus* Annotation::GetAimStatus() const{

	return  _aimStatus.get();
}

const AnatomicEntityVector& Annotation::GetAnatomicEntityCollection() const{

	return  _anatomicEntityCollection;
}

const ImagingObservationVector& Annotation::GetImagingObservationCollection() const{

	return  _imagingObservationCollection;
}

const CalculationVector& Annotation::GetCalculationCollection() const{

	return  _calculationCollection;
}

const InferenceVector& Annotation::GetInferenceCollection() const{

	return  _inferenceCollection;
}

void Annotation::SetUniqueidentifier(const string& newVal){

	_uniqueIdentifier = newVal;
}

void Annotation::SetAimVersion(const string& newVal){

	_aimVersion = newVal;
}

void Annotation::SetCodeMeaning(const string& newVal){

	_codeMeaning = newVal;
}

void Annotation::SetCodeValue(const string& newVal){

	_codeValue = newVal;
}

void Annotation::SetCodingSchemeDesignator(const string& newVal){

	_codingSchemeDesignator = newVal;
}

void Annotation::SetCodingSchemeVersion(const string& newVal){

	_codingSchemeVersion = newVal;
}

/**
 * Human readble colloquial name of the annotation not guaranteed to be unique
 */
void Annotation::SetName(const string& newVal){

	_name = newVal;
}

void Annotation::SetDateTime(const DateTime& newVal){

	_dateTime = newVal;
}

void Annotation::SetComment(const string& newVal){

	_comment = newVal;
}

void Annotation::SetPrecedentReferencedAnnotationUID(const string& newVal){

	_precedentReferencedAnnotationUID = newVal;
}

void Annotation::SetUser(const User* user){
	if (user == NULL)
		_user.reset();
	else
		_user.reset(user->Clone());
}

void Annotation::SetEquipment(const Equipment* equipment){
	if (equipment == NULL)
		_equipment.reset();
	else
		_equipment.reset(equipment->Clone());
}

void Annotation::SetAimStatus(const AimStatus* aimStatus){
	if (aimStatus == NULL)
		_aimStatus.reset();
	else
		_aimStatus.reset(aimStatus->Clone());
}

void Annotation::SetAnatomicEntityCollection(const AnatomicEntityVector& anatomicEntity){

	_anatomicEntityCollection.assign(anatomicEntity.begin(), anatomicEntity.end());
}

void Annotation::SetImagingObservationCollection(const ImagingObservationVector& imagingObservation){

	_imagingObservationCollection.assign(imagingObservation.begin(), imagingObservation.end());
}

void Annotation::SetCalculationCollection(const CalculationVector& calculation){

	_calculationCollection.assign(calculation.begin(), calculation.end());
}

void Annotation::SetInferenceCollection(const InferenceVector& inferences){

	_inferenceCollection.assign(inferences.begin(), inferences.end());
}
