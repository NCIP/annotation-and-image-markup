/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/oflog/spi/rootlog.h"

using namespace dcmtk::log4cplus;
using namespace dcmtk::log4cplus::helpers;
using namespace dcmtk::log4cplus::spi;



//////////////////////////////////////////////////////////////////////////////
// RootLogger Constructor
//////////////////////////////////////////////////////////////////////////////

RootLogger::RootLogger(Hierarchy& h, LogLevel ll_)
: LoggerImpl(DCMTK_LOG4CPLUS_TEXT("root"), h)
{
    setLogLevel(ll_);
}



//////////////////////////////////////////////////////////////////////////////
// Logger Methods
//////////////////////////////////////////////////////////////////////////////

LogLevel
RootLogger::getChainedLogLevel() const
{
    return ll;
}


void
RootLogger::setLogLevel(LogLevel ll_)
{
    if(ll_ == NOT_SET_LOG_LEVEL) {
        getLogLog().error(DCMTK_LOG4CPLUS_TEXT("You have tried to set NOT_SET_LOG_LEVEL to root."));
    }
    else {
        LoggerImpl::setLogLevel(ll_);
    }
}

