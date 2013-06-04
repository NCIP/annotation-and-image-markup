/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"
#include "../AimEnum.h"
#include "CharacteristicQuantification.h"
#include "Numerical.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;

Numerical::Numerical(void) : CharacteristicQuantification(C_QUANTIFICATION_NUMERICAL_NAME),
_value(0.0), _operator(None){
}

Numerical::Numerical(const Numerical& numerical) : CharacteristicQuantification(numerical){
	*this = numerical;
}

Numerical::~Numerical(void){
}

Numerical& Numerical::operator=(const Numerical& numerical){
	if (this != &numerical)
	{
		CharacteristicQuantification::operator=(numerical);
		_value = numerical._value;
		_ucumString	= numerical._ucumString;
		_operator	= numerical._operator;
	}

	return *this;
}

Numerical* Numerical::Clone() const{
	return new Numerical(*this);
}

const CharacteristicQuantification::QuantificationType Numerical::GetQuantificationType() const{
	return QT_Numerical;
}

double Numerical::GetValue() const{
	return _value;
}

const string& Numerical::GetUcumString() const{
	return _ucumString;
}

ComparisonOperatorType Numerical::GetOperator() const{
	return _operator;
}

void Numerical::SetValue(double newVal){
	_value = newVal;
}

void Numerical::SetUcumString(const string& newVal){
	_ucumString = newVal;
}

void Numerical::SetOperator(ComparisonOperatorType newVal){
	_operator = newVal;
}
