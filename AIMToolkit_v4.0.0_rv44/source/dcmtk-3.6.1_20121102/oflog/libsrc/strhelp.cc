/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/oflog/helpers/strhelp.h"
#include "dcmtk/oflog/streams.h"
#include "dcmtk/oflog/logmacro.h"
#include "dcmtk/ofstd/ofstd.h"

//#include <iterator>
//#include <algorithm>
//#include <cstring>
//#include <cwchar>
//#include <cwctype>
//#include <cctype>

using namespace dcmtk::log4cplus;

#if defined (DCMTK_LOG4CPLUS_SINGLE_THREADED)

namespace dcmtk
{

namespace log4cplus
{

tostringstream _macros_oss;

namespace
{

static tostringstream const _macros_oss_defaults;

} // namespace

void _clear_tostringstream (tostringstream & os)
{
    os.clear ();
    os.str ("");
    os.setf (_macros_oss_defaults.flags ());
    os.fill (_macros_oss_defaults.fill ());
    os.precision (_macros_oss_defaults.precision ());
    os.width (_macros_oss_defaults.width ());
#if defined (DCMTK_LOG4CPLUS_WORKING_LOCALE)
    STD_NAMESPACE locale glocale = STD_NAMESPACE locale ();
    if (os.getloc () != glocale)
        os.imbue (glocale);
#endif // defined (DCMTK_LOG4CPLUS_WORKING_LOCALE)
}

} // namespace log4cplus

} // namespace dcmtk

#endif


//////////////////////////////////////////////////////////////////////////////
// Global Methods
//////////////////////////////////////////////////////////////////////////////

tstring
helpers::toUpper(const tstring& s)
{
    OFString tmp;
    return OFStandard::toUpper(tmp, s);
}


tstring
helpers::toLower(const tstring& s)
{
    OFString tmp;
    return OFStandard::toLower(tmp, s);
}
