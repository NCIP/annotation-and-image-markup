/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/** @file */

#ifndef LOG4CPLUS_TSTRING_HEADER_
#define LOG4CPLUS_TSTRING_HEADER_

#include "dcmtk/oflog/config.h"
#include "dcmtk/ofstd/ofstring.h"

#define LOG4CPLUS_TEXT2(STRING) STRING
#define LOG4CPLUS_TEXT(STRING) LOG4CPLUS_TEXT2(STRING)


namespace log4cplus {
    typedef char tchar;
    typedef OFString tstring;
}

#define LOG4CPLUS_C_STR_TO_TSTRING(STRING) OFString(STRING)
#define LOG4CPLUS_STRING_TO_TSTRING(STRING) STRING
#define LOG4CPLUS_TSTRING_TO_STRING(STRING) STRING

#endif // LOG4CPLUS_TSTRING_HEADER_
