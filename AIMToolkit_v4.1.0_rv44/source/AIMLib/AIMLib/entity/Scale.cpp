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
