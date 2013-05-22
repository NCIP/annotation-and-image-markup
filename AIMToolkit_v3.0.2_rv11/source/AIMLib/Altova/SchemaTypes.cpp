/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "StdAfx.h"
#include "Altova.h"
#include "AltovaException.h"
#include "SchemaTypes.h"
#include "xs-types.h"

#include <math.h>



#include <algorithm>
#include <limits>

#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#include "exception.h"

#undef min
#undef max

template < typename T>
static tstring altovaitoa( T value, int base)
{
	tstring buf;
	buf.reserve( 36 ); // Pre-allocate enough space.

	// check that the base is valid
	if (base < 2 || base > 16) return buf;

	T quotient = value;
	// Translating number to string with base:
	do {
		buf += "0123456789abcdef"[ abs( static_cast<int>(quotient % base ) ) ];
		quotient /= base;
	} while ( quotient );

	// Append the negative sign for base 10
	if ( value < 0 && base == 10) buf += '-';

	std::reverse( buf.begin(), buf.end() );

	return buf;
}

#if !defined( __GNUC__ )
#if _MSC_VER <= 1200

// VC6 does not properly define numeric_limits for __int64 and unsigned __int64, so we do it here
namespace std
{
class numeric_limits<__int64> : public _Num_int_base
{
public:
	typedef __int64 _Ty;
	static _Ty (__cdecl min)() _THROW0()
	{return (_I64_MIN); }
	static _Ty (__cdecl max)() _THROW0()
	{return (_I64_MAX); }
	static _Ty __cdecl epsilon() _THROW0()
	{return (0); }
	static _Ty __cdecl round_error() _THROW0()
	{return (0); }
	static _Ty __cdecl denorm_min() _THROW0()
	{return (0); }
	static _Ty __cdecl infinity() _THROW0()
	{return (0); }
	static _Ty __cdecl quiet_NaN() _THROW0()
	{return (0); }
	static _Ty __cdecl signaling_NaN() _THROW0()
	{return (0); }
	_STCONS(bool, is_signed, true);
	_STCONS(int, digits, CHAR_BIT * sizeof (__int64) - 1);
	_STCONS(int, digits10, (CHAR_BIT * sizeof (__int64) - 1)
		* 301L / 1000);
};

class numeric_limits<unsigned __int64> : public _Num_int_base
{
public:
	typedef unsigned __int64 _Ty;
	static _Ty (__cdecl min)() _THROW0()
	{return 0; }
	static _Ty (__cdecl max)() _THROW0()
	{return (_UI64_MAX); }
	static _Ty __cdecl epsilon() _THROW0()
	{return (0); }
	static _Ty __cdecl round_error() _THROW0()
	{return (0); }
	static _Ty __cdecl denorm_min() _THROW0()
	{return (0); }
	static _Ty __cdecl infinity() _THROW0()
	{return (0); }
	static _Ty __cdecl quiet_NaN() _THROW0()
	{return (0); }
	static _Ty __cdecl signaling_NaN() _THROW0()
	{return (0); }
	_STCONS(bool, is_signed, true);
	_STCONS(int, digits, CHAR_BIT * sizeof (unsigned __int64) - 1);
	_STCONS(int, digits10, (CHAR_BIT * sizeof (unsigned __int64) - 1)
		* 301L / 1000);
};
}

#endif
#endif //GNUC


#pragma warning(disable:4996)	// VC2005 deprecation 

namespace
{
	static string_type& normalize(string_type& str)
	{
		std::replace(str.begin(), str.end(), (char_type)_T('\n'), _T(' '));
		std::replace(str.begin(), str.end(), (char_type)_T('\r'), _T(' '));
		std::replace(str.begin(), str.end(), (char_type)_T('\t'), _T(' '));

		// trim
		string_type::size_type i = str.find_last_not_of(_T(' '));
		if (i != tstring::npos)
		{
			str.erase(i + 1);
			i = str.find_first_not_of(' ');
			if(i != string_type::npos) str.erase(0, i);
		}
		else
			str.erase(str.begin(), str.end());

		// collapse
		for (i = 1; i<str.size();)
		{
			if (str[i] == _T(' ') && str[i-1] == _T(' '))
				str.erase(i, 1);
			else
				i++;
		}

		return str;
	}
}


namespace altova
{
	// number parsing helpers
	inline bool IsSchemaSign(char_type c)
	{
		return c == '+' || c == '-';
	}

	inline bool IsSchemaDigit(char_type c)
	{
		return c >= '0' && c <= '9';
	}

	inline bool IsSchemaRadix(char_type c)
	{
		return c == '.';
	}

	inline bool IsSchemaExponent(char_type c)
	{
		return c == 'e' || c == 'E';
	}

	inline void Append(char_type*& buffer, char_type c)
	{
		*buffer++ = c;
	}
	
	// prepares number literals for use with strtod
	// return buffer contains at most one character more 
	// return value indicates number type (1 = int, 2 = decimal, 3 = float)
	// adheres to the definition given XML Schema 1.1 Part 2, except that
	// it doesn't treat NaN and INF here.
	static unsigned PrepareNumber(char_type* buffer, const char_type* in)
	{
		enum State
		{
			Start,
			AfterSign,
			MantissaBeforePoint,
			AfterPoint,
			AfterPointNeedNoDigit,
			AfterPointNeedNoDigit1,
			AfterExponentE,
			AfterExponentSign,
			AfterExponentNeedNoDigit,

			StateCount,
			Invalid = StateCount,
		} state = Start;

		enum Action
		{
			AppendChar,
			AppendZeroChar,
			Abort,
		};

		enum Class
		{
			Sign,
			Digit,
			Radix,
			Exponent,
			NoClass,
			ClassCount,
		} cls;

		static const Action actions[StateCount][ClassCount] = 
		{
			{ AppendChar, AppendChar, AppendZeroChar, Abort, Abort  },	// Start
			{ Abort,      AppendChar, AppendZeroChar, Abort, Abort  },	// AfterSign
			{ Abort,      AppendChar, AppendChar, AppendChar, Abort  },	// MantissaBeforePoint
			{ Abort,      AppendChar, Abort,      Abort, Abort  },		// AfterPoint
			{ Abort,      AppendChar, Abort,      AppendChar, Abort  },	// AfterPointNeedNoDigit
			{ Abort,      AppendChar, Abort,      AppendZeroChar, Abort  }, // AfterPointNeedNoDigit1
			{ AppendChar, AppendChar, Abort,      Abort, Abort  },	// AfterExponentE
			{ Abort,      AppendChar, Abort,      Abort, Abort  },  // AfterExponentSign
			{ Abort,      AppendChar, Abort,      Abort, Abort  },  // AfterExponentNeedNoDigit		
		};

		static const State follow[StateCount][ClassCount] = 
		{
			{ AfterSign, MantissaBeforePoint, AfterPoint, Invalid, Invalid }, // Start
			{ Invalid, MantissaBeforePoint, AfterPoint, Invalid, Invalid },	// AfterSign
			{ Invalid, MantissaBeforePoint, AfterPointNeedNoDigit1, AfterExponentE, Invalid }, // MantissaBeforePoint
			{ Invalid, AfterPointNeedNoDigit, Invalid, Invalid, Invalid }, // AfterPoint
			{ Invalid, AfterPointNeedNoDigit, Invalid, AfterExponentE, Invalid }, // AfterPointNeedNoDigit
			{ Invalid, AfterPointNeedNoDigit, Invalid, AfterExponentE, Invalid }, // AfterPointNeedNoDigit1
			{ AfterExponentSign, AfterExponentNeedNoDigit, Invalid, Invalid, Invalid }, // AfterExponentE
			{ Invalid, AfterExponentNeedNoDigit, Invalid, Invalid, Invalid }, // AfterExponentSign
			{ Invalid, AfterExponentNeedNoDigit, Invalid, Invalid, Invalid }, // AfterExponentNeedNoDigit
		};

		for (const char_type* p = in; *p; ++p)
		{
			if (IsSchemaDigit(*p))
				cls = Digit;
			else if (IsSchemaSign(*p))
				cls = Sign;
			else if (IsSchemaRadix(*p))
				cls = Radix;
			else if (IsSchemaExponent(*p))
				cls = Exponent;
			else
				cls = NoClass;

			switch (actions[state][cls])
			{
			case AppendChar:
				Append(buffer, *p);
				break;
			case AppendZeroChar:
				Append(buffer, '0');
				Append(buffer, *p);
				break;
			case Abort:
				*buffer = 0;
				return 0;
			}
			state = follow[state][cls];
		}

		switch (state)
		{
		case Start:
		case AfterSign:
		case AfterPoint:
		case AfterExponentE:
		case AfterExponentSign:
			*buffer = 0;
			return 0;		

		case AfterPointNeedNoDigit1:
			Append(buffer, '0');
			break;	
		}

		*buffer = 0;

		switch (state)
		{
		case MantissaBeforePoint:
			return 1;	// integer
		case AfterPointNeedNoDigit:
		case AfterPointNeedNoDigit1:
			return 2;	// decimal
		case AfterExponentNeedNoDigit:
			return 3;	// float
		}
		return 0;
	}


