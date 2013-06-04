/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
