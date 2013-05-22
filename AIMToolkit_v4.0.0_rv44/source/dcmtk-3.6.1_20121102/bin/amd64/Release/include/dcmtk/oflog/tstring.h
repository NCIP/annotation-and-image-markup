/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/** @file */

#ifndef DCMTK_LOG4CPLUS_TSTRING_HEADER_
#define DCMTK_LOG4CPLUS_TSTRING_HEADER_

#include "dcmtk/oflog/config.h"
#include "dcmtk/ofstd/ofstring.h"

#define DCMTK_LOG4CPLUS_TEXT2(STRING) STRING
#define DCMTK_LOG4CPLUS_TEXT(STRING) DCMTK_LOG4CPLUS_TEXT2(STRING)


namespace dcmtk {
namespace log4cplus {
    typedef char tchar;
    typedef OFString tstring;
}
}

#define DCMTK_LOG4CPLUS_C_STR_TO_TSTRING(STRING) OFString(STRING)
#define DCMTK_LOG4CPLUS_STRING_TO_TSTRING(STRING) STRING
#define DCMTK_LOG4CPLUS_TSTRING_TO_STRING(STRING) STRING

#endif // DCMTK_LOG4CPLUS_TSTRING_HEADER_