	static bool IsSchemaWhitespace(char_type v)
	{
		return (v == '\x9' || v == '\x20' || v == '\xa' || v == '\xd');
	}

	static string_type TrimWhitespace(const string_type& s)
	{
		string_type::const_iterator it = s.begin();
		while (it != s.end() && IsSchemaWhitespace(*it))
			++it;

		if (it == s.end())
			return string_type();

		string_type::const_iterator it2 = s.end();
		while (--it2 != it && IsSchemaWhitespace(*it2))
			;
		return string_type(it, ++it2);
	}



	static string_type::const_iterator SkipWhitespace(string_type::const_iterator begin, const string_type::const_iterator& end)
	{
		while (begin != end)
		{
			string_type::value_type v = *begin;
			if (!IsSchemaWhitespace(v))
				break;
			++begin;
		}
		return begin;
	}


	static bool IsDigit(const string_type::const_iterator& x)
	{
		string_type::value_type v = *x;
		return v >= '\x30' && v <= '\x39';
	}

	static int GetNumericValue(const string_type::const_iterator& x)
	{
		string_type::value_type v = *x;
		return v - '\x30';
	}

	inline int GetNumericValue(char_type c)
	{
		return c - '\x30';
	}

	static string_type::const_iterator IgnoreFraction(string_type::const_iterator begin, const string_type::const_iterator& end)
	{
		if (begin == end)
			return begin;
		if (*begin != '.')
			return begin;
		++begin;
		while (begin != end && IsDigit(begin))
			++begin;
		return begin;
	}

	static string_type::const_iterator IgnoreExponent(string_type::const_iterator begin, const string_type::const_iterator& end)
	{
		if (begin == end)
			return begin;
		if (*begin != 'e' && *begin != 'E')
			return begin;
		++begin;
		if (begin != end && (*begin == '+' || *begin == '-'))
			++begin;
		while (begin != end && IsDigit(begin))
			++begin;
		return begin;
	}

	static bool IsEqualString(string_type::const_iterator begin, const string_type::const_iterator& end, const char_type* str)
	{
		while (begin != end && *str)
		{
			if (*begin != *str)
				return false;
			++begin;
			++str;
		}
		return SkipWhitespace(begin, end) == end;
	}

	struct TValueComponents
	{
		unsigned __int64 value;
		bool positive;
		string_type::const_iterator end;
		bool overflow;
	};

	static TValueComponents ParseIntCore(string_type::const_iterator first, const string_type::const_iterator& end)
	{
		TValueComponents result = { 0, true, first, false };
		if (first == end) 
			return result;

		if (*first == '+') { ++first; }
		else if (*first == '-') { result.positive = false; ++first; }
		
		while (first != end && IsDigit(first))
		{						
			if (result.value >= std::numeric_limits<unsigned __int64>::max() / 10 && GetNumericValue(first) > std::numeric_limits<unsigned __int64>::max() % 10)
				result.overflow = true;

			result.value = result.value * 10 + GetNumericValue(first);
			++first;
		}

		result.end = IgnoreFraction(first, end);
		return result;
	}


	struct ParseResult
	{
		unsigned __int64 value;
		bool positive;
		bool overflow;
	};

	// assumes buffer is a well-formed integer already.
	ParseResult ParseInteger(const char_type* p)
	{
		ParseResult r = { 0, true, false };

		// sign
		if (*p == '-') {
			r.positive = false;
			++p;
		} else if (*p == '+') {
			++p;
		}

		while (*p) {
			if (r.value >= std::numeric_limits<unsigned __int64>::max() / 10 && GetNumericValue(*p) > std::numeric_limits<unsigned __int64>::max() % 10)
			{
				r.overflow = true;
			}
			r.value = r.value * 10 + GetNumericValue(*p);
			++p;
		}		
		if (!r.overflow && r.value == 0)	// treat zero as positive
			r.positive = true;
		return r;
	}


	bool CoreTypes::IsNumber(const string_type& s)
	{
		string_type str = TrimWhitespace(s);
		if (str == _T("NaN") || str == _T("INF") || str == _T("-INF"))
			return true;
		// alloc temporary buffer
		char_type* buffer = (char_type*) alloca((str.size() + 2) * sizeof(char_type));
		return PrepareNumber(buffer, str.c_str()) != 0;
	}

	int CoreTypes::CastToInt(int i) 
	{ 
		return i; 
	}

	int CoreTypes::CastToInt(unsigned int i) 
	{ 
		if (i > (unsigned) std::numeric_limits<int>::max()) 
			throw altova::OutOfRangeException(_T("unsignedInt"), _T("int"), CastToString(i));
		return (int)i; 
	}

	int CoreTypes::CastToInt(double d) 
	{ 
		if (d < std::numeric_limits<int>::min() || d > std::numeric_limits<int>::max())
			throw altova::OutOfRangeException(_T("double"), _T("int"), CastToString(d));
		return (int)d; 
	}
	


	int CoreTypes::CastToInt(const string_type& s) 
	{ 		
		string_type str = TrimWhitespace(s);
		if (str == _T("NaN") || str == _T("INF") || str == _T("-INF"))
			throw altova::OutOfRangeException(_T("string"), _T("int"), s);

		// alloc temporary buffer
		char_type* buffer = (char_type*) alloca((str.size() + 2) * sizeof(char_type));
		switch (PrepareNumber(buffer, str.c_str()))
		{
		case 1:
			{
				ParseResult r = ParseInteger(buffer);
				if (r.positive) 
				{
					if (r.overflow || r.value > (unsigned __int64) std::numeric_limits<int>::max() )
						throw altova::OutOfRangeException(_T("string"), _T("int"), s);
					return (int)r.value;
				}
				else
				{
					if (r.overflow || r.value > (unsigned __int64) -(__int64) std::numeric_limits<int>::min() )
						throw altova::OutOfRangeException(_T("string"), _T("int"), s);
					return -(int)r.value;
				}
			}
		case 2:
		case 3:
			return CastToInt(_tcstod(buffer, 0));
		default:
			throw altova::StringParseException(_T("int"), s);
		}
	}


	int CoreTypes::CastToInt(__int64 i) 
	{ 
		if (i < std::numeric_limits<int>::min() || i > std::numeric_limits<int>::max())
			throw altova::OutOfRangeException(_T("long"), _T("int"), CastToString(i));
		return (int)i; 
	}


	int CoreTypes::CastToInt(unsigned __int64 i) 
	{ 
		if (i > std::numeric_limits<int>::max())
			throw altova::OutOfRangeException(_T("unsignedLong"), _T("int"), CastToString(i));
		return (int)i; 
	}


	unsigned CoreTypes::CastToUInt(int i) 
	{ 
		if (i < 0)
			throw altova::OutOfRangeException(_T("int"), _T("unsignedInt"), CastToString(i));
		return (unsigned)i; 
	}


	unsigned CoreTypes::CastToUInt(unsigned int i) 
	{ 
		return i; 
	}


	unsigned CoreTypes::CastToUInt(double d) 
	{ 
		if (d < 0 || d > std::numeric_limits<unsigned>::max())
			throw altova::OutOfRangeException(_T("double"), _T("unsignedInt"), CastToString(d));
		return (unsigned)d; 
	}


