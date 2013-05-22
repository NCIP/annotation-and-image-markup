/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/oflog/nullap.h"

using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;



///////////////////////////////////////////////////////////////////////////////
// log4cplus::NullAppender ctors and dtor
///////////////////////////////////////////////////////////////////////////////

log4cplus::NullAppender::NullAppender()
{
}


log4cplus::NullAppender::NullAppender(const log4cplus::helpers::Properties& properties, tstring&)
: Appender(properties)
{
}



log4cplus::NullAppender::~NullAppender()
{
    destructorImpl();
}



///////////////////////////////////////////////////////////////////////////////
// log4cplus::NullAppender public methods
///////////////////////////////////////////////////////////////////////////////

void
log4cplus::NullAppender::close()
{
}



///////////////////////////////////////////////////////////////////////////////
// log4cplus::NullAppender protected methods
///////////////////////////////////////////////////////////////////////////////

// This method does not need to be locked since it is called by
// doAppend() which performs the locking
void
log4cplus::NullAppender::append(const spi::InternalLoggingEvent&)
{
}


