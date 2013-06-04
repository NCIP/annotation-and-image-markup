/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "AimBase.h"
#include "CharacteristicQuantification.h"

#include "../AimEnum.h"
#include "Numerical.h"
#include "Quantile.h"
#include "NonQuantifiable.h"
#include "Scale.h"
#include "Interval.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;

CharacteristicQuantification::CharacteristicQuantification(const string& typeName) : AimBase(typeName)
{
}

CharacteristicQuantification::CharacteristicQuantification(const CharacteristicQuantification& characteristicQuantification) : AimBase(characteristicQuantification)
{
	*this = characteristicQuantification;
}

CharacteristicQuantification& CharacteristicQuantification::operator=(const CharacteristicQuantification& characteristicQuantification)
{
	if (this != &characteristicQuantification)
	{
		AimBase::operator=(characteristicQuantification);
		_cagridId	= characteristicQuantification._cagridId;
		_name		= characteristicQuantification._name;

		SetAnnotatorConfidence(characteristicQuantification.GetAnnotatorConfidence());
	}
	return *this;
}

CharacteristicQuantification::~CharacteristicQuantification(void)
{
}

const string& CharacteristicQuantification::GetName() const
{
	return _name;
}

double* CharacteristicQuantification::GetAnnotatorConfidence() const
{
	return _annotatorConfidence.get();
}

void CharacteristicQuantification::SetName(const string& newVal)
{
	_name = newVal;
}

void CharacteristicQuantification::SetAnnotatorConfidence(double* pConfidence)
{
	if (pConfidence == NULL)
		_annotatorConfidence.reset();
	else
		_annotatorConfidence.reset(new double(*pConfidence));
}

const CharacteristicQuantification::E_QuantificationType CharacteristicQuantification::GetQuantificationType() const
{
	if (dynamic_cast<const Numerical*>(this) != NULL)
		return QT_Numerical;
	else if(dynamic_cast<const Quantile*>(this) != NULL)
		return QT_Quantile;
	else if(dynamic_cast<const NonQuantifiable*>(this) != NULL)
		return QT_Non_Quantifiable;
	else if(dynamic_cast<const Scale*>(this) != NULL)
		return QT_Scale;
	else if(dynamic_cast<const Interval*>(this) != NULL)
		return QT_Interval;
	else
		return QT_Unknown;
}