	unsigned CoreTypes::CastToUInt(const string_type& s) 
	{ 
		string_type str = TrimWhitespace(s);
		if (str == _T("NaN") || str == _T("INF") || str == _T("-INF"))
			throw altova::OutOfRangeException(_T("string"), _T("unsignedInt"), s);

		// alloc temporary buffer
		char_type* buffer = (char_type*) alloca((str.size() + 2) * sizeof(char_type));
		switch (PrepareNumber(buffer, str.c_str()))
		{
		case 1:
			{
				ParseResult r = ParseInteger(buffer);
				if (r.positive) 
				{
					if (r.overflow || r.value > (unsigned __int64) std::numeric_limits<unsigned int>::max() )
						throw altova::OutOfRangeException(_T("string"), _T("unsignedInt"), s);
					return (unsigned)r.value;
				}
				else
					throw altova::OutOfRangeException(_T("string"), _T("unsignedInt"), s);
			}
		case 2:
		case 3:
			return CastToUInt(_tcstod(buffer, 0));
		default:
			throw altova::StringParseException(_T("unsignedInt"), s);
		}
	}

	
	unsigned CoreTypes::CastToUInt(__int64 i) 
	{ 
		if (i < 0 || i > std::numeric_limits<unsigned>::max())
			throw altova::OutOfRangeException(_T("long"), _T("unsignedInt"), CastToString(i));
		return (unsigned)i; 	
	}


	unsigned CoreTypes::CastToUInt(unsigned __int64 i) 
	{ 
		if (i > std::numeric_limits<unsigned>::max())
			throw altova::OutOfRangeException(_T("unsignedLong"), _T("unsignedInt"), CastToString(i));
		return (unsigned)i; 
	}


	__int64 CoreTypes::CastToInt64(int i) 
	{ 
		return i; 
	}


	__int64 CoreTypes::CastToInt64(unsigned int i) 
	{ 
		return i; 
	}


	__int64 CoreTypes::CastToInt64(double d) 
	{ 
		if (d < std::numeric_limits<__int64>::min() || d > std::numeric_limits<__int64>::max())
			throw altova::OutOfRangeException(_T("double"), _T("long"), CastToString(d));
		
		return (__int64)d; 
	}


	__int64 CoreTypes::CastToInt64(const string_type& s) 
	{
		string_type str = TrimWhitespace(s);
		if (str == _T("NaN") || str == _T("INF") || str == _T("-INF"))
			throw altova::OutOfRangeException(_T("string"), _T("long"), s);

		// alloc temporary buffer
		char_type* buffer = (char_type*) alloca((str.size() + 2) * sizeof(char_type));
		switch (PrepareNumber(buffer, str.c_str()))
		{
		case 1:
			{
				ParseResult r = ParseInteger(buffer);
				if (r.positive) 
				{
					if (r.overflow || r.value > (unsigned __int64)std::numeric_limits<__int64>::max() )
						throw altova::OutOfRangeException(_T("string"), _T("long"), s);
					return (__int64)r.value;
				}
				else
				{
					if (r.overflow || r.value > (unsigned __int64) -std::numeric_limits<__int64>::min() )
						throw altova::OutOfRangeException(_T("string"), _T("long"), s);
					return -(__int64)r.value;
				}
			}
		case 2:
		case 3:
			return CastToInt64(_tcstod(buffer, 0));
		default:
			throw altova::StringParseException(_T("int"), s);
		}
	}


	__int64 CoreTypes::CastToInt64(__int64 i) 
	{ 
		return i; 
	}


	__int64 CoreTypes::CastToInt64(unsigned __int64 i) 
	{ 
		if (i > (unsigned __int64) std::numeric_limits<__int64>::max())
			throw altova::OutOfRangeException(_T("unsignedLong"), _T("long"), CastToString(i));
		return (__int64)i; 
	}

	unsigned __int64 CoreTypes::CastToUInt64(int i) 
	{ 
		return (unsigned __int64)i; 
	}


	unsigned __int64 CoreTypes::CastToUInt64(unsigned int i) 
	{ 
		return i; 
	}


	unsigned __int64 CoreTypes::CastToUInt64(double d) 
	{ 
		if (d < 0 || d > CastToDouble(std::numeric_limits<unsigned __int64>::max())) 
			throw altova::OutOfRangeException(_T("double"), _T("unsignedLong"), CastToString(d));
		return (unsigned __int64)d; 	
	}


	unsigned __int64 CoreTypes::CastToUInt64(const string_type& s) 
	{ 
		string_type str = TrimWhitespace(s);
		if (str == _T("NaN") || str == _T("INF") || str == _T("-INF"))
			throw altova::OutOfRangeException(_T("string"), _T("unsignedLong"), s);

		// alloc temporary buffer
		char_type* buffer = (char_type*) alloca((str.size() + 2) * sizeof(char_type));
		switch (PrepareNumber(buffer, str.c_str()))
		{
		case 1:
			{
				ParseResult r = ParseInteger(buffer);
				if (r.positive) 
				{
					if (r.overflow)
						throw altova::OutOfRangeException(_T("string"), _T("unsignedLong"), s);
					return r.value;
				}
				else 
					throw altova::OutOfRangeException(_T("string"), _T("unsignedLong"), s);
			}
		case 2:
		case 3:
			return CastToUInt64(_tcstod(buffer, 0));
		default:
			throw altova::StringParseException(_T("int"), s);
		}
	}


	unsigned __int64 CoreTypes::CastToUInt64(__int64 i) 
	{ 
		if (i < 0)
			throw altova::OutOfRangeException(_T("long"), _T("unsignedLong"), CastToString(i));
		return (unsigned __int64)i; 
	}


	unsigned __int64 CoreTypes::CastToUInt64(unsigned __int64 i) 
	{
		return i; 
	}


	double CoreTypes::CastToDouble(int i) 
	{ 
		return i; 
	}
	
	
	double CoreTypes::CastToDouble(unsigned i) 
	{ 
		return i; 
	}


	double CoreTypes::CastToDouble(__int64 i) 
	{ 
		return (double)i; 
	}

	double CoreTypes::CastToDouble(unsigned __int64 i) 
	{ 
#if defined(_MSC_VER) && _MSC_VER <= 1200
		double d = (unsigned)i;
		d = d + ((unsigned)(i >> 32)) * 4294967296.0;
		return d;
#else
		return (double)i; 
#endif
	}


	double CoreTypes::CastToDouble(double d) 
	{ 
		return d; 
	}


	double CoreTypes::CastToDouble(const string_type& s) 
	{
		string_type str = TrimWhitespace(s);
		if (str == _T("NaN"))
			return std::numeric_limits<double>::quiet_NaN();
		else if (str == _T("INF"))
			return std::numeric_limits<double>::infinity();
		else if (str == _T("-INF"))
			return -std::numeric_limits<double>::infinity();

		// alloc temporary buffer
		char_type* buffer = (char_type*) alloca((str.size() + 2) * sizeof(char_type));
		switch (PrepareNumber(buffer, str.c_str()))
		{
		case 1:
		case 2:
		case 3:
			return _tcstod(buffer, 0);
		default:
			throw altova::StringParseException(_T("int"), s);
		}
	}


