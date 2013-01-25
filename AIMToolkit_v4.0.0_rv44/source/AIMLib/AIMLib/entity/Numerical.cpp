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
