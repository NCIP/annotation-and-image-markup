/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/oflog/windebap.h"


using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;



///////////////////////////////////////////////////////////////////////////////
// log4cplus::Win32DebugAppender ctors and dtor
///////////////////////////////////////////////////////////////////////////////

log4cplus::Win32DebugAppender::Win32DebugAppender()
{
}


log4cplus::Win32DebugAppender::Win32DebugAppender(
    const log4cplus::helpers::Properties& properties, tstring& error)
    : Appender(properties)
{
}



log4cplus::Win32DebugAppender::~Win32DebugAppender()
{
    destructorImpl();
}



///////////////////////////////////////////////////////////////////////////////
// log4cplus::Win32DebugAppender public methods
///////////////////////////////////////////////////////////////////////////////

void
log4cplus::Win32DebugAppender::close()
{
    closed = true;
}



///////////////////////////////////////////////////////////////////////////////
// log4cplus::Win32DebugAppender protected methods
///////////////////////////////////////////////////////////////////////////////

// This method does not need to be locked since it is called by
// doAppend() which performs the locking
void
log4cplus::Win32DebugAppender::append(const spi::InternalLoggingEvent& event)
{
    tostringstream buf;
    layout->formatAndAppend(buf, event);
    OFSTRINGSTREAM_GETSTR(buf, s);
    ::OutputDebugString(s);
    OFSTRINGSTREAM_FREESTR(s);
}
