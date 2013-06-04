/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "Dimension.h"
#include "../AimEnum.h"
#include "CalculationResult.h"
#include "CompactCalculationResult.h"

using std::string;
using namespace aim_lib;
using iso_21090::CD;

CompactCalculationResult::CompactCalculationResult(){
}

CompactCalculationResult::CompactCalculationResult(const CompactCalculationResult& calculationResult) : CalculationResult(calculationResult) {
	*this = calculationResult;
}

CompactCalculationResult& CompactCalculationResult::operator=(const CompactCalculationResult& calculationResult){

	if (this != &calculationResult)
	{
		CalculationResult::operator=(calculationResult);
		_value = calculationResult._value;
		SetEncoding(calculationResult.GetEncoding());
		SetCompression(calculationResult.GetCompression());
	}

	return *this;
}

CompactCalculationResult* CompactCalculationResult::Clone() const{
	return new CompactCalculationResult(*this);
}

CompactCalculationResult::~CompactCalculationResult(){
}

const string& CompactCalculationResult::GetValue() const{
	return _value;
}

const CD* CompactCalculationResult::GetEncoding() const{
	return _encoding.get();
}

const CD* CompactCalculationResult::GetCompression() const{
	return _compression.get();
}

void CompactCalculationResult::SetValue(const string& newVal){
	_value = newVal;
}

void CompactCalculationResult::SetEncoding(const CD* newVal){
	_encoding.reset(newVal ? new CD(*newVal) : NULL);
}

void CompactCalculationResult::SetCompression(const CD* newVal){
	_compression.reset(newVal ? new CD(*newVal) : NULL);
}
