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
