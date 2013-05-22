/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "../stdafx.h"

#include "Parameter.h"

using std::string;
using namespace aim_lib;
using iso_21090::CD;

Parameter::Parameter(void){
}

Parameter::Parameter(const Parameter& parameter){
	_name	= parameter._name;
	_value	= parameter._value;
	SetDataType(parameter.GetDataType());
}

Parameter::~Parameter(void){
}

const string& Parameter::GetName() const{
	return _name;
}

const string& Parameter::GetValue() const{
	return _value;
}

const CD& Parameter::GetDataType() const{
	return _dataType;
}

void Parameter::SetName(const string& newVal){
	_name = newVal;
}

void Parameter::SetValue(const string& newVal){
	_value = newVal;
}

void Parameter::SetDataType(const CD& newVal){
	_dataType = newVal;
}
