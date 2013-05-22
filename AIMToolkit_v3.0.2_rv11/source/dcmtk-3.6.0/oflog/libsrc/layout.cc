/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/oflog/layout.h"
#include "dcmtk/oflog/helpers/strhelp.h"
#include "dcmtk/oflog/helpers/timehelp.h"
#include "dcmtk/oflog/spi/logevent.h"


using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;
using namespace log4cplus::spi;


///////////////////////////////////////////////////////////////////////////////
// log4cplus::SimpleLayout public methods
///////////////////////////////////////////////////////////////////////////////

void
SimpleLayout::formatAndAppend(log4cplus::tostream& output,
                              const log4cplus::spi::InternalLoggingEvent& event)
{
    output << llmCache.toString(event.getLogLevel())
           << LOG4CPLUS_TEXT(" - ")
           << event.getMessage()
           << LOG4CPLUS_TEXT("\n");
}



///////////////////////////////////////////////////////////////////////////////
// log4cplus::TTCCLayout ctors and dtor
///////////////////////////////////////////////////////////////////////////////

TTCCLayout::TTCCLayout(bool use_gmtime_)
: dateFormat( LOG4CPLUS_TEXT("%m-%d-%y %H:%M:%S,%q") ),
  use_gmtime(use_gmtime_)
{
}


TTCCLayout::TTCCLayout(const log4cplus::helpers::Properties& properties, tstring&)
: Layout(properties),
  dateFormat( LOG4CPLUS_TEXT("%m-%d-%y %H:%M:%S,%q") ),
  use_gmtime(false)
{
    if(properties.exists( LOG4CPLUS_TEXT("DateFormat") )) {
        dateFormat  = properties.getProperty( LOG4CPLUS_TEXT("DateFormat") );
    }

    tstring tmp = properties.getProperty( LOG4CPLUS_TEXT("Use_gmtime") );
    use_gmtime = (toLower(tmp) == LOG4CPLUS_TEXT("true"));
}


TTCCLayout::~TTCCLayout()
{
}



///////////////////////////////////////////////////////////////////////////////
// log4cplus::TTCCLayout public methods
///////////////////////////////////////////////////////////////////////////////

void
TTCCLayout::formatAndAppend(log4cplus::tostream& output,
                            const log4cplus::spi::InternalLoggingEvent& event)
{
    output << event.getTimestamp().getFormattedTime(dateFormat, use_gmtime)
           << LOG4CPLUS_TEXT(" [")
           << event.getThread()
           << LOG4CPLUS_TEXT("] ")
           << llmCache.toString(event.getLogLevel())
           << LOG4CPLUS_TEXT(" ")
           << event.getLoggerName()
           << LOG4CPLUS_TEXT(" <")
           << event.getNDC()
           << LOG4CPLUS_TEXT("> - ")
           << event.getMessage()
           << LOG4CPLUS_TEXT("\n");
}




