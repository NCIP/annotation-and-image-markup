/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "stdafx.h"
#include <limits.h>
#include <sstream>

#include "dcmtk/dcmdata/dcuid.h"

#include "AIMUtil.h"

using namespace aim_lib;

//OFDateTime AIMUtil::DateTimeConvert(const time_t &timeIn)
//{
//	struct tm *tmTime;
//	tmTime = localtime(&timeIn);
//	OFDateTime ofDateTime;
//	ofDateTime.setDateTime(1900+tmTime->tm_year, tmTime->tm_mon+1, tmTime->tm_mday, tmTime->tm_hour, tmTime->tm_min, tmTime->tm_sec);
//
//	return ofDateTime;
//}

OFDateTime AIMUtil::DateTimeConvert(const std::string& dicomDateTime)
{
	OFDateTime ofDateTime;
	ofDateTime.setISOFormattedDateTime(dicomDateTime.c_str());

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
//
//time_t AIMUtil::DateTimeConvert(const altova::DateTime& altovaDateTime)
//{
//	struct tm tmTime;
//
//	// Date
//	tmTime.tm_year = altovaDateTime.Year() - 1900;
//	tmTime.tm_mon = altovaDateTime.Month() - 1;
//	tmTime.tm_mday = altovaDateTime.Day();
//
//	// Time
//	tmTime.tm_hour = altovaDateTime.Hour();
//	tmTime.tm_min = altovaDateTime.Minute();
//	tmTime.tm_sec = min(max((int)altovaDateTime.Second(), 0), 59); // (0 <= sec < 60)
//
//	return mktime(&tmTime);
//}
//
//altova::DateTime AIMUtil::DateTimeToAltovaDateTime(const time_t& timeIn)
//{
//	struct tm *tmTime;
//	tmTime = localtime(&timeIn);
//
//	if (tmTime == NULL)
//		return altova::DateTime();
//	
//	return altova::DateTime(1900+tmTime->tm_year, tmTime->tm_mon+1, tmTime->tm_mday, tmTime->tm_hour, tmTime->tm_min, tmTime->tm_sec);
//}

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
//
//time_t AIMUtil::DateTimeConvert(const OFDateTime& ofDateTimeIn)
//{
//	struct tm tmTime;
//
//	// Date
//	tmTime.tm_year = ofDateTimeIn.getDate().getYear() - 1900;
//	tmTime.tm_mon = ofDateTimeIn.getDate().getMonth() - 1;
//	tmTime.tm_mday = ofDateTimeIn.getDate().getDay();
//
//	// Time
//	tmTime.tm_hour = ofDateTimeIn.getTime().getHour();
//	tmTime.tm_min = ofDateTimeIn.getTime().getMinute();
//	tmTime.tm_sec = min(max((int)ofDateTimeIn.getTime().getSecond(), 0), 59); // (0 <= sec < 60)
//
//	return mktime(&tmTime);
//}
//
//time_t AIMUtil::DateConvert(const OFDate& ofDateIn)
//{
//	struct tm tmTime;
//
//	// Date
//	tmTime.tm_year = ofDateIn.getYear() - 1900;
//	tmTime.tm_mon = ofDateIn.getMonth() - 1;
//	tmTime.tm_mday = ofDateIn.getDay();
//
//	// Time
//	tmTime.tm_hour = 12;
//	tmTime.tm_min = 0;
//	tmTime.tm_sec = 0;
//
//	return mktime(&tmTime);
//}

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
	ofDate.setISOFormattedDate(dicomDateIn.c_str());

	return ofDate;
}

//OFDate AIMUtil::DateConvert(const time_t &timeIn)
//{
//	struct tm *tmTime;
//	tmTime = localtime(&timeIn);
//	OFDate ofDate;
//	ofDate.setDate(1900+tmTime->tm_year, tmTime->tm_mon+1, tmTime->tm_mday);
//
//	return ofDate;
//}

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
	ofTime.setISOFormattedTime(dicomTime.c_str());

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
