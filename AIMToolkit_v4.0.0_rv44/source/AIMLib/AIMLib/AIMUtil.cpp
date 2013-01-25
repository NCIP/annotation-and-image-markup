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
#include <limits.h>
#include <sstream>

#include "dcmtk/dcmdata/dcuid.h"

#include "util/DateTime.h"
#include "AIMUtil.h"

using namespace aim_lib;

OFDateTime AIMUtil::DateTimeConvert(const std::string& dicomDateTime)
{
	OFDateTime ofDateTime;
	ofDateTime.setISOFormattedDateTime(dicomDateTime);

	return ofDateTime;
}

OFDateTime AIMUtil::DateTimeConvert(const aim_lib::DateTime& dateTime)
{
	OFDateTime ofDateTime(
		OFDate(dateTime.GetYear(), dateTime.GetMonth(), dateTime.GetDay()),
		OFTime(dateTime.GetHour(), dateTime.GetMinute(), dateTime.GetSecond()));

	return ofDateTime;
}

aim_lib::DateTime AIMUtil::DateTimeConvert(const altova::DateTime& altovaDateTime)
{
	aim_lib::DateTime dateTime(altovaDateTime.Year(), altovaDateTime.Month(), altovaDateTime.Day(),
		altovaDateTime.Hour(), altovaDateTime.Minute(), altovaDateTime.Second());

	return dateTime;
}

DateTime AIMUtil::DateTimeConvert(const OFDateTime& ofDateTimeIn)
{
	aim_lib::DateTime dateTime(ofDateTimeIn.getDate().getYear(), ofDateTimeIn.getDate().getMonth(), ofDateTimeIn.getDate().getDay(),
		ofDateTimeIn.getTime().getHour(), ofDateTimeIn.getTime().getMinute(), ofDateTimeIn.getTime().getSecond());

	return dateTime;
}

altova::DateTime AIMUtil::DateToAltovaDateTime(const aim_lib::Date& dateIn)
{
	altova::DateTime altovaDateTime(dateIn.GetYear(), dateIn.GetMonth(), dateIn.GetDay(), 0, 0, 0.0);
	
	return altovaDateTime;
}

altova::DateTime AIMUtil::DateTimeToAltovaDateTime(const aim_lib::DateTime& timeIn)
{
	altova::DateTime altovaDateTime(timeIn.GetYear(), timeIn.GetMonth(), timeIn.GetDay(), timeIn.GetHour(), timeIn.GetMinute(), timeIn.GetSecond());
	
	return altovaDateTime;
}

aim_lib::Date AIMUtil::DateConvert(const OFDate& ofDateIn)
{
	aim_lib::Date date(ofDateIn.getYear(), ofDateIn.getMonth(), ofDateIn.getDay());

	return date;
}

aim_lib::Date AIMUtil::DateConvert(const altova::DateTime& dateIn)
{
	aim_lib::Date date(dateIn.Year(), dateIn.Month(), dateIn.Day());

	return date;
}

OFDate AIMUtil::DateConvert(const aim_lib::Date& dateIn)
{
	OFDate ofDate(dateIn.GetYear(), dateIn.GetMonth(), dateIn.GetDay());

	return ofDate;
}

OFDate AIMUtil::DateConvert(const std::string& dicomDateIn)
{
	OFDate ofDate;
	ofDate.setISOFormattedDate(dicomDateIn);

	return ofDate;
}

aim_lib::Time AIMUtil::TimeConvert(const OFTime& ofTimeIn)
{
	aim_lib::Time time(ofTimeIn.getHour(), ofTimeIn.getMinute(), ofTimeIn.getSecond());

	return time;
}

OFTime AIMUtil::TimeConvert(const aim_lib::Time& timeIn)
{
	OFTime ofTime(timeIn.GetHour(), timeIn.GetMinute(), timeIn.GetSecond());

	return ofTime;
}

OFTime AIMUtil::TimeConvert(const std::string& dicomTime)
{
	OFTime ofTime;
	ofTime.setISOFormattedTime(dicomTime);

	return ofTime;
}

std::string AIMUtil::IntToString(int numIn)
{
	std::stringstream ss;
	ss << numIn;
	return ss.str();
}

int AIMUtil::StringToInt(const std::string& strIn)
{
	int retVal = atoi(strIn.data());
	//errno; 
	assert(retVal != INT_MAX || retVal != INT_MIN);

	return retVal;
}

const std::string AIMUtil::DoubleToString(double numIn)
{
	std::stringstream ss;
	ss << numIn;
	return ss.str();
}

double AIMUtil::StringToDouble(const std::string &strIn)
{
	double retVal = atof(strIn.c_str());

	return retVal;
}

const std::string AIMUtil::LongToString(long numIn)
{
	std::stringstream ss;
	ss << numIn;
	return ss.str();
}

bool AIMUtil::IsNumeric(const std::string& strIn)
{
	std::istringstream iss(strIn);
	std::ostringstream oss;
	double x;
	iss >> x;
	oss << x;

	return strIn == oss.str();
}

bool AIMUtil::isLeapYear(int year)
{
	/*
	 Leap year is divisible by 4, but when it's divisible by 100, it should be divisible by 400.
	 Leap years examples: 1896, 1904, 1996, 2000
	 Year 1900 is not a leap year.
	*/
	if (year != 0 && year%4 == 0)
		return year%100 == 0 ? year%400 == 0 : true;

	return false;
}

int AIMUtil::compareNoCase(const std::string& str1, const std::string& str2)
{
#if defined(UNICODE) || defined(_UNICODE)
	// see: http://stackoverflow.com/questions/11635/case-insensitive-string-comparison-in-c
	assert(false); // this cannot properly handle UNICODE strings
#endif

	// NOTE: Can work for non-UNICODE only

	if (str1.length() < str2.length())
		return -1;
	if (str1.length() > str2.length())
		return 1;

	for(size_t i=0; i < str1.length(); i++)
	{
		if (toupper(str1[i]) < toupper(str2[i]))
			return -1;
		if (toupper(str1[i]) > toupper(str2[i]))
			return 1;
	}
	return 0;

	// This is Windows only
	//return _stricmp(str1.c_str(), str2.c_str());
}
