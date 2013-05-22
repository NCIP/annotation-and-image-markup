/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

//#include <sstream>
#include "dcmtk/oflog/helpers/syncprims.h"
#include "dcmtk/ofstd/ofconsol.h"


namespace dcmtk { namespace log4cplus { namespace thread { namespace detail {


DCMTK_LOG4CPLUS_EXPORT
void
syncprims_throw_exception (char const * const msg, char const * const file,
    int line)
{
    //STD_NAMESPACE ostringstream oss;
    CERR << file << ":" << line << msg;
    //throw STD_NAMESPACE runtime_error (oss.str ());
    abort();
}


} } } } // namespace dcmtk { namespace log4cplus { namespace thread { namespace detail {
