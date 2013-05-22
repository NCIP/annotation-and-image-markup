/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/oflog/streams.h"
#include "dcmtk/oflog/helpers/lloguser.h"
#include "dcmtk/oflog/helpers/loglog.h"

using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;

typedef SharedObjectPtr<LogLog> LogLogPtr;



///////////////////////////////////////////////////////////////////////////////
// log4cplus::helpers::LogLogUser ctor and dtor
///////////////////////////////////////////////////////////////////////////////

LogLogUser::LogLogUser()
{
    loglogRef = new SharedObjectPtr<LogLog>(LogLog::getLogLog());
}


LogLogUser::LogLogUser(const LogLogUser& rhs)
{
    loglogRef = new SharedObjectPtr<LogLog>(*OFstatic_cast(LogLogPtr*, rhs.loglogRef));
}


LogLogUser::~LogLogUser()
{
    delete OFstatic_cast(LogLogPtr*, loglogRef);
}



///////////////////////////////////////////////////////////////////////////////
// log4cplus::helpers::LogLogUser public methods
///////////////////////////////////////////////////////////////////////////////

LogLog&
LogLogUser::getLogLog() const
{
    LogLogPtr* ptr = OFstatic_cast(LogLogPtr*, loglogRef);
    return **ptr;
}


LogLogUser&
LogLogUser::operator=(const LogLogUser& rhs)
{
    if(this == &rhs) {
        return *this;
    }

    delete OFstatic_cast(LogLogPtr*, loglogRef);
    loglogRef = new SharedObjectPtr<LogLog>(*OFstatic_cast(LogLogPtr*, rhs.loglogRef));

    return *this;
}

