/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "Coordinate.h"
#include "CalculationData.h"

using namespace aim_lib;

CalculationData::CalculationData(){
}

CalculationData::CalculationData(const CalculationData& data){
	*this = data;
}

CalculationData& CalculationData::operator=(const CalculationData& data){

	if (this != &data)
	{
		_cagridId	= data._cagridId;
		_value		= data._value;

		this->SetCoordinateCollection(data.GetCoordinateCollection());
	}

	return *this;
}

CalculationData::~CalculationData(void){
	_coordinateCollection.clear();
}

double CalculationData::GetValue() const{
	return _value;
}

const CoordinateVector& CalculationData::GetCoordinateCollection() const {
	return _coordinateCollection;
}

void CalculationData::SetValue(double newValue){
	_value = newValue;
}

void CalculationData::SetCoordinateCollection(const aim_lib::CoordinateVector &coordinateCollection){
	_coordinateCollection.assign(coordinateCollection.begin(), coordinateCollection.end());
}
