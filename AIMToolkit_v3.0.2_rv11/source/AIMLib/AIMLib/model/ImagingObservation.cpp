/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "AimBase.h"
#include "ReferencedGeometricShape.h"
#include "CharacteristicQuantification.h"
#include "ImagingObservationCharacteristic.h"
#include "ImagingObservation.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;

ImagingObservation::ImagingObservation() : _isPresent(true){

}

ImagingObservation::ImagingObservation(const ImagingObservation& imgObservation){
	*this = imgObservation;
}

ImagingObservation& ImagingObservation::operator= (const ImagingObservation& imgObservation){
	_cagridId				= imgObservation._cagridId;
	_codeValue				= imgObservation._codeValue;
	_codeMeaning			= imgObservation._codeMeaning;
	_codingSchemeDesignator	= imgObservation._codingSchemeDesignator;
	_codingSchemeVersion	= imgObservation._codingSchemeVersion;
	_comment				= imgObservation._comment;
	_label					= imgObservation._label;
	_isPresent				= imgObservation._isPresent;

	SetAnnotatorConfidence(imgObservation.GetAnnotatorConfidence());
	SetReferencedGeometricShape(imgObservation.GetReferencedGeometricShape());
	SetImagingObservationCharacteristicCollection(imgObservation.GetImagingObservationCharacteristicCollection());

	return *this;
}

ImagingObservation::~ImagingObservation(){

}

ImagingObservation* ImagingObservation::Clone() const{

	return new ImagingObservation(*this);
}

const string& ImagingObservation::GetCodeMeaning() const{

	return _codeMeaning;
}

const string& ImagingObservation::GetCodeValue() const{

	return _codeValue;
}

const string& ImagingObservation::GetCodingSchemeDesignator() const{

	return _codingSchemeDesignator;
}

const string& ImagingObservation::GetCodingSchemeVersion() const{

	return _codingSchemeVersion;
}

const string& ImagingObservation::GetComment() const{

	return _comment;
}

double* ImagingObservation::GetAnnotatorConfidence() const{
	return _annotatorConfidence.get();
}

const string& ImagingObservation::GetLabel() const{
	return _label;
}

bool ImagingObservation::GetIsPresent() const{
	return _isPresent;
}

const ReferencedGeometricShape* ImagingObservation::GetReferencedGeometricShape() const{
	return _referencedGeometricShape.get();
}

const ImagingObservationCharacteristicVector& ImagingObservation::GetImagingObservationCharacteristicCollection() const{

	return _imagingObservationCharachteristicCollection;
}

void ImagingObservation::SetCodeMeaning(const string& newVal){

	_codeMeaning = newVal;
}

void ImagingObservation::SetCodeValue(const string& newVal){

	_codeValue = newVal;
}

void ImagingObservation::SetCodingSchemeDesignator(const string& newVal){

	_codingSchemeDesignator = newVal;
}

void ImagingObservation::SetCodingSchemeVersion(const string& newVal){

	_codingSchemeVersion = newVal;
}

void ImagingObservation::SetComment(const string& newVal){

	_comment = newVal;
}

void ImagingObservation::SetAnnotatorConfidence(double* pConfidence){

	if (pConfidence == NULL)
		_annotatorConfidence.reset();
	else
		_annotatorConfidence.reset(new double(*pConfidence));
}

void ImagingObservation::SetLabel(const string& newVal){
	_label = newVal;
}

void ImagingObservation::SetIsPresent(bool newVal){
	_isPresent = newVal;
}

void ImagingObservation::SetReferencedGeometricShape(const ReferencedGeometricShape* pRefGeoShape){

	if (pRefGeoShape == NULL)
		_referencedGeometricShape.reset();
	else
		_referencedGeometricShape.reset(pRefGeoShape->Clone());
}

void ImagingObservation::SetImagingObservationCharacteristicCollection(const aim_lib::ImagingObservationCharacteristicVector& newVal){

	_imagingObservationCharachteristicCollection.assign(newVal.begin(), newVal.end());
}
