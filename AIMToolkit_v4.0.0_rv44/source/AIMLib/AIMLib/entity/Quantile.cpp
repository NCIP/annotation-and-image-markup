/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"
#include "CharacteristicQuantification.h"
#include "Quantile.h"

#include "../memdebug.h"

//#include <limits.h>

using std::string;
using namespace aim_lib;

Quantile::Quantile(void) : CharacteristicQuantification(C_QUANTIFICATION_QUANTILE_NAME), _bins(0), _minValue(0.0), _maxValue(0.0), _selectedBin(0){
}

Quantile::Quantile(const Quantile& quantile) : CharacteristicQuantification(quantile){
	*this = quantile;
}

Quantile::~Quantile(void){
}

Quantile& Quantile::operator=(const Quantile& quantile){
	if (this != &quantile)
	{
		CharacteristicQuantification::operator=(quantile);
		_bins			= quantile._bins;
		_selectedBin	= quantile._selectedBin;
		_minValue		= quantile._minValue;
		_maxValue		= quantile._maxValue;
	}

	return *this;
}

Quantile* Quantile::Clone() const{
	return new Quantile(*this);
}

const CharacteristicQuantification::QuantificationType Quantile::GetQuantificationType() const{
	return QT_Quantile;
}

int Quantile::GetBins() const{
	return _bins;
}

double Quantile::GetMinValue() const{
	return _minValue;
}

double Quantile::GetMaxValue() const{
	return _maxValue;
}

int Quantile::GetSelectedBin() const{
	return _selectedBin;
}

void Quantile::SetBins(int newVal){
	_bins = newVal;
}

void Quantile::SetMinValue(double minValue){
	_minValue = minValue;
}

void Quantile::SetMaxValue(double maxValue){
	_maxValue = maxValue;
}

void Quantile::SetSelectedBin(int selectedBin){
	_selectedBin = selectedBin;
}
