/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#ifndef CHARLS_LOOKUPTABLE
#define CHARLS_LOOKUPTABLE

// Tables for fast decoding of short Golomb Codes.

struct Code
{
	Code()
	{
	}

	Code(LONG value, LONG length)	:
		_value(value),
		_length(length)
	{
	}

	LONG GetValue() const
		{ return _value; }
	LONG GetLength() const
		{ return _length; }

	LONG _value;
	LONG _length;
};



class CTable
{
public:

	enum { cbit = 8 } ;

	CTable()
	{
		::memset(rgtype, 0, sizeof(rgtype));
	}

	void AddEntry(BYTE bvalue, Code c);

	inlinehint const Code& Get(LONG value)
		{ return rgtype[value]; }
private:
	Code rgtype[1 << cbit];
};


//
// AddEntry
//
void CTable::AddEntry(BYTE bvalue, Code c)
{
	LONG length = c.GetLength();
	ASSERT(length <= cbit);

	for (LONG i = 0; i < LONG(1) << (cbit - length); ++i)
	{
		ASSERT(rgtype[(bvalue << (cbit - length)) + i].GetLength() == 0);
		rgtype[(bvalue << (cbit - length)) + i] = c;
	}
}

#endif
