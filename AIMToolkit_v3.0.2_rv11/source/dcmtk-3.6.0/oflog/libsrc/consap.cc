/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/oflog/layout.h"
#include "dcmtk/oflog/consap.h"
#include "dcmtk/oflog/streams.h"
#include "dcmtk/oflog/helpers/loglog.h"
#include "dcmtk/oflog/helpers/strhelp.h"
#include "dcmtk/oflog/spi/logevent.h"
#include "dcmtk/ofstd/ofconsol.h"

using namespace std;
using namespace log4cplus::helpers;


//////////////////////////////////////////////////////////////////////////////
// log4cplus::ConsoleAppender ctors and dtor
//////////////////////////////////////////////////////////////////////////////

log4cplus::ConsoleAppender::ConsoleAppender(bool logToStdErr_, bool immediateFlush_)
: logToStdErr(logToStdErr_),
  immediateFlush(immediateFlush_)
{
}



log4cplus::ConsoleAppender::ConsoleAppender(const log4cplus::helpers::Properties properties, log4cplus::tstring&)
: Appender(properties),
  logToStdErr(false),
  immediateFlush(false)
{
    tstring val = toLower(properties.getProperty(LOG4CPLUS_TEXT("logToStdErr")));
    if(val == LOG4CPLUS_TEXT("true")) {
        logToStdErr = true;
    }
    if(properties.exists( LOG4CPLUS_TEXT("ImmediateFlush") )) {
        tstring tmp = properties.getProperty( LOG4CPLUS_TEXT("ImmediateFlush") );
        immediateFlush = (toLower(tmp) == LOG4CPLUS_TEXT("true"));
    }
}



log4cplus::ConsoleAppender::~ConsoleAppender()
{
    destructorImpl();
}



//////////////////////////////////////////////////////////////////////////////
// log4cplus::ConsoleAppender public methods
//////////////////////////////////////////////////////////////////////////////

void
log4cplus::ConsoleAppender::close()
{
    getLogLog().debug(LOG4CPLUS_TEXT("Entering ConsoleAppender::close().."));
    closed = true;
}



//////////////////////////////////////////////////////////////////////////////
// log4cplus::ConsoleAppender protected methods
//////////////////////////////////////////////////////////////////////////////

// Normally, append() methods do not need to be locked since they are
// called by doAppend() which performs the locking.  However, this locks
// on the LogLog instance, so we don't have multiple threads writing to
// tcout and tcerr
void
log4cplus::ConsoleAppender::append(const spi::InternalLoggingEvent& event)
{
    LOG4CPLUS_BEGIN_SYNCHRONIZE_ON_MUTEX( getLogLog().mutex )
        log4cplus::tostream& output = (logToStdErr ? ofConsole.lockCerr() : ofConsole.lockCout());
        layout->formatAndAppend(output, event);
        if(immediateFlush) {
            output.flush();
        }
        if (logToStdErr) {
            ofConsole.unlockCerr();
        } else {
            ofConsole.unlockCout();
        }
    LOG4CPLUS_END_SYNCHRONIZE_ON_MUTEX;
}


