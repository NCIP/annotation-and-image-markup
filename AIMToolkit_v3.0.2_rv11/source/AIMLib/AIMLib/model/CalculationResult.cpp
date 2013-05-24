/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "Dimension.h"
#include "Coordinate.h"
#include "CalculationData.h"
#include "../AimEnum.h"
#include "CalculationResult.h"

using std::string;
using namespace aim_lib;

CalculationResult::CalculationResult(){
	_type = InvalidCalculationResultType;
}

CalculationResult::CalculationResult(const CalculationResult& calculationResult){
	*this = calculationResult;
}

CalculationResult& CalculationResult::operator=(const CalculationResult& calculationResult){

	if (this != &calculationResult)
	{
		_cagridId			= calculationResult._cagridId;
		_type				= calculationResult._type;
		_numberOfDimensions	= calculationResult._numberOfDimensions;
		_unitOfMeasure		= calculationResult._unitOfMeasure;

		this->SetDimensionCollection(calculationResult.GetDimensionCollection());
		this->SetCalculationDataCollection(calculationResult.GetCalculationDataCollection());
	}

	return *this;
}

CalculationResult::~CalculationResult(){
	_dimensionCollection.clear();
	_calculationDataCollection.clear();
}

CalculationResultType CalculationResult::GetType() const{

	return _type;
}

int CalculationResult::GetNumberOfDimensions() const{

	return _numberOfDimensions;
}

const std::string& CalculationResult::GetUnitOfMeasure() const{

	return _unitOfMeasure;
}

const DimensionVector& CalculationResult::GetDimensionCollection() const{

	return _dimensionCollection;
}

const CalculationDataVector& CalculationResult::GetCalculationDataCollection() const{

	return _calculationDataCollection;
}

void CalculationResult::SetType(CalculationResultType newVal){

	_type = newVal;
}

void CalculationResult::SetNumberOfDimensions(int newVal){

	_numberOfDimensions = newVal;
}

void CalculationResult::SetUnitOfMeasure(const std::string& newVal){

	_unitOfMeasure = newVal;
}

void CalculationResult::SetDimensionCollection(const DimensionVector& dimensionCollection){

	_dimensionCollection.assign(dimensionCollection.begin(), dimensionCollection.end());
}

void CalculationResult::SetCalculationDataCollection(const CalculationDataVector& dataCollection){

	_calculationDataCollection.assign(dataCollection.begin(), dataCollection.end());
}

const std::string CalculationResult::CalculationResultTypeToString(const CalculationResultType& type){
	std::string retVal;
	switch(type)
	{
		case Scalar:
			retVal = "Scalar";
			break;
		case Vector:
			retVal = "Vector";
			break;
		case Histogram:
			retVal = "Histogram";
			break;
		case Matrix:
			retVal = "Matrix";
			break;
		case Array:
			retVal = "Array";
			break;
	}
	return retVal;
}

const CalculationResultType CalculationResult::StringToCalculationResultType(const std::string& stringType){
	if (stringType == "Scalar")
		return Scalar;
	if (stringType == "Vector")
		return Vector;
	if (stringType == "Histogram")
		return Histogram;
	if (stringType == "Matrix")
		return Matrix;
	if (stringType == "Array")
		return Array;

	return InvalidCalculationResultType;
}