	string_type CoreTypes::CastToString(double d) 
	{ 
		double origd = d;
		// according to IEEE this is valid:
		if (d != d)
			return _T("NaN");

		if (d <= -std::numeric_limits<double>::infinity())
			return _T("-INF");

		if (d >= std::numeric_limits<double>::infinity())
			return _T("INF");

		if (d == 0)	// exact zero
			return _T("0");

		string_type result;

		// Typically double is used for decimal, therefore no exponent shall be written.
		const int MinDigits = 14;	// emit at this many digits for double
		bool negative = false;
		if (d < 0)
		{
			negative = true;
			d = -d;
		}

		// scale number (inefficient variant)

		double exponent = log10(d);		
		int scale = (int)floor(exponent);
		scale -= MinDigits;

		static double factors[] = 
		{
			1e1,
			1e2,
			1e4,
			1e8,
			1e16,
			1e32,
			1e64,
			1e128,
			1e256,
		};

		if (scale > 0)
		{
			double factor = 10;
			for (unsigned u = 0; u != 9; ++u)
			{
				if (scale & (1 << u))
					d /= factors[u];//factor;
				//factor *= factor;
			}
		}
		else
		{
			double factor = 10;
			for (unsigned u = 0; u != 9; ++u)
			{
				if (-scale & (1 << u))
					d *= factors[u];
				factor *= factor;
			}
		}		

		scale += MinDigits;
		__int64 mantissa = (__int64) floor(d + 0.5);
		result = CastToString(mantissa);
		__int64 mantissaFloor = (__int64) floor(d);
		if ( CastToString(mantissaFloor).length() < result.length() )
			scale += 1;

		// now place comma in right position, that is scale places from the right.
		if (scale >= MinDigits)
		{
			result.append(scale - MinDigits + 1, _T('0'));
		}
		if (scale < 0)
		{
			std::reverse(result.begin(), result.end());
			result.append(-scale, _T('0'));
			std::reverse(result.begin(), result.end());
			scale = 0;
		}

		result.insert(scale + 1, 1, _T('.'));
		if (negative)
			result.insert((string_type::size_type)0, 1, _T('-'));

		while (true)
		{
			// now remove trailing zeros
			while (result.at(result.size()-1) == _T('0'))
				result.erase(result.size()-1, 1);

			if (result.at(result.size()-1) == _T('.'))
			{
				result.erase(result.size()-1, 1);
				break;	// can't remove any more digits
			}

			string_type temp = result.substr(0, result.size() - 1);


			if (CastToDouble(temp) != origd)
				break;
			result = temp;
		}

		return result;
	}

	string_type CoreTypes::CastToString(const altova::QName& qn)
	{
		return qn.ToString(); 
	}

	altova::QName CoreTypes::CastToQName(const string_type& s)
	{
		return altova::QName(s);
	}
	


	altova::QName CoreTypes::CastToQName(const altova::QName& qn)
	{
		return qn;
	}

	string_type CoreTypes::FormatBase64(const std::vector<unsigned char>& v)
	{
		string_type result;
		static char_type EncodingTable[] = _T("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");
		unsigned counter = 0;
		for (std::vector<unsigned char>::const_iterator it = v.begin(); it != v.end(); )
		{
			unsigned char b1 = *it++;
			result.append(1, EncodingTable[b1 >> 2]);
			if (it != v.end())
			{
				unsigned char b2 = *it++;
				result.append(1, EncodingTable[((b1 & 3) << 4) | (b2 >> 4)]);

				if (it != v.end())
				{
					unsigned char b3 = *it++;
					result.append(1, EncodingTable[((b2 & 15) << 2) | (b3 >> 6)]);
					result.append(1, EncodingTable[(b3 & 63)]);					
					counter = 0;
					if (counter == 76)
					{
						result.append(1, (char_type)0xa);
						counter = 0;
					}
				}
				else
				{
					result.append(1, EncodingTable[((b2 & 15) << 2)]);
					result.append(1, _T('='));
				}
			}
			else
			{
				result.append(1, EncodingTable[((b1 & 3) << 4)]);				
				result.append(1, _T('='));
				result.append(1, _T('='));
			}
		}
		return result;
	}

