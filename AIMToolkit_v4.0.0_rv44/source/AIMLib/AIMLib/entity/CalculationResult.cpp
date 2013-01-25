/*
Copyright (c) 2008-2013, Northwestern University
All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 
  Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
 
  Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
 
  Neither the name of the Northwestern University nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
