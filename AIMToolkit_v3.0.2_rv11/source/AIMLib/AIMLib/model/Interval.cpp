/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "../AimEnum.h"

#include "AimBase.h"
#include "CharacteristicQuantification.h"
#include "Interval.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;

Interval::Interval(void) : CharacteristicQuantification(C_QUANTIFICATION_INTERVAL_NAME)
{
	_minValue		= 0.0;
	_maxValue		= 0.0;
	_minOperator	= None;
	_maxOperator	= None;
}

Interval::Interval(const Interval& interval) : CharacteristicQuantification(interval)
{
	*this = interval;
}

Interval::~Interval(void)
{
}

Interval& Interval::operator=(const Interval& interval)
{
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

Interval* Interval::Clone() const
{
	return new Interval(*this);
}

double Interval::GetMinValue() const
{
	return _minValue;
}

double Interval::GetMaxValue() const
{
	return _maxValue;
}

ComparisonOperatorType Interval::GetMinOperator() const
{
	return _minOperator;
}

ComparisonOperatorType Interval::GetMaxOperator() const
{
	return _maxOperator;
}

const string& Interval::GetUcumString() const
{
	return _ucumString;
}

void Interval::SetMinValue(double newVal)
{
	_minValue = newVal;
}

void Interval::SetMaxValue(double newVal)
{
	_maxValue = newVal;
}

void Interval::SetMinOperator(ComparisonOperatorType newVal)
{
	_minOperator = newVal;
}

void Interval::SetMaxOperator(ComparisonOperatorType newVal)
{
	_maxOperator = newVal;
}

void Interval::SetUcumString(const string& newVal)
{
	_ucumString = newVal;
}
