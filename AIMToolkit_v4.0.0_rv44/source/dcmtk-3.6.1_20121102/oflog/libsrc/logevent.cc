/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/oflog/spi/logevent.h"


using namespace dcmtk::log4cplus;
using namespace dcmtk::log4cplus::spi;


#define DCMTK_LOG4CPLUS_DEFAULT_TYPE 1


///////////////////////////////////////////////////////////////////////////////
// InternalLoggingEvent dtor
///////////////////////////////////////////////////////////////////////////////

InternalLoggingEvent::~InternalLoggingEvent()
{
}



///////////////////////////////////////////////////////////////////////////////
// InternalLoggingEvent static methods
///////////////////////////////////////////////////////////////////////////////

unsigned int
InternalLoggingEvent::getDefaultType()
{
    return DCMTK_LOG4CPLUS_DEFAULT_TYPE;
}



///////////////////////////////////////////////////////////////////////////////
// InternalLoggingEvent implementation
///////////////////////////////////////////////////////////////////////////////

const tstring&
InternalLoggingEvent::getMessage() const
{
    return message;
}


unsigned int
InternalLoggingEvent::getType() const
{
    return DCMTK_LOG4CPLUS_DEFAULT_TYPE;
}



OFauto_ptr<InternalLoggingEvent>
InternalLoggingEvent::clone() const
{
    OFauto_ptr<InternalLoggingEvent> tmp(new InternalLoggingEvent(*this));
    return tmp;
}



InternalLoggingEvent&
InternalLoggingEvent::operator=(const InternalLoggingEvent& rhs)
{
    if(this == &rhs) return *this;

    message = rhs.message;
    loggerName = rhs.loggerName;
    ll = rhs.ll;
    ndc = rhs.getNDC();
    thread = rhs.getThread();
    timestamp = rhs.timestamp;
    file = rhs.file;
    function = rhs.function;
    line = rhs.line;
    threadCached = true;
    ndcCached = true;

    return *this;
}


