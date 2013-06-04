/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "ReferencedCalculation.h"

using std::string;
using namespace aim_lib;

ReferencedCalculation::ReferencedCalculation(){

}

ReferencedCalculation::ReferencedCalculation(const ReferencedCalculation& referencedCalculation){
	*this = referencedCalculation;
}

ReferencedCalculation& ReferencedCalculation::operator=(const ReferencedCalculation& referencedCalculation){
	if (this != &referencedCalculation)
	{
		_cagridId			= referencedCalculation._cagridId;
		_uniqueIdentifier	= referencedCalculation._uniqueIdentifier;
	}

	return *this;
}

ReferencedCalculation::~ReferencedCalculation(){

}

const string& ReferencedCalculation::GetUniqueIdentifier() const{

	return _uniqueIdentifier;
}

void ReferencedCalculation::SetUniqueIdentifier(const string& newVal){

	_uniqueIdentifier = newVal;
}
