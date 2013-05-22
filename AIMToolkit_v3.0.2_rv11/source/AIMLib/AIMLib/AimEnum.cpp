/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "stdafx.h"

#include "AimEnum.h"

using std::string;
using namespace aim_lib;

const string AimEnum::ComparisonOperatorTypeToString(const ComparisonOperatorType& type)
{
	string retVal("Invalid");
	switch(type)
	{
	case None:
		retVal = "";
		break;
	case Equal:
		retVal = "Equal";
		break;
	case NotEqual:
		retVal = "NotEqual";
		break;
	case LessThan:
		retVal = "LessThan";
		break;
	case LessThanEqual:
		retVal = "LessThanEqual";
		break;
	case GreaterThan:
		retVal = "GreaterThan";
		break;
	case GreaterThanEqual:
		retVal = "GreaterThanEqual";
		break;
	}

	return retVal;
}

const ComparisonOperatorType AimEnum::StringToComparisonOperatorType(const string& stringType)
{
	if (stringType == "")
		return None;
	if (stringType == "Equal")
		return Equal;
	if (stringType == "NotEqual")
		return NotEqual;
	if (stringType == "LessThan")
		return LessThan;
	if (stringType == "LessThanEqual")
		return LessThanEqual;
	if (stringType == "GreaterThan")
		return GreaterThan;
	if (stringType == "GreaterThanEqual")
		return GreaterThanEqual;

	return InvalidComparisonOperatorType;
}
