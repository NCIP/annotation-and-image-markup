/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/** @file */

#ifndef DCMTK__LOG4CPLUS_HELPERS_SLEEP_HEADER_
#define DCMTK__LOG4CPLUS_HELPERS_SLEEP_HEADER_

#include "dcmtk/oflog/config.h"


namespace dcmtk {
namespace log4cplus {
    namespace helpers {
        DCMTK_LOG4CPLUS_EXPORT void sleep(unsigned long secs);
    } // end namespace helpers
} // end namespace log4cplus
} // end namespace dcmtk

#endif // DCMTK__LOG4CPLUS_HELPERS_SLEEP_HEADER_

