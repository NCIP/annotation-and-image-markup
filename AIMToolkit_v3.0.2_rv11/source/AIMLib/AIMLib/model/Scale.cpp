/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "AimBase.h"
#include "CharacteristicQuantification.h"
#include "Scale.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;

Scale::Scale(void) : CharacteristicQuantification(C_QUANTIFICATION_SCALE_NAME)
{
}

Scale::Scale(const Scale& scale) : CharacteristicQuantification(scale)
{
	*this = scale;
}

Scale::~Scale(void)
{
}

Scale& Scale::operator=(const Scale& scale)
{
	if (this != &scale)
	{
		CharacteristicQuantification::operator =(scale);
		_value			= scale._value;
		_comment		= scale._comment;
		_description	= scale._description;
	}

	return *this;
}

Scale* Scale::Clone() const
{
	return new Scale(*this);
}

const string& Scale::GetValue() const
{
	return _value;
}

const string& Scale::GetComment() const
{
	return _comment;
}

const string& Scale::GetDescription() const
{
	return _description;
}

void Scale::SetValue(const string& newVal)
{
	_value = newVal;
}

void Scale::SetComment(const string& newVal)
{
	_comment = newVal;
}

void Scale::SetDescription(const string& newVal)
{
	_description = newVal;
}
