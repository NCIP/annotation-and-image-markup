/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dcvm.h"

#define INCLUDE_CSTRING
#include "dcmtk/ofstd/ofstdinc.h"

// get the number of values stored in string
unsigned long getVMFromString(const char * val)
{
    unsigned long vm = 1;
    if (val == NULL)
	vm = 0; 
    else
    {
	for(const char * s = strchr(val, '\\'); s; s = strchr(++s, '\\'))
	    vm++;
    }
    return vm;
}

// get first value stored in string, set the parameter to beginning of the
// next value
char * getFirstValueFromString(const char * & s)
{
    if (s)
    {
	const char * p = strchr(s, '\\');
	const char * backup = s;
	size_t len = 0;
	if (p)
	{
	    len = p-s;
	    s += (len+1);
	}
	else
	{
	    len = strlen(s);
	    s = NULL;
	}

	char * result = new char[len+1];
	strncpy(result, backup, len);
	result[len] = '\0';
	return result;
    }
    else
	return NULL;
}


/*
** CVS/RCS Log:
** $Log: dcvm.cc,v $
** Revision 1.10  2010-10-14 13:14:09  joergr
** Updated copyright header. Added reference to COPYRIGHT file.
**
** Revision 1.9  2009-11-04 09:58:10  uli
** Switched to logging mechanism provided by the "new" oflog module
**
** Revision 1.8  2005-12-08 15:41:43  meichel
** Changed include path schema for all DCMTK header files
**
** Revision 1.7  2002/11/27 12:06:54  meichel
** Adapted module dcmdata to use of new header file ofstdinc.h
**
** Revision 1.6  2001/06/01 15:49:13  meichel
** Updated copyright header
**
** Revision 1.5  2000/03/08 16:26:44  meichel
** Updated copyright header.
**
** Revision 1.4  1999/03/31 09:25:44  meichel
** Updated copyright header in module dcmdata
**
** Revision 1.3  1996/04/29 13:35:27  savonge
** -checking NULL string in getVMFromString
**
** Revision 1.2  1996/03/26 09:59:33  meichel
** corrected bug (deletion of const char *) which prevented compilation on NeXT
**
** Revision 1.1  1996/01/29 13:38:30  andreas
** - new put method for every VR to put value as a string
** - better and unique print methods
**
*/

