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
#include "Interval.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;

Interval::Interval(void) : CharacteristicQuantification(C_QUANTIFICATION_INTERVAL_NAME),
		_minValue(0.0), _maxValue(0.0), _minOperator(None), _maxOperator(None){
}

Interval::Interval(const Interval& interval) : CharacteristicQuantification(interval){
	*this = interval;
}

Interval::~Interval(void){
}

Interval& Interval::operator=(const Interval& interval){
	if (this != &interval)
	{
		CharacteristicQuantification::operator=(interval);
		_minValue		= interval._minValue;
		_maxValue		= interval._maxValue;
		_minOperator	= interval._minOperator;
		_maxOperator	= interval._maxOperator;
		_ucumString		= interval._ucumString;
	}

	return *this;
}

Interval* Interval::Clone() const{
	return new Interval(*this);
}

const CharacteristicQuantification::QuantificationType Interval::GetQuantificationType() const{
	return QT_Interval;
}

double Interval::GetMinValue() const{
	return _minValue;
}

double Interval::GetMaxValue() const{
	return _maxValue;
}

ComparisonOperatorType Interval::GetMinOperator() const{
	return _minOperator;
}

ComparisonOperatorType Interval::GetMaxOperator() const{
	return _maxOperator;
}

const string& Interval::GetUcumString() const{
	return _ucumString;
}

void Interval::SetMinValue(double newVal){
	_minValue = newVal;
}

void Interval::SetMaxValue(double newVal){
	_maxValue = newVal;
}

void Interval::SetMinOperator(ComparisonOperatorType newVal){
	_minOperator = newVal;
}

void Interval::SetMaxOperator(ComparisonOperatorType newVal){
	_maxOperator = newVal;
}

void Interval::SetUcumString(const string& newVal){
	_ucumString = newVal;
}
