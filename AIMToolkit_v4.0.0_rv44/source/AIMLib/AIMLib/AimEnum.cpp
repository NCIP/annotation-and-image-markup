/*
*  2007 – 2013 Copyright Northwestern University
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

const std::string AimEnum::GetAimVersionString(AimVersion aimVersion){
	switch(aimVersion)
	{
	case AIMv1_0:
		return "AIMv1_0";
	case AIMv2_0:
		return "AIMv2_0";
	case AIMv3_0_1:
		return "AIMv3_0_1";
	case AIMv3_0_2:
		return "AIMv3_0_2";
	case AIMv4_0:
		return "AIMv4_0";
	default:
		assert(false); // unexpected version
		return "";
	};
}
