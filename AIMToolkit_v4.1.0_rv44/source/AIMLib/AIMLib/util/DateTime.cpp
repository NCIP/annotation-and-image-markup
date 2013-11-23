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

#include "DateTime.h"

#include "../AIMUtil.h"

using namespace aim_lib;

//
// *******************  Date **************************
//
Date::Date(int year, int month, int day) : _year(year), _month(month), _day(day)
{
}

Date::Date(const Date& date)
{
	_year	= date._year;
	_month	= date._month;
	_day	= date._day;
}

Date::Date(const time_t& t) : _year(1), _month(1), _day(1)
{
	struct tm *tmTime;
	tmTime = localtime(&t);

	if (tmTime == NULL)
		return;

	_year = tmTime->tm_year + 1900;
	_month = tmTime->tm_mon + 1;
	_day = tmTime->tm_mday;
}

Date::Date(const std::string& dicomDate) : _year(1), _month(1), _day(1)
{
	OFDate ofDate = AIMUtil::DateConvert(dicomDate.c_str());
	if (ofDate.isValid())
	{
		_year = ofDate.getYear();
		_month = ofDate.getMonth();
		_day = ofDate.getDay();
	}
}

Date::~Date()
{
}

bool Date::operator== (const Date& dateIn) const
{
	return _year == dateIn._year && _month == dateIn._month && _day == dateIn._day;
}

bool Date::operator!= (const Date& dateIn) const
{
	return !((*this) == dateIn);
}

Date Date::Today()
{
	time_t ttNow;
	time(&ttNow);

	return Date(ttNow);
}

int Date::GetYear() const
{
	return _year;
}

int Date::GetMonth() const
{
	return _month;
}

int Date::GetDay() const
{
	return _day;
}

void Date::SetYear(int year)
{
	_year = year;
}

void Date::SetMonth(int month)
{
	_month = month;
}

void Date::SetDay(int day)
{
	_day = day;
}

bool Date::IsEmpty() const
{
	return (*this) == Date();
}

std::string Date::GetDicomFormatedDate() const
{
	OFString formattedDate;
	AIMUtil::DateConvert(*this).getISOFormattedDate(formattedDate, false); // can be empty

	return formattedDate.c_str();
}


//
// *****************  DateTime ************************
//
DateTime::DateTime(int year, int month, int day, int hour, int minute, double second) :
	_date(year, month, day), _hour(hour), _min(minute), _second(second)
{
}

DateTime::DateTime(const DateTime& dateTime)
{
	_date	= dateTime._date;
	_hour	= dateTime._hour;
	_min	= dateTime._min;
	_second	= dateTime._second;
}

DateTime::DateTime(const time_t& t) : _date(), _hour(0), _min(0), _second(0.0)
{
	struct tm *tmTime;
	tmTime = localtime(&t);

	if (tmTime == NULL)
		return;

	_date	= aim_lib::Date(tmTime->tm_year + 1900, tmTime->tm_mon + 1, tmTime->tm_mday);
	_hour	= tmTime->tm_hour;
	_min	= tmTime->tm_min;
	_second	= tmTime->tm_sec;

}

DateTime::DateTime(const std::string& dicomDateTime) : _date(), _hour(0), _min(0), _second(0.0)
{
	OFDateTime ofDateTime = AIMUtil::DateTimeConvert(dicomDateTime);
	if (ofDateTime.isValid())
	{
		_date	= aim_lib::Date(ofDateTime.getDate().getYear(), ofDateTime.getDate().getMonth(), ofDateTime.getDate().getDay());
		_hour	= ofDateTime.getTime().getHour();
		_min	= ofDateTime.getTime().getMinute();
		_second	= ofDateTime.getTime().getSecond();
	}
}

DateTime::~DateTime(void)
{
}

bool DateTime::operator == (const DateTime& dateTimeIn) const
{
	return _date == dateTimeIn._date && _hour == dateTimeIn._hour && _min == dateTimeIn._min && _second == dateTimeIn._second;
}

bool DateTime::operator != (const DateTime& dateTimeIn) const
{
	return !((*this) == dateTimeIn);
}

int DateTime::GetYear() const
{
	return _date.GetYear();
}

int DateTime::GetMonth() const
{
	return _date.GetMonth();
}

int DateTime::GetDay() const
{
	return _date.GetDay();
}

const Date& DateTime::GetDate() const
{
	return _date;
}

int DateTime::GetHour() const
{
	return _hour;
}

int DateTime::GetMinute() const
{
	return _min;
}

double DateTime::GetSecond() const
{
	return _second;
}

void DateTime::SetYear(int year)
{
	_date.SetYear(year);
}

void DateTime::SetMonth(int month)
{
	_date.SetMonth(month);
}

void DateTime::SetDay(int day)
{
	_date.SetDay(day);
}

void DateTime::SetHour(int hour)
{
	_hour = hour;
}

void DateTime::SetMinute(int minute)
{
	_min = minute;
}

void DateTime::SetSecond(double second)
{
	_second = second;
}

bool DateTime::IsEmpty() const
{
	return (*this) == DateTime();
}

DateTime DateTime::Now()
{
	time_t ttNow;
	time(&ttNow);

	return DateTime(ttNow);
}

std::string DateTime::GetDicomFormatedDateTime() const
{
	OFString formattedDateTime;
	AIMUtil::DateTimeConvert(*this).getISOFormattedDateTime(formattedDateTime, true, false, false, false); // can be empty

	return formattedDateTime.c_str();
}


//
// *****************  Time ************************
//
Time::Time(int hour, int minute, double second) :
	_hour(hour), _min(minute), _second(second)
{
}

Time::Time(const Time& time)
{
	_hour	= time._hour;
	_min	= time._min;
	_second	= time._second;
}

Time::Time(const time_t& t) : _hour(0), _min(0), _second(0.0)
{
	struct tm *tmTime;
	tmTime = localtime(&t);

	if (tmTime == NULL)
		return;

	_hour	= tmTime->tm_hour;
	_min	= tmTime->tm_min;
	_second	= tmTime->tm_sec;

}

Time::Time(const std::string& dicomTime) : _hour(0), _min(0), _second(0.0)
{
	OFTime ofTime = AIMUtil::TimeConvert(dicomTime);
	if (ofTime.isValid())
	{
		_hour	= ofTime.getHour();
		_min	= ofTime.getMinute();
		_second	= ofTime.getSecond();
	}
}

Time::~Time(void)
{
}

bool Time::operator == (const Time& timeIn) const
{
	return _hour == timeIn._hour && _min == timeIn._min && _second == timeIn._second;
}

bool Time::operator != (const Time& timeIn) const
{
	return !((*this) == timeIn);
}

int Time::GetHour() const
{
	return _hour;
}

int Time::GetMinute() const
{
	return _min;
}

double Time::GetSecond() const
{
	return _second;
}

void Time::SetHour(int hour)
{
	_hour = hour;
}

void Time::SetMinute(int minute)
{
	_min = minute;
}

void Time::SetSecond(double second)
{
	_second = second;
}

bool Time::IsEmpty() const
{
	return (*this) == Time();
}

Time Time::Now()
{
	time_t ttNow;
	time(&ttNow);

	return Time(ttNow);
}

std::string Time::GetDicomFormatedTime() const
{
	OFString formattedTime;
	AIMUtil::TimeConvert(*this).getISOFormattedTime(formattedTime, true, false, false, false); // can be empty

	return formattedTime.c_str();
}
