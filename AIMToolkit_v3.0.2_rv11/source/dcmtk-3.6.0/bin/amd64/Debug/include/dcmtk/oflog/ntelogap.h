/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/** @file */

#ifndef _LOG4CPLUS_NT_EVENT_LOG_APPENDER_HEADER_
#define _LOG4CPLUS_NT_EVENT_LOG_APPENDER_HEADER_

#include "dcmtk/oflog/config.h"
#include "dcmtk/oflog/appender.h"

#if defined(_WIN32)
#  if ! defined (LOG4CPLUS_HAVE_NT_EVENT_LOG)
#    error "Your platform does not support NT event log."
#  else


namespace log4cplus {

    /**
     * Appends log events to NT EventLog.
     */
    class LOG4CPLUS_EXPORT NTEventLogAppender : public Appender {
    public:
      // ctors
        NTEventLogAppender(const log4cplus::tstring& server,
                           const log4cplus::tstring& log,
                           const log4cplus::tstring& source);
        NTEventLogAppender(const log4cplus::helpers::Properties properties, tstring& error);

      // dtor
        virtual ~NTEventLogAppender();

      // public Methods
        virtual void close();

    protected:
        virtual void append(const spi::InternalLoggingEvent& event);
        virtual WORD getEventType(const spi::InternalLoggingEvent& event);
        virtual WORD getEventCategory(const spi::InternalLoggingEvent& event);
        void init();

        /*
         * Add this source with appropriate configuration keys to the registry.
         */
        void addRegistryInfo();

      // Data
        log4cplus::tstring server;
        log4cplus::tstring log;
        log4cplus::tstring source;
        HANDLE hEventLog;
        SID* pCurrentUserSID;

    private:
      // Disallow copying of instances of this class
        NTEventLogAppender(const NTEventLogAppender&);
        NTEventLogAppender& operator=(const NTEventLogAppender&);
    };

} // end namespace log4cplus

#endif // LOG4CPLUS_HAVE_NT_EVENT_LOG
#endif // _WIN32
#endif //_LOG4CPLUS_NT_EVENT_LOG_APPENDER_HEADER_