	string_type CoreTypes::CastToString(const std::vector<unsigned char>& v)
	{
		return FormatBase64(v);
	}

string_type CoreTypes::CastToString(int i) { return altovaitoa( i, 10);  }
string_type CoreTypes::CastToString(unsigned int i) { return altovaitoa( i, 10); }
string_type CoreTypes::CastToString(__int64 i) { return altovaitoa( i, 10); }
string_type CoreTypes::CastToString(unsigned __int64 i) { return altovaitoa( i, 10); }
string_type CoreTypes::CastToString(const string_type& s) { return s; }
string_type CoreTypes::CastToString(const char_type* s) { return string_type(s); }
string_type CoreTypes::CastToString(bool b) { return b ? _T("true") : _T("false"); }

bool CoreTypes::CastToBool(bool b) { return b; }
bool CoreTypes::CastToBool(int i) { return i != 0; }
bool CoreTypes::CastToBool(unsigned i) { return i != 0; }
bool CoreTypes::CastToBool(__int64 i) { return i != 0; }
bool CoreTypes::CastToBool(unsigned __int64 i) { return i != 0; }
bool CoreTypes::CastToBool(double d) { return d != 0; }
bool CoreTypes::CastToBool(const string_type& v) 
{ 
	string_type s = v;
	normalize(s);
	
	
	if (s == _T("true") || s == _T("1")) 
		return true; 
	if (s == _T("false") || s == _T("0")) 
		return false; 
	throw altova::StringParseException(_T("bool"), v); 
}
bool CoreTypes::CastToBool(const char_type* s) {return CastToBool(string_type(s));}


std::vector<unsigned char> CoreTypes::CastToBinary(const std::vector<unsigned char>& v) { return v; }

void CoreTypes::FormatNumber(string_type& target, unsigned value, unsigned minDigits)
{
	char_type temp[32];
	char_type* p = temp;
	while(value != 0)
	{
		*p++ = (value % 10) + '0';
		value /= 10;
	}
	while (p - temp < (int)minDigits)
		*p++ = '0';
	while (p != temp)
	{
		target.append(1, *(p - 1));
		--p;
	}
}

void CoreTypes::FormatTimezone(string_type& result, short value)
{
	if (value == 0)
		result.append(1, _T('Z'));
	else
	{
		if (value< 0)
		{
			result.append(1, _T('-'));
			value = -value;
		}
		else
		{
			result.append(1, _T('+'));
		}
		FormatNumber(result, value / 60, 2);
		result.append(1, _T(':'));
		FormatNumber(result, value % 60, 2);
	}
}

void CoreTypes::FormatFraction(string_type& result, unsigned value, unsigned precision)
{
	if (value != 0)
	{
		result.append(1, _T('.'));
		FormatNumber(result, value, precision);
		string_type::size_type s = result.size();
		while (result.at(s - 1) == '0')
			s -= 1;
		result.erase(s);
	}
}


string_type CoreTypes::CastToString(const altova::DateTime& dt, DateTimeFormat format)
{
	string_type result;

	int year, month, day;
	DateTime::GetDateFromTimeValue(dt.Value(), year, month, day);
	__int64 value = dt.Value();
	__int64 intraday = value % (86400 * altova::TicksPerSecond);
	if (intraday < 0) intraday += (86400 * altova::TicksPerSecond);
	unsigned fraction = (unsigned)(intraday % altova::TicksPerSecond);
	intraday /= altova::TicksPerSecond;
	unsigned second = (unsigned)(intraday % 60);
	intraday /= 60;
	unsigned minute = (unsigned)(intraday % 60);
	intraday /= 60;
	unsigned hour = (unsigned)intraday;

	// print date part
	switch (format)
	{
	case DateTimeFormat_W3_dateTime:
	case DateTimeFormat_W3_date:
	case DateTimeFormat_S_DateTime:		
		if (year < 0)
		{
			result.append(1, _T('-'));
			year = -year;
		}
		FormatNumber(result, year, 4);
		result.append(1, _T('-'));
		FormatNumber(result, month, 2);
		result.append(1, _T('-'));
		FormatNumber(result, day, 2);
		break;
	}

	// print a separator.
	switch (format)
	{
	case DateTimeFormat_W3_dateTime:
		result.append(1, _T('T'));
		break;
	case DateTimeFormat_S_DateTime:
		result.append(1, _T(' '));
		break;
	}

	// print the remainder
	switch (format)
	{
	case DateTimeFormat_W3_dateTime:
	case DateTimeFormat_S_DateTime:
	case DateTimeFormat_W3_time:
		FormatNumber(result, hour, 2);
		result.append(1, _T(':'));
		FormatNumber(result, minute, 2);
		result.append(1, _T(':'));
		FormatNumber(result, second, 2);
		FormatFraction(result, fraction, 7);
		break;

	case DateTimeFormat_W3_gYear:
		if (year < 0)
		{
			result.append(1, _T('-'));
			year = -year;
		}
		FormatNumber(result, year, 4);
		break;

	case DateTimeFormat_W3_gYearMonth:
		if (year < 0)
		{
			result.append(1, _T('-'));
			year = -year;
		}
		FormatNumber(result, year, 4);
		result.append(1, _T('-'));
		FormatNumber(result, month, 2);
		break;

	case DateTimeFormat_W3_gMonth:
		result.append(2, _T('-'));
		FormatNumber(result, month, 2);
		break;

	case DateTimeFormat_W3_gMonthDay:
		result.append(2, _T('-'));
		FormatNumber(result, month, 2);
		result.append(1, _T('-'));
		FormatNumber(result, day, 2);
		break;

	case DateTimeFormat_W3_gDay:
		result.append(3, _T('-'));
		FormatNumber(result, day, 2);
		break;

	case DateTimeFormat_S_Seconds:
		if (value < 0)
		{
			result.append(1, _T('-'));
			value = -value;
		}
		FormatNumber(result, unsigned(value / altova::TicksPerSecond), 1);
		FormatFraction(result, unsigned(value % altova::TicksPerSecond), 7);
		break;

	case DateTimeFormat_S_Days:
		if (value < 0)
		{
			result.append(1, _T('-'));
			value = -value;
		}
		FormatNumber(result, unsigned(value / (86400 * altova::TicksPerSecond)), 1);
		FormatFraction(result, unsigned(value % (86400 * altova::TicksPerSecond) / 86400), 7);
		break;
	}

	if (dt.HasTimezone())
		FormatTimezone(result, dt.Timezone());

	return result;
}


string_type CoreTypes::CastToString(altova::DateTime dt)
{
	return CastToString(dt, DateTimeFormat_W3_dateTime);
}


string_type CoreTypes::CastToString(altova::Duration dur)
{
	string_type result;
	if (dur.IsNegative() && dur.IsPositive())
		throw altova::ValueNotRepresentableException(_T("duration"), 
			_T("Sign of year month part differs from sign of day time part."));
	
	if (dur.IsNegative())
	{
		result += _T("-");
		dur = -dur;
	}

	result += _T("P");
	if (dur.Years())
		result += CastToString(dur.Years()) + _T("Y");
	if (dur.Months())
		result += CastToString(dur.Months()) + _T("M");
	if (dur.Days())
		result += CastToString(dur.Days()) + _T("D");

	if (dur.Hours() || dur.Minutes() || dur.Seconds())
		result += _T("T");
	if (dur.Hours())
		result += CastToString(dur.Hours()) + _T("H");
	if (dur.Minutes())
		result += CastToString(dur.Minutes()) + _T("M");
	if (dur.Seconds())
		result += CastToString(dur.Seconds()) + _T("S");

	if (result[result.size()-1] == 'P')
		result += _T("T0S");

	return result;
}

string_type CoreTypes::CastToString(altova::DayTimeDuration dur)
{
	string_type result;
	if (dur.IsNegative())
	{
		result += _T("-");
		dur = -dur;
	}

	result += _T("P");
	if (dur.Days())
		result += CastToString(dur.Days()) + _T("D");

	if (dur.Hours() || dur.Minutes() || dur.Seconds())
		result += _T("T");
	if (dur.Hours())
		result += CastToString(dur.Hours()) + _T("H");
	if (dur.Minutes())
		result += CastToString(dur.Minutes()) + _T("M");
	if (dur.Seconds())
		result += CastToString(dur.Seconds()) + _T("S");

	if (result[result.size()-1] == 'P')
		result += _T("T0S");

	return result;
}

string_type CoreTypes::CastToString(altova::YearMonthDuration dur)
{
	string_type result;

	if (dur.IsNegative())
	{
		result += _T("-");
		dur = -dur;
	}

	result += _T("P");
	if (dur.Years())
		result += CastToString(dur.Years()) + _T("Y");
	if (dur.Months())
		result += CastToString(dur.Months()) + _T("M");

	if (result[result.size()-1] == 'P')
		result += _T("0M");
	return result;
}


// isdigit depends on locale, which we do not want

inline unsigned GetSchemaDigitValue(char_type c)
{
	return c - '0';
}

struct DateTimeParseState
{
	string_type::size_type pos;
	int year;
	unsigned month, day, hour, minute, second, fraction;
	int timezone;
	unsigned value;
};


void SkipWhitespace(const string_type& input, DateTimeParseState& state)
{
	while (state.pos != input.size()) 
	{ 
		char_type c = input.at(state.pos);
		if (c != (char_type)0x20 && c != (char_type)0x09 && 
			c != (char_type)0x0a && c != (char_type)0x0d)
			break;
		state.pos += 1;
	}
}

bool Read2DigitNumber(const string_type& input, DateTimeParseState& state)
{
	if (state.pos == input.size())
		return false;
	char_type c = input.at(state.pos);
	if (!IsSchemaDigit(c))
		return false;
	state.value = GetSchemaDigitValue(c);

	if (++state.pos == input.size())
		return false;
	c = input.at(state.pos);
	if (!IsSchemaDigit(c))
		return false;
	state.value = state.value * 10 + GetSchemaDigitValue(c);
	++state.pos;
	return true;
}

bool ReadNumber(const string_type& input, DateTimeParseState& state)
{
	if (state.pos == input.size())
		return false;
	char_type c = input.at(state.pos);
	if (!IsSchemaDigit(c))
		return false;
	state.value = GetSchemaDigitValue(c);
	++state.pos;
	while (state.pos != input.size())
	{
		c = input.at(state.pos);
		if (!IsSchemaDigit(c))
			break;
		state.value = state.value * 10 + GetSchemaDigitValue(c);
		++state.pos;
	}
	return true;
}

bool ReadFraction(const string_type& input, DateTimeParseState& state)
{
	state.fraction = 0;
	if (state.pos == input.size())
		return true;

	char_type c = input.at(state.pos);
	if (c != '.')
		return true;	// no fraction, but it is optional -> ok
	if (++state.pos == input.size())
		return false;	// at least one digit must follow
	if (!IsSchemaDigit(input.at(state.pos)))
		return false;

	// now examine 7 digits (governed by TicksPerSecond actually)	
	for (unsigned u = 0; u != 7; ++u)
	{
		state.fraction = state.fraction * 10;
		if (state.pos != input.size())
		{
			char_type c = input.at(state.pos);
			if (IsSchemaDigit(c))
			{
				state.fraction += GetSchemaDigitValue(c);
				++state.pos;
			}
		}
	}

	// ignore any further digits. we do not round up if there is a digit >= 5 following.
	while (state.pos != input.size())
	{
		if (!IsSchemaDigit(input.at(state.pos)))
			break;
		++state.pos;
	}

	return true;
}


bool ReadTime(const string_type& input, DateTimeParseState& state)
{
	if (!Read2DigitNumber(input, state))
		return false;
	if (state.value > 24)
		return false;
	state.hour = state.value;
	if (state.pos == input.size())
		return false;
	if (input.at(state.pos) != ':')
		return false;
	++state.pos;
	if (!Read2DigitNumber(input, state))
		return false;
	if (state.value >= 60 || (state.hour == 24 && state.value != 0))		
		return false;
	state.minute = state.value;
	if (state.pos == input.size())
		return false;
	if (input.at(state.pos) != ':')
		return false;
	++state.pos;
	if (!Read2DigitNumber(input, state))
		return false;
	if (state.value >= 60 || (state.hour == 24 && state.value != 0))		
		return false;
	state.second = state.value;
	if (!ReadFraction(input, state))
		return false;
	return true;
}

bool ReadYear(const string_type& input, DateTimeParseState& state)
{
	// read 4 digits
	state.year = 0;
	for (unsigned u = 0; u != 4; ++u)
	{
		if (state.pos == input.size())
			return false;
		char_type c = input.at(state.pos);
		if (!IsSchemaDigit(c))
			return false;
		state.year = state.year * 10 + GetSchemaDigitValue(c);
		++state.pos;
	}

	if (state.year >= 1000)
	{
		// read more digits in this case (otherwise we leave the digits and the parser will fail)
		while (state.pos != input.size())
		{
			char_type c = input.at(state.pos);
			if (!IsSchemaDigit(c))
				break;
			state.year = state.year * 10 + GetSchemaDigitValue(c);
			++state.pos;
		}		
	}
	return true;
}


bool TryParseDateTime(const string_type& input, unsigned formatFlags, altova::DateTime& value)
{
	DateTimeParseState state;

	if ((formatFlags & CoreTypes::ParseDateTimeFlag_RequireYear) != 0)
		formatFlags |= CoreTypes::ParseDateTimeFlag_AllowYear;
	if ((formatFlags & CoreTypes::ParseDateTimeFlag_RequireMonth) != 0)
		formatFlags |= CoreTypes::ParseDateTimeFlag_AllowMonth;
	if ((formatFlags & CoreTypes::ParseDateTimeFlag_RequireDay) != 0)
		formatFlags |= CoreTypes::ParseDateTimeFlag_AllowDay;
	if ((formatFlags & CoreTypes::ParseDateTimeFlag_RequireTime) != 0)
		formatFlags |= CoreTypes::ParseDateTimeFlag_AllowTime;

	state.pos = 0;
	state.year = state.month = state.day = 1;
	state.hour = state.minute = state.second = state.fraction = 0;
	state.timezone = altova::DateTime::NO_TIMEZONE;

	SkipWhitespace(input, state);
	if (state.pos == input.size())
		return false;	// not a valid dateTime

	// if string is a time string, the 3rd character is a ':', otherwise it is not. 
	if (state.pos + 3 > input.size())
		return false;	// no known format of this kind

	if (input.at(state.pos + 2) == ':')
	{
		// time only 
		if ((formatFlags & CoreTypes::ParseDateTimeFlag_AllowTime) == 0 ||
			(formatFlags & CoreTypes::ParseDateTimeFlag_RequireDate) != 0)
			return false;

		state.year = state.month = state.day = 1;
		if (!ReadTime(input, state))
			return false;
	}
	else
	{
		// date possibly followed by time
		if ((formatFlags & CoreTypes::ParseDateTimeFlag_AllowDate) == 0)
			return false;

		// this must be present (ensured above)
		bool positive = true;
		if (input.at(state.pos) == '-')
		{
			positive = false;
			++state.pos;
		}

		// next char is either '-' for no year at all, or a digit
		if (state.pos == input.size())
			return false;
		if (input.at(state.pos) != '-')
		{
			if ((formatFlags & CoreTypes::ParseDateTimeFlag_AllowYear) == 0)
				return false;
			if (!ReadYear(input, state))
				return false;		

			if (!positive)
				state.year = -state.year;
		}
		else
		{
			if ((formatFlags & CoreTypes::ParseDateTimeFlag_RequireYear) != 0)
				return false;
			formatFlags &= ~CoreTypes::ParseDateTimeFlag_AllowTime;	// disallow time
			state.year = 4;
		}

		// now care must be taken: the next character can be '-', but this may be part of the timezone
		if (state.pos != input.size() && input.at(state.pos) == '-')
		{
			// if timezone, then '-HH:MM'
			if (state.pos + 3 >= input.size() || input.at(state.pos + 3) != ':')
			{
				// a month, maybe.
				++state.pos;	// skip '-' anyways.
				if (state.pos == input.size())	// ok, that is odd
					return false;

				if (input.at(state.pos) != '-')	
				{
					// month
					if ((formatFlags & CoreTypes::ParseDateTimeFlag_AllowMonth) == 0)
						return false;	// not allowed
					if (!Read2DigitNumber(input, state))
						return false;
					state.month = state.value;
				}
				else
				{
					if ((formatFlags & CoreTypes::ParseDateTimeFlag_RequireMonth) != 0)
						return false;	// was required
					formatFlags &= ~CoreTypes::ParseDateTimeFlag_AllowTime;	// disallow time
					state.month = 1;
				}
			}
			else
			{
				if ((formatFlags & CoreTypes::ParseDateTimeFlag_RequireMonth) != 0)
					return false;	// was required
				formatFlags &= ~CoreTypes::ParseDateTimeFlag_AllowTime;
			}
		}
		else
		{
			if ((formatFlags & CoreTypes::ParseDateTimeFlag_RequireMonth) != 0)
				return false;	// was required
			formatFlags &= ~CoreTypes::ParseDateTimeFlag_AllowTime;
		}

		// now care must be taken: the next character can be '-', but this may be part of the timezone
		if (state.pos != input.size() && input.at(state.pos) == '-')
		{
			// if timezone, then '-HH:MM'
			if (state.pos + 3 >= input.size() || input.at(state.pos + 3) != ':')
			{
				// a day, maybe.
				++state.pos;	// skip '-' anyways.
				if (state.pos == input.size())	// ok, that is odd
					return false;

				// day
				if ((formatFlags & CoreTypes::ParseDateTimeFlag_AllowDay) == 0)
					return false;	// not allowed
				if (!Read2DigitNumber(input, state))
					return false;
				state.day = state.value;
			}
			else
			{
				if ((formatFlags & CoreTypes::ParseDateTimeFlag_RequireDay) != 0)
					return false;	// not allowed
				formatFlags &= ~CoreTypes::ParseDateTimeFlag_AllowTime;
			}
		}
		else
		{
			if ((formatFlags & CoreTypes::ParseDateTimeFlag_RequireDay) != 0)
				return false;	// not allowed
			formatFlags &= ~CoreTypes::ParseDateTimeFlag_AllowTime;
		}

		if (state.pos != input.size() && input.at(state.pos) == 'T')
		{
			// time part 
			if ((formatFlags & CoreTypes::ParseDateTimeFlag_AllowTime) == 0)
				return false; 
			++state.pos;
			if (!ReadTime(input, state))
				return false;
		}
		else
		{
			if ((formatFlags & CoreTypes::ParseDateTimeFlag_RequireTime) != 0)
				return false;
		}
	}

	// timezone
	if (state.pos != input.size())
	{
		char_type c = input.at(state.pos);
		if (c == '+' || c == '-')
		{
			bool positiveOffset = c == '+';
			++state.pos;
			if (!Read2DigitNumber(input, state))
				return false;
			if (state.value >= 24)
				return false;
			state.timezone = state.value * 60;
			bool timezoneMinuteSkip = false;
			bool timezoneMinuteOptional = (formatFlags & CoreTypes::ParseDateTimeFlag_OptionalTimezoneMinute) != 0;
			if (state.pos == input.size())
				if( timezoneMinuteOptional ) 
					timezoneMinuteSkip = true; 
				else 
					return false; 
			if( !timezoneMinuteSkip )
			{
				if (input.at(state.pos) != ':')
					return false;
				++state.pos;
				if (!Read2DigitNumber(input, state))
					return false;
				if (state.value >= 60)
					return false;
				state.timezone += state.value;
			}
			if (!positiveOffset)
				state.timezone = -state.timezone;
		}
		else if (c == 'Z')
		{
			++state.pos;
			state.timezone = 0;
		}		
	}

	SkipWhitespace(input, state);
	if (state.pos != input.size())
		return false;


	value = altova::DateTime(
		state.year, state.month, state.day, state.hour, state.minute, 
		state.second + (double)state.fraction / altova::TicksPerSecond, state.timezone);
	return true;
}


altova::DateTime CoreTypes::ParseTime(const string_type& s, unsigned addendumFlags )
{
	altova::DateTime dt;
	if (!TryParseDateTime(s, CoreTypes::ParseDateTimeFlag_AllowTime | addendumFlags, dt))
		throw altova::StringParseException(_T("time"), s);

	return dt;
}


altova::DateTime CoreTypes::CastToDateTime(const string_type& s)
{
	altova::DateTime dt;
	if (!TryParseDateTime(s, CoreTypes::ParseDateTimeFlag_AllowTime|CoreTypes::ParseDateTimeFlag_AllowDate, dt))
		throw altova::StringParseException(_T("dateTime"), s);

	return dt;
}

altova::DateTime CoreTypes::CastToDateTime(const altova::DateTime& s, DateTimeFormat format)
{
	return CastToDateTime(s);
}


altova::Duration CoreTypes::CastToDuration(const string_type& s)
{
	bool positive = true;
	DateTimeParseState state;
	state.pos = 0;
	SkipWhitespace(s, state);
	if (state.pos == s.size())
		throw altova::StringParseException(_T("duration"), s);

	if (s.at(state.pos) == '-')
	{
		positive = false;
		if (++state.pos == s.size())
			throw altova::StringParseException(_T("duration"), s);
	}

	if (s.at(state.pos) != 'P')
		throw altova::StringParseException(_T("duration"), s);

	if (++state.pos == s.size())
		throw altova::StringParseException(_T("duration"), s);

	int ymvalue = 0;
	__int64 dtvalue = 0;

	bool number = ReadNumber(s, state);
	bool anyFound = false;
	if (number)	// try 'Y'
	{
		if (state.pos == s.size())
			throw altova::StringParseException(_T("duration"), s);
		if (s.at(state.pos) == 'Y')
		{
			anyFound = true;
			ymvalue += state.value * 12;
			++state.pos;
			number = ReadNumber(s, state);
		}
	}
	if (number) // try 'M'
	{
		if (state.pos == s.size())
			throw altova::StringParseException(_T("duration"), s);
		if (s.at(state.pos) == 'M')
		{
			anyFound = true;
			ymvalue += state.value;
			++state.pos;
			number = ReadNumber(s, state);
		}
	}
	if (number) // try 'D'
	{
		if (state.pos == s.size())
			throw altova::StringParseException(_T("duration"), s);
		if (s.at(state.pos) == 'D')
		{
			anyFound = true;
			dtvalue += state.value * 86400 * TicksPerSecond;
			++state.pos;			
		}
	}
	if (state.pos != s.size() && s.at(state.pos) == 'T')
	{
		// time part
		++state.pos;
		number = ReadNumber(s, state);
		if (!number) 
			throw altova::StringParseException(_T("duration"), s);
		if (state.pos == s.size())
			throw altova::StringParseException(_T("duration"), s);
		if (s.at(state.pos) == 'H')
		{
			anyFound = true;
			dtvalue += state.value * 3600 * TicksPerSecond;
			++state.pos;
			number = ReadNumber(s, state);
		}
		if (number)
		{
			if (state.pos == s.size())
				throw altova::StringParseException(_T("duration"), s);
			if (s.at(state.pos) == 'M')
			{
				anyFound = true;
				dtvalue += state.value * 60 * TicksPerSecond;
				++state.pos;
				number = ReadNumber(s, state);
			}
		}
		if (number)
		{
			if (state.pos == s.size())
				throw altova::StringParseException(_T("duration"), s);
			if (s.at(state.pos) == 'S')
			{
				anyFound = true;
				dtvalue += state.value * TicksPerSecond;
				++state.pos;				
			}
			else if (s.at(state.pos) == '.')
			{
				anyFound = true;
				dtvalue += state.value * TicksPerSecond;
				if (!ReadFraction(s, state))
					throw altova::StringParseException(_T("duration"), s);
				dtvalue += state.fraction;
				if (s.at(state.pos) != 'S')
					throw altova::StringParseException(_T("duration"), s);
				++state.pos;
			}
		}
	}

	SkipWhitespace(s, state);
	if (state.pos != s.size())
		throw altova::StringParseException(_T("duration"), s);

	if (!anyFound)
		throw altova::StringParseException(_T("duration"), s);

	return altova::Duration(altova::YearMonthDuration(positive ? ymvalue : -ymvalue), altova::DayTimeDuration(positive ? dtvalue : -dtvalue));
}

//These 2 functions where copied from the CSchemaTypeCalendar classes
//to remove the dependency for all other CSchema* classes
namespace {
	static const int aMonthStart[] = 
	{
		0,	// 1st of Jan
		31,	// 1st of Feb
		59,	// 1st of Mar
		90,	// 1st of Apr
		120, // 1st of May
		151, // 1st of Jun
		181, // 1st of Jul
		212, // 1st of Aug
		243, // 1st of Sep
		273, // 1st of Oct
		304, // 1st of Nov
		334, // 1st of Dec
		365, // 1st of next year
	};

