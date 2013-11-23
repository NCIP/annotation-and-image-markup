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
