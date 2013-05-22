/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef DCVM_H
#define DCVM_H

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

/** compute the number of values stored in one string
 *  @param val string
 *  @return number of values separated by backslash characters in this string
 */
unsigned long getVMFromString(const char * val);

/** get the first value strored in the given string and update the parameter
 *  to point to the next value in the string (values separated by backslash).
 *  The result of this function is allocated with new[] and must be delete[]d by the caller.
 *  The original string pointed to by s is not modified.
 *  @param s points to start of string; updated to point to start of next value in string
 *  @return first value in string, zero-terminated. char array allocated on heap, must be delete[]d by caller
 */
char * getFirstValueFromString(const char * & s);


#endif 

/*
** CVS/RCS Log:
** $Log: dcvm.h,v $
** Revision 1.9  2010-10-14 13:15:42  joergr
** Updated copyright header. Added reference to COPYRIGHT file.
**
** Revision 1.8  2009-11-04 09:58:07  uli
** Switched to logging mechanism provided by the "new" oflog module
**
** Revision 1.7  2007-11-29 14:30:35  meichel
** Updated doxygen API documentation
**
** Revision 1.6  2005/12/08 16:28:49  meichel
** Changed include path schema for all DCMTK header files
**
** Revision 1.5  2001/06/01 15:48:47  meichel
** Updated copyright header
**
** Revision 1.4  2000/03/08 16:26:20  meichel
** Updated copyright header.
**
** Revision 1.3  1999/03/31 09:24:53  meichel
** Updated copyright header in module dcmdata
**
** Revision 1.2  1996/03/26 09:59:20  meichel
** corrected bug (deletion of const char *) which prevented compilation on NeXT
**
** Revision 1.1  1996/01/29 13:38:15  andreas
** - new put method for every VR to put value as a string
** - better and unique print methods
**
*/

