/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/** @file */

#ifndef _LOG4CPLUS_HELPERS_SLEEP_HEADER_
#define _LOG4CPLUS_HELPERS_SLEEP_HEADER_

#include "dcmtk/oflog/config.h"


namespace log4cplus {
    namespace helpers {
        LOG4CPLUS_EXPORT void sleep(unsigned long secs);
    } // end namespace helpers
} // end namespace log4cplus

#endif // _LOG4CPLUS_HELPERS_SLEEP_HEADER_