	static const int aMonthStartLeap[] = 
	{
		0,	// 1st of Jan
		31,	// 1st of Feb
		60,	// 1st of Mar
		91,	// 1st of Apr
		121, // 1st of May
		152, // 1st of Jun
		182, // 1st of Jul
		213, // 1st of Aug
		244, // 1st of Sep
		274, // 1st of Oct
		305, // 1st of Nov
		335, // 1st of Dec
		366, // 1st of next year
	};
    
static __int64 GetTimeValue( 
	int nYear, int nMonth, int nDay, int nHour, int nMinute, double dSecond, int nTZOffset)
{
	__int64 nValue = 0; // 0001-01-01T00:00:00.000Z		

	int nMonthRem = ( nMonth - 1 ) % 12;
	if ( nMonthRem < 0 ) nMonthRem += 12;
	nYear += ( nMonth - nMonthRem - 1 ) / 12;
	nMonth = nMonthRem + 1;

	int nYearRed = nYear - 1;
	nValue += ( nYearRed / 400 ) * (303 * 365 + 97 * 366);
	nYearRed %= 400;
	nValue += ( nYearRed / 100 ) * (76 * 365 + 24 * 366);
	nYearRed %= 100;
	nValue += ( nYearRed / 4 ) * (365 * 3 + 366);
	nYearRed %= 4;
	nValue += nYearRed * 365; 

	if ( ( nYear % 4 == 0 ) && ( ( nYear % 100 != 0 ) || ( nYear % 400 == 0 ) ) )
		nValue += aMonthStartLeap[ nMonth - 1 ];
	else
		nValue += aMonthStart[ nMonth - 1 ];

	// add day (1-31)
	nValue += nDay - 1;

	nValue = nValue * 24 + nHour;
	nValue = nValue * 60 + nMinute - nTZOffset;
	nValue = ( __int64 )( ( nValue * 60 + dSecond ) * 1000 );
	return nValue;
}    
    
bool ParseDateTime ( const string_type& sValue, int& ymValue, __int64& dtValue)
{
	string_type sTmp( sValue);
	normalize( sTmp);
	if( sTmp.size() > 0)
	{
		int nPositive = 1;
		int nYear = 0;
		int nMonth= 0;
		int nDay = 0;
		int nHour = 0;
		int nMinute = 0;
		double dSecond = 0.0;

		const TCHAR* szTmp = sTmp.c_str();

		if ( *szTmp == _T('-') )
		{
			nPositive = -1;
			++szTmp;
		}

		// '' and '-' are not valid, and a P has to appear here.
		if ( *szTmp != _T('P') )
			ThrowFormatError();
		++szTmp;

		// algorithm will progress through states, order is important.
		enum TState
		{
			k_Year,
			k_Month,
			k_Day,
			k_Time,
			k_Hour,
			k_Minute,
			k_Second,
			k_Fraction,
			k_Bad,
		} state = k_Year;

		while ( *szTmp )
		{
			// no more data allowed?
			if ( state == k_Bad )
				ThrowFormatError();

			// check if ymd part is over
			if ( *szTmp == _T('T') )
			{
				if ( state >= k_Hour )
					ThrowFormatError();
				state = k_Hour;
				++szTmp;
			}

			if ( state == k_Time )
				ThrowFormatError();

			// now a digit has to follow, and probably more than one
			if ( *szTmp < _T('0') || *szTmp > _T('9') )
				ThrowFormatError();

			unsigned val = 0;
			unsigned digits = 0;
			while ( *szTmp >= _T('0') && *szTmp <= _T('9') )
			{
				if ( val >= 100000000u ) // xe8 * 10 may be >= 2^32
					ThrowFormatError();

				val = val * 10 + ( *szTmp - _T('0') );
				digits += 1;
				++szTmp;
			}

			TState foundState = k_Bad;

			switch ( *szTmp )
			{
			case _T('Y'): if ( state >= k_Hour ) foundState = k_Bad; else foundState = k_Year; break;
			case _T('M'): if ( state >= k_Hour ) foundState = k_Minute; else foundState = k_Month; break;
			case _T('D'): if ( state >= k_Hour ) foundState = k_Bad; else foundState = k_Day; break;
			case _T('H'): if ( state >= k_Hour ) foundState = k_Hour; else foundState = k_Bad; break;
			case _T('S'): if ( state >= k_Fraction ) foundState = k_Fraction;
						  else if ( state >= k_Hour) foundState = k_Second; else foundState = k_Bad; break;
			case _T('.'): if ( state >= k_Hour ) foundState = k_Second; else foundState = k_Bad; break;
			}

			// when finding something that already occurred (or is otherwise invalid), bark.
			if ( foundState == k_Bad || foundState < state )
				ThrowFormatError();

			++szTmp;

			switch ( foundState )
			{
			case k_Year: nYear = val; break;
			case k_Month: nMonth= val; break;
			case k_Day: nDay = val; break;
			case k_Hour: nHour = val; break;
			case k_Minute: nMinute = val; break;
			case k_Second: dSecond = val; break;
			case k_Fraction: dSecond += (double)val * pow(0.1, (int)digits) ; break;
			}

			state = ( TState )( foundState + 1 );
		}

		// if still at start state this means someone 'forgot' to add any data (e.g. 'P' alone)
		if ( state == k_Year )
			ThrowFormatError();

        ymValue = nPositive * (nYear * 12 + nMonth);
        dtValue = nPositive * GetTimeValue( 1, 1, nDay + 1, nHour, nMinute, dSecond, 0 );
	}
	else
		return false;
	return true;
}
}

altova::YearMonthDuration CoreTypes::CastToYearMonthDuration(const string_type& s)
{
	int yearMonthValue;
	__int64 dayTimeValue;
	altova::ParseDateTime( s, yearMonthValue, dayTimeValue);
	return altova::YearMonthDuration(yearMonthValue);
}

altova::DayTimeDuration CoreTypes::CastToDayTimeDuration(const string_type& s)
{
	int yearMonthValue;
	__int64 dayTimeValue;
	altova::ParseDateTime( s, yearMonthValue, dayTimeValue);
	return altova::DayTimeDuration(dayTimeValue);
}

altova::DateTime CoreTypes::CastToDateTime(const altova::DateTime& s) { return s; }
altova::Duration CoreTypes::CastToDuration(const altova::Duration& s) { return s; }
altova::YearMonthDuration CoreTypes::CastToYearMonthDuration(const altova::YearMonthDuration& s) { return s; }
altova::DayTimeDuration CoreTypes::CastToDayTimeDuration(const altova::DayTimeDuration& s) { return s; }



bool CoreTypes::CastToBool(const bool* v)
{
	if (v == 0)
		throw altova::Error(_T("Trying to read NULL value."));
	return *v;
}

int CoreTypes::CastToInt(const int* v)
{
	if (v == 0)
		throw altova::Error(_T("Trying to read NULL value."));
	return *v;
}

unsigned CoreTypes::CastToUInt(const unsigned* v)
{
	if (v == 0)
		throw altova::Error(_T("Trying to read NULL value."));
	return *v;
}

__int64 CoreTypes::CastToInt64(const __int64* v)
{
	if (v == 0)
		throw altova::Error(_T("Trying to read NULL value."));
	return *v;
}

unsigned __int64 CoreTypes::CastToUInt64(const unsigned __int64* v)
{
	if (v == 0)
		throw altova::Error(_T("Trying to read NULL value."));
	return *v;
}

string_type CoreTypes::CastToString(const string_type* v)
{
	if (v == 0)
		throw altova::Error(_T("Trying to read NULL value."));
	return *v;
}

altova::DateTime CoreTypes::CastToDateTime(const altova::DateTime* v)
{
	if (v == 0)
		throw altova::Error(_T("Trying to read NULL value."));
	return *v;
}

altova::Duration CoreTypes::CastToDuration(const altova::Duration* v)
{
	if (v == 0)
		throw altova::Error(_T("Trying to read NULL value."));
	return *v;
}

double CoreTypes::CastToDouble(const double* v)
{
	if (v == 0)
		throw altova::Error(_T("Trying to read NULL value."));
	return *v;
}



int* CoreTypes::Box(int i)
{
	return new int(i);
}

bool* CoreTypes::Box(bool b)
{
	return new bool(b);
}

unsigned* CoreTypes::Box(unsigned u)
{
	return new unsigned(u);
}

__int64* CoreTypes::Box(__int64 i)
{
	return new __int64(i);
}

unsigned __int64* CoreTypes::Box(unsigned __int64 u)
{
	return new unsigned __int64(u);
}

string_type* CoreTypes::Box(const string_type& s)
{
	return new string_type(s);
}

altova::DateTime* CoreTypes::Box(const altova::DateTime& dt)
{
	return new altova::DateTime(dt);
}

altova::Duration* CoreTypes::Box(const altova::Duration& d)
{
	return new altova::Duration(d);
}

double* CoreTypes::Box(double d)
{
	return new double(d);
}


int* CoreTypes::Box(int* p)
{
	if (p == 0) return 0;
	return new int(*p);
}

bool* CoreTypes::Box(bool* p) 
{
	if (p == 0) return 0;
	return new bool(*p);
}

unsigned* CoreTypes::Box(unsigned* p)
{
	if (p == 0) return 0;
	return new unsigned(*p);
}

__int64* CoreTypes::Box(__int64* p)
{
	if (p == 0) return 0;
	return new __int64(*p);
}

unsigned __int64* CoreTypes::Box(unsigned __int64* p)
{
	if (p == 0) return 0;
	return new unsigned __int64(*p);
}

string_type* CoreTypes::Box(string_type* p)
{
	if (p == 0) return 0;
	return new string_type(*p);
}

altova::DateTime* CoreTypes::Box(altova::DateTime* p)
{
	if (p == 0) return 0;
	return new altova::DateTime(*p);
}

altova::Duration* CoreTypes::Box(altova::Duration* p)
{
	if (p == 0) return 0;
	return new altova::Duration(*p);
}

double* CoreTypes::Box(double* p)
{
	if (p == 0) return 0;
	return new double(*p);
}

int CoreTypes::Unbox(int* v)
{
	if (v == 0)
		throw altova::Error(_T("Trying to read NULL value."));
	return *v;
}

bool CoreTypes::Unbox(bool* v)
{
	if (v == 0)
		throw altova::Error(_T("Trying to read NULL value."));
	return *v;
}

unsigned CoreTypes::Unbox(unsigned* v)
{
	if (v == 0)
		throw altova::Error(_T("Trying to read NULL value."));
	return *v;
}

__int64 CoreTypes::Unbox(__int64* v)
{
	if (v == 0)
		throw altova::Error(_T("Trying to read NULL value."));
	return *v;
}

unsigned __int64 CoreTypes::Unbox(unsigned __int64* v)
{
	if (v == 0)
		throw altova::Error(_T("Trying to read NULL value."));
	return *v;
}

string_type CoreTypes::Unbox(string_type* v)
{
	if (v == 0)
		throw altova::Error(_T("Trying to read NULL value."));
	return *v;
}

altova::DateTime CoreTypes::Unbox(altova::DateTime* v)
{
	if (v == 0)
		throw altova::Error(_T("Trying to read NULL value."));
	return *v;
}

altova::Duration CoreTypes::Unbox(altova::Duration* v)
{
	if (v == 0)
		throw altova::Error(_T("Trying to read NULL value."));
	return *v;
}

double CoreTypes::Unbox(double* v)
{
	if (v == 0)
		throw altova::Error(_T("Trying to read NULL value."));
	return *v;
}

string_type CoreTypes::BinaryToBase64String(const std::vector<unsigned char>& v) { return ((XmlFormatter*) Exported_Base64BinaryFormatter)->Format(v); }
const std::vector<unsigned char> CoreTypes::ParseBase64Binary(const string_type& v) { return ((XmlFormatter*) Exported_Base64BinaryFormatter)->ParseBinary(v); }
string_type CoreTypes::BinaryToHexString(const std::vector<unsigned char>& v) { return ((XmlFormatter*) Exported_HexBinaryFormatter)->Format(v); }
const std::vector<unsigned char> CoreTypes::ParseHexBinary(const string_type& v) { return ((XmlFormatter*) Exported_HexBinaryFormatter)->ParseBinary(v); }


}


