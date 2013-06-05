/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "Dimension.h"
#include "CalculationResult.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;
using iso_21090::CD;

CalculationResult::CalculationResult() : _type(InvalidCalculationResultType){
}

CalculationResult::CalculationResult(const CalculationResult& calculationResult){
	*this = calculationResult;
}

CalculationResult& CalculationResult::operator=(const CalculationResult& calculationResult){

	if (this != &calculationResult)
	{
		_type			= calculationResult._type;
		_dataType		= calculationResult._dataType;
		_unitOfMeasure	= calculationResult._unitOfMeasure;

		SetDimensionCollection(calculationResult.GetDimensionCollection());
	}

	return *this;
}

CalculationResult::~CalculationResult(){
	_dimensionCollection.clear();
}

CalculationResult::CalculationResultType CalculationResult::GetType() const{
	return _type;
}

const CD& CalculationResult::GetDataType() const{
	return _dataType;
}

const std::string& CalculationResult::GetUnitOfMeasure() const{
	return _unitOfMeasure;
}

const DimensionVector& CalculationResult::GetDimensionCollection() const{
	return _dimensionCollection;
}

void CalculationResult::SetType(CalculationResult::CalculationResultType newVal){
	_type = newVal;
}

void CalculationResult::SetDataType(const CD& newVal){
	_dataType = newVal;
}

void CalculationResult::SetUnitOfMeasure(const std::string& newVal){
	_unitOfMeasure = newVal;
}

void CalculationResult::SetDimensionCollection(const DimensionVector& dimensionCollection){
	_dimensionCollection.assign(dimensionCollection.begin(), dimensionCollection.end());
}

const std::string CalculationResult::CalculationResultTypeToString(const CalculationResult::CalculationResultType& type){
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
		case Binary:
			retVal = "Binary";
			break;
	}
	return retVal;
}

const CalculationResult::CalculationResultType CalculationResult::StringToCalculationResultType(const std::string& stringType){
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
	if (stringType == "Binary")
		return Binary;

	return InvalidCalculationResultType;
}
