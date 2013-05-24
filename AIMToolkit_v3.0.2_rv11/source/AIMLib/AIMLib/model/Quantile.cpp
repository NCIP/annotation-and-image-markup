/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include <limits.h>

#include "AimBase.h"
#include "CharacteristicQuantification.h"
#include "Quantile.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;

Quantile::Quantile(void) : CharacteristicQuantification(C_QUANTIFICATION_QUANTILE_NAME)
{
	_bin = INT_MIN;
}

Quantile::Quantile(const Quantile& quantile) : CharacteristicQuantification(quantile)
{
	*this = quantile;
}

Quantile::~Quantile(void)
{
}

Quantile& Quantile::operator=(const Quantile& quantile)
{
	if (this != &quantile)
	{
		CharacteristicQuantification::operator=(quantile);
		_bin = quantile._bin;
	}

	return *this;
}

Quantile* Quantile::Clone() const
{
	return new Quantile(*this);
}

int Quantile::GetBin() const
{
	return _bin;
}

void Quantile::SetBin(int newVal)
{
	_bin = newVal;
}
