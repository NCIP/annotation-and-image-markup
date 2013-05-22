/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/** @file */

#ifndef _LOG4CPLUS_WIN32DEBUG_APPENDER_HEADER_
#define _LOG4CPLUS_WIN32DEBUG_APPENDER_HEADER_

#include "dcmtk/oflog/config.h"
#if defined(_WIN32)

#include "dcmtk/oflog/appender.h"
#include "dcmtk/oflog/helpers/property.h"


namespace log4cplus {

    /**
     * Prints log events using OutputDebugString().
     */
    class LOG4CPLUS_EXPORT Win32DebugAppender
        : public Appender
    {
    public:
      // Ctors
        Win32DebugAppender();
        Win32DebugAppender(const log4cplus::helpers::Properties& properties, tstring& error);

      // Dtor
        virtual ~Win32DebugAppender();

      // Methods
        virtual void close();

    protected:
        virtual void append(const log4cplus::spi::InternalLoggingEvent& event);

    private:
      // Disallow copying of instances of this class
        Win32DebugAppender(const Win32DebugAppender&);
        Win32DebugAppender& operator=(const Win32DebugAppender&);
    };

} // end namespace log4cplus

#endif // _WIN32
#endif // _LOG4CPLUS_WIN32DEBUG_APPENDER_HEADER_

