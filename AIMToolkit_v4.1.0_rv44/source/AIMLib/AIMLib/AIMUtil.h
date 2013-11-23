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

#ifndef _AIMLib_AIMUtil_Class
#define _AIMLib_AIMUtil_Class

#include <string>
#include <ctime>
#include <map>

// DCMTK includes
#include "dcmtk/dcmsr/dsrdoc.h"

// Altova includes
#include "../Altova/Altova.h"
#include "../Altova/AltovaException.h"
#include "../Altova/xs-datetime.h"

// AIM includes

namespace aim_lib
{
	class AIMUtil
	{
	public:
		static OFDateTime DateTimeConvert(const std::string& dicomDateTime);
		static OFDateTime DateTimeConvert(const aim_lib::DateTime& dateTime);
		static DateTime DateTimeConvert(const OFDateTime& ofDateTimeIn);

		static DateTime DateTimeConvert(const altova::DateTime& altovaDateTime);
		static altova::DateTime DateTimeToAltovaDateTime(const DateTime& timeIn);

		static altova::DateTime DateToAltovaDateTime(const Date& timeIn);

		static aim_lib::Date DateConvert(const OFDate& ofDateIn);
		static aim_lib::Date DateConvert(const altova::DateTime& ofDateIn);
		static OFDate DateConvert(const aim_lib::Date& dateIn);
		static OFDate DateConvert(const std::string& dicomDateIn);

		static aim_lib::Time TimeConvert(const OFTime& ofTimeIn);
		static OFTime TimeConvert(const aim_lib::Time& timeIn);
		static OFTime TimeConvert(const std::string& dicomTime);

		static std::string IntToString(int numIn);
		static int StringToInt(const std::string& strIn);
		static const std::string DoubleToString(double numIn);
		static double StringToDouble(const std::string& strIn);
		static const std::string LongToString(long numIn);
		static bool IsNumeric(const std::string& strIn);

		static bool isLeapYear(int year);

		// uses C's stricmp()
		static int compareNoCase(const std::string& str1, const std::string& str2);
	protected:

	};
}
#endif // _AIMLib_AIMUtil_Class
