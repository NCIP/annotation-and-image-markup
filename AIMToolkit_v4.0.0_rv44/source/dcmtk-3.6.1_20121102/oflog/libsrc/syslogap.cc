/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/oflog/syslogap.h"
#if defined(DCMTK_LOG4CPLUS_HAVE_SYSLOG_H) && !defined(_WIN32)

#include "dcmtk/oflog/streams.h"
#include "dcmtk/oflog/helpers/loglog.h"
#include "dcmtk/oflog/spi/logevent.h"

#include <syslog.h>

using namespace std;
using namespace dcmtk::log4cplus;
using namespace dcmtk::log4cplus::helpers;



///////////////////////////////////////////////////////////////////////////////
// dcmtk::log4cplus::SysLogAppender ctors and dtor
///////////////////////////////////////////////////////////////////////////////

SysLogAppender::SysLogAppender(const tstring& id)
: ident(id)
{
    ::openlog(DCMTK_LOG4CPLUS_TSTRING_TO_STRING (ident).c_str(), 0, 0);
}


SysLogAppender::SysLogAppender(const Properties properties, tstring&)
: Appender(properties)
{
    ident = properties.getProperty( DCMTK_LOG4CPLUS_TEXT("ident") );
    ::openlog(DCMTK_LOG4CPLUS_TSTRING_TO_STRING (ident).c_str(), 0, 0);
}


SysLogAppender::~SysLogAppender()
{
    destructorImpl();
}



///////////////////////////////////////////////////////////////////////////////
// dcmtk::log4cplus::SysLogAppender public methods
///////////////////////////////////////////////////////////////////////////////

void
SysLogAppender::close()
{
    getLogLog().debug(DCMTK_LOG4CPLUS_TEXT("Entering SysLogAppender::close()..."));
    DCMTK_LOG4CPLUS_BEGIN_SYNCHRONIZE_ON_MUTEX( access_mutex )
        ::closelog();
        closed = true;
    DCMTK_LOG4CPLUS_END_SYNCHRONIZE_ON_MUTEX;
}



///////////////////////////////////////////////////////////////////////////////
// dcmtk::log4cplus::SysLogAppender protected methods
///////////////////////////////////////////////////////////////////////////////

int
SysLogAppender::getSysLogLevel(const LogLevel& ll) const
{
    if(ll < DEBUG_LOG_LEVEL) {
        return -1;
    }
    else if(ll < INFO_LOG_LEVEL) {
        return LOG_DEBUG;
    }
    else if(ll < WARN_LOG_LEVEL) {
        return LOG_INFO;
    }
    else if(ll < ERROR_LOG_LEVEL) {
        return LOG_WARNING;
    }
    else if(ll < FATAL_LOG_LEVEL) {
        return LOG_ERR;
    }
    else if(ll == FATAL_LOG_LEVEL) {
        return LOG_CRIT;
    }

    return LOG_ALERT;  // ll > FATAL_LOG_LEVEL
}


// This method does not need to be locked since it is called by
// doAppend() which performs the locking
void
SysLogAppender::append(const spi::InternalLoggingEvent& event)
{
    int level = getSysLogLevel(event.getLogLevel());
    if(level != -1) {
        tostringstream buf;
        layout->formatAndAppend(buf, event);
        ::syslog(level, "%s", DCMTK_LOG4CPLUS_TSTRING_TO_STRING(buf.str()).c_str());
    }
}

#endif // defined(DCMTK_LOG4CPLUS_HAVE_SYSLOG_H)

