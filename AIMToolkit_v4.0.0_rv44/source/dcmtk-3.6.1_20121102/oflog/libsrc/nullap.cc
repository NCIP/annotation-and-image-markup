/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/oflog/nullap.h"

using namespace std;
using namespace dcmtk::log4cplus;
using namespace dcmtk::log4cplus::helpers;



///////////////////////////////////////////////////////////////////////////////
// dcmtk::log4cplus::NullAppender ctors and dtor
///////////////////////////////////////////////////////////////////////////////

NullAppender::NullAppender()
{
}


NullAppender::NullAppender(const helpers::Properties& properties, tstring&)
: Appender(properties)
{
}



NullAppender::~NullAppender()
{
    destructorImpl();
}



///////////////////////////////////////////////////////////////////////////////
// dcmtk::log4cplus::NullAppender public methods
///////////////////////////////////////////////////////////////////////////////

void
NullAppender::close()
{
}



///////////////////////////////////////////////////////////////////////////////
// dcmtk::log4cplus::NullAppender protected methods
///////////////////////////////////////////////////////////////////////////////

// This method does not need to be locked since it is called by
// doAppend() which performs the locking
void
NullAppender::append(const spi::InternalLoggingEvent&)
{
}


