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

#include "Coordinate.h"
#include "CalculationData.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;

CalculationData::CalculationData(){
}

CalculationData::CalculationData(const CalculationData& data){
	*this = data;
}

CalculationData& CalculationData::operator=(const CalculationData& data){

	if (this != &data)
	{
		_value = data._value;

		this->SetCoordinateCollection(data.GetCoordinateCollection());
	}

	return *this;
}

CalculationData::~CalculationData(void){
	_coordinateCollection.clear();
}

const string& CalculationData::GetValue() const{
	return _value;
}

const CoordinateVector& CalculationData::GetCoordinateCollection() const {
	return _coordinateCollection;
}

void CalculationData::SetValue(const string& newValue){
	_value = newValue;
}

void CalculationData::SetCoordinateCollection(const aim_lib::CoordinateVector &coordinateCollection){
	_coordinateCollection.assign(coordinateCollection.begin(), coordinateCollection.end());
}
