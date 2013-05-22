/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "../stdafx.h"

#include "Dimension.h"
#include "Coordinate.h"
#include "CalculationData.h"
#include "../AimEnum.h"
#include "CalculationResult.h"
#include "ExtendedCalculationResult.h"

using namespace aim_lib;

ExtendedCalculationResult::ExtendedCalculationResult(){
}

ExtendedCalculationResult::ExtendedCalculationResult(const ExtendedCalculationResult& calculationResult){
	*this = calculationResult;
}

ExtendedCalculationResult& ExtendedCalculationResult::operator=(const ExtendedCalculationResult& calculationResult){
	if (this != &calculationResult)
	{
		CalculationResult::operator=(calculationResult);
		this->SetCalculationDataCollection(calculationResult.GetCalculationDataCollection());
	}

	return *this;
}

ExtendedCalculationResult* ExtendedCalculationResult::Clone() const {
	return new ExtendedCalculationResult(*this);
}

ExtendedCalculationResult::~ExtendedCalculationResult(){
	_calculationDataCollection.clear();
}

const CalculationDataVector& ExtendedCalculationResult::GetCalculationDataCollection() const{
	return _calculationDataCollection;
}

void ExtendedCalculationResult::SetCalculationDataCollection(const CalculationDataVector& dataCollection){
	_calculationDataCollection.assign(dataCollection.begin(), dataCollection.end());
}
