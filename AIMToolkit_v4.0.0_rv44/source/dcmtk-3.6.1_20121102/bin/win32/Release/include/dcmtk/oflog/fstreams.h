/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/** @file */

#ifndef DCMTK_LOG4CPLUS_FSTREAMS_HEADER_
#define DCMTK_LOG4CPLUS_FSTREAMS_HEADER_

#include "dcmtk/oflog/config.h"

//#include <fstream>

#if defined(__DECCXX) && !defined(__USE_STD_IOSTREAM)
#  define DCMTK_LOG4CPLUS_FSTREAM_NAMESPACE
#else
#  define DCMTK_LOG4CPLUS_FSTREAM_NAMESPACE std
#endif


namespace dcmtk {
namespace log4cplus {
    typedef DCMTK_LOG4CPLUS_FSTREAM_NAMESPACE::ofstream tofstream;
    typedef DCMTK_LOG4CPLUS_FSTREAM_NAMESPACE::ifstream tifstream;
}
}

#endif // DCMTK_LOG4CPLUS_FSTREAMS_HEADER_

