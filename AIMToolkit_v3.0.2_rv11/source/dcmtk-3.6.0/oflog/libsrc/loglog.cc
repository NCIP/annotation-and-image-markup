/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/oflog/streams.h"
#include "dcmtk/oflog/helpers/loglog.h"
#include "dcmtk/ofstd/ofconsol.h"

using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;


namespace
{

static tchar const PREFIX[] = LOG4CPLUS_TEXT("log4cplus: ");
static tchar const WARN_PREFIX[] = LOG4CPLUS_TEXT("log4cplus:WARN ");
static tchar const ERR_PREFIX[] = LOG4CPLUS_TEXT("log4cplus:ERROR ");

} // namespace



///////////////////////////////////////////////////////////////////////////////
// static methods
///////////////////////////////////////////////////////////////////////////////

SharedObjectPtr<LogLog>
LogLog::getLogLog()
{
    static SharedObjectPtr<LogLog> singleton(new LogLog());
    return singleton;
}



///////////////////////////////////////////////////////////////////////////////
// log4cplus::helpers::LogLog ctor and dtor
///////////////////////////////////////////////////////////////////////////////

LogLog::LogLog()
 : mutex(LOG4CPLUS_MUTEX_CREATE),
   debugEnabled(false),
   quietMode(false)
{
}


LogLog::~LogLog()
{
    LOG4CPLUS_MUTEX_FREE( mutex );
}



///////////////////////////////////////////////////////////////////////////////
// log4cplus::helpers::LogLog public methods
///////////////////////////////////////////////////////////////////////////////

void
LogLog::setInternalDebugging(bool enabled)
{
    debugEnabled = enabled;
}


void
LogLog::setQuietMode(bool quietModeVal)
{
    quietMode = quietModeVal;
}


void
LogLog::debug(const log4cplus::tstring& msg)
{
    LOG4CPLUS_BEGIN_SYNCHRONIZE_ON_MUTEX( mutex )
        if(debugEnabled && !quietMode) {
             ofConsole.lockCout() << PREFIX << msg << endl;
             ofConsole.unlockCout();
        }
    LOG4CPLUS_END_SYNCHRONIZE_ON_MUTEX;
}


void
LogLog::warn(const log4cplus::tstring& msg)
{
    LOG4CPLUS_BEGIN_SYNCHRONIZE_ON_MUTEX( mutex )
        if(quietMode) return;

        ofConsole.lockCerr() << WARN_PREFIX << msg << endl;
        ofConsole.unlockCerr();
    LOG4CPLUS_END_SYNCHRONIZE_ON_MUTEX;
}


void
LogLog::error(const log4cplus::tstring& msg)
{
    LOG4CPLUS_BEGIN_SYNCHRONIZE_ON_MUTEX( mutex )
        if(quietMode) return;

        ofConsole.lockCerr() << ERR_PREFIX << msg << endl;
        ofConsole.unlockCerr();
    LOG4CPLUS_END_SYNCHRONIZE_ON_MUTEX;
}


