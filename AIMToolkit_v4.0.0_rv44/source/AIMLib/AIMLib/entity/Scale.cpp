/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"
#include "CharacteristicQuantification.h"
#include "Scale.h"

#include "../memdebug.h"

#include <cassert>

using std::string;
using namespace aim_lib;

Scale::Scale(void) : CharacteristicQuantification(C_QUANTIFICATION_SCALE_NAME), _scaleType(InvalidScaleType){
}

Scale::Scale(const Scale& scale) : CharacteristicQuantification(scale){
	*this = scale;
}

Scale::~Scale(void){
}

Scale& Scale::operator=(const Scale& scale){
	if (this != &scale)
	{
		CharacteristicQuantification::operator =(scale);
		_value			= scale._value;
		_scaleType		= scale._scaleType;
	}

	return *this;
}

Scale* Scale::Clone() const{
	return new Scale(*this);
}

const CharacteristicQuantification::QuantificationType Scale::GetQuantificationType() const{
	return QT_Scale;
}

const string& Scale::GetValue() const{
	return _value;
}

const Scale::ScaleType Scale::GetScaleType() const{
	return _scaleType;
}

void Scale::SetValue(const string& newVal){
	_value = newVal;
}

void Scale::SetScaleType(ScaleType newVal){
	_scaleType = newVal;
}

const std::string Scale::ScaleTypeToString(const Scale::ScaleType& type)
{
	std::string retVal;
	switch(type)
	{
		case Scale::Ordinal:
			retVal = "Ordinal";
			break;
		case Scale::Nominal:
			retVal = "Nominal";
			break;
		case Scale::Ratio:
			retVal = "Ratio";
			break;
		default:
			assert(false);
	}
	return retVal;
}

const Scale::ScaleType Scale::StringToScaleType(const std::string& scaleType)
{
	ScaleType retVal = Scale::InvalidScaleType;

	if (scaleType == "Ordinal")
		retVal = Scale::Ordinal;
	else if (scaleType == "Nominal")
		retVal = Scale::Nominal;
	else if (scaleType == "Ratio")
		retVal = Scale::Ratio;
	else
		assert(false);

	return retVal;
}
