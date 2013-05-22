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
using namespace dcmtk::log4cplus;
using namespace dcmtk::log4cplus::helpers;
using namespace dcmtk::log4cplus::spi;


///////////////////////////////////////////////////////////////////////////////
// dcmtk::log4cplus::SimpleLayout public methods
///////////////////////////////////////////////////////////////////////////////

void
SimpleLayout::formatAndAppend(tostream& output,
                              const InternalLoggingEvent& event)
{
    output << llmCache.toString(event.getLogLevel())
           << DCMTK_LOG4CPLUS_TEXT(" - ")
           << event.getMessage()
           << DCMTK_LOG4CPLUS_TEXT("\n");
}



///////////////////////////////////////////////////////////////////////////////
// dcmtk::log4cplus::TTCCLayout ctors and dtor
///////////////////////////////////////////////////////////////////////////////

TTCCLayout::TTCCLayout(bool use_gmtime_)
: dateFormat( DCMTK_LOG4CPLUS_TEXT("%m-%d-%y %H:%M:%S,%q") ),
  use_gmtime(use_gmtime_)
{
}


TTCCLayout::TTCCLayout(const Properties& properties, tstring&)
: Layout(properties),
  dateFormat( DCMTK_LOG4CPLUS_TEXT("%m-%d-%y %H:%M:%S,%q") ),
  use_gmtime(false)
{
    if(properties.exists( DCMTK_LOG4CPLUS_TEXT("DateFormat") )) {
        dateFormat  = properties.getProperty( DCMTK_LOG4CPLUS_TEXT("DateFormat") );
    }

    tstring tmp = properties.getProperty( DCMTK_LOG4CPLUS_TEXT("Use_gmtime") );
    use_gmtime = (toLower(tmp) == DCMTK_LOG4CPLUS_TEXT("true"));
}


TTCCLayout::~TTCCLayout()
{
}



///////////////////////////////////////////////////////////////////////////////
// dcmtk::log4cplus::TTCCLayout public methods
///////////////////////////////////////////////////////////////////////////////

void
TTCCLayout::formatAndAppend(tostream& output,
                            const InternalLoggingEvent& event)
{
    output << event.getTimestamp().getFormattedTime(dateFormat, use_gmtime)
           << DCMTK_LOG4CPLUS_TEXT(" [")
           << event.getThread()
           << DCMTK_LOG4CPLUS_TEXT("] ")
           << llmCache.toString(event.getLogLevel())
           << DCMTK_LOG4CPLUS_TEXT(" ")
           << event.getLoggerName()
           << DCMTK_LOG4CPLUS_TEXT(" <")
           << event.getNDC()
           << DCMTK_LOG4CPLUS_TEXT("> - ")
           << event.getMessage()
           << DCMTK_LOG4CPLUS_TEXT("\n");
}




