/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "../AimEnum.h"

#include "Dimension.h"
#include "Coordinate.h"
#include "CalculationData.h"
#include "CalculationResult.h"
#include "ReferencedCalculation.h"
#include "ReferencedGeometricShape.h"
#include "Calculation.h"

using std::string;
using namespace aim_lib;

Calculation::Calculation(){

}

Calculation::Calculation(const Calculation& calculation){
	*this = calculation;
}

Calculation& Calculation::operator=(const Calculation& calculation){

	if (this != &calculation)
	{
		_cagridId				= calculation._cagridId;
		_uid					= calculation._uid;
		_codeMeaning			= calculation._codeMeaning;
		_codeValue				= calculation._codeValue;
		_codingSchemeDesignator	= calculation._codingSchemeDesignator;
		_codingSchemeVersion	= calculation._codingSchemeVersion;
		_description			= calculation._description;
		_mathML					= calculation._mathML;
		_algorithmName			= calculation._algorithmName;
		_algorithmVersion		= calculation._algorithmVersion;

		this->SetCalculationResultCollection(calculation.GetCalculationResultCollection());
		this->SetReferencedCalculationCollection(calculation.GetReferencedCalculationCollection());
		this->SetReferencedGeometricShapeCollection(calculation.GetReferencedGeometricShapeCollection());
	}

	return *this;
}

Calculation::~Calculation(){

}

const string& Calculation::GetUID() const{

	return _uid;
}

const string& Calculation::GetCodeMeaning() const{

	return _codeMeaning;
}

const string& Calculation::GetCodeValue() const{

	return _codeValue;
}

const string& Calculation::GetCodingSchemeDesignator() const{

	return _codingSchemeDesignator;
}

const string& Calculation::GetCodingSchemeVersion() const{

	return _codingSchemeVersion;
}

const string& Calculation::GetDescription() const {

	return _description;
}

const string& Calculation::GetMathML() const{

	return _mathML;
}

const string& Calculation::GetAlgorithmName() const{

	return _algorithmName;
}

const string& Calculation::GetAlgorithmVersion() const{

	return _algorithmVersion;
}

const CalcResultVector& Calculation::GetCalculationResultCollection() const{

	return  _calculationResultCollection;
}

const ReferencedCalcVector& Calculation::GetReferencedCalculationCollection() const{

	return _referencedCalculationCollection;
}

const ReferencedGeometricShapeVector& Calculation::GetReferencedGeometricShapeCollection() const{

	return _referencedGeoShapeCollection;
}

void Calculation::SetUID(const string& newVal){

	_uid = newVal;
}

void Calculation::SetCodeMeaning(const string& newVal){

	_codeMeaning = newVal;
}

void Calculation::SetCodeValue(const string& newVal){

	_codeValue = newVal;
}

void Calculation::SetCodingSchemeDesignator(const string& newVal){

	_codingSchemeDesignator = newVal;
}

void Calculation::SetCodingSchemeVersion(const string& newVal){

	_codingSchemeVersion = newVal;
}

void Calculation::SetDescription(const string& newVal){

	_description = newVal;
}

void Calculation::SetMathML(const string& newVal){

	_mathML = newVal;
}

void Calculation::SetAlgorithmName(const string& newVal){

	_algorithmName = newVal;
}

void Calculation::SetAlgorithmVersion(const string& newVal){

	_algorithmVersion = newVal;
}

void Calculation::SetCalculationResultCollection(const CalcResultVector& calculationResults){
	_calculationResultCollection.assign(calculationResults.begin(), calculationResults.end());
}

void Calculation::SetReferencedCalculationCollection(const ReferencedCalcVector& referencedCalculations){
	_referencedCalculationCollection.assign(referencedCalculations.begin(), referencedCalculations.end());
}

void Calculation::SetReferencedGeometricShapeCollection(const ReferencedGeometricShapeVector& referencedGeoShapes){
	_referencedGeoShapeCollection.assign(referencedGeoShapes.begin(), referencedGeoShapes.end());
}
