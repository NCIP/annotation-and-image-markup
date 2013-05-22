/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/** @file */

#ifndef _LOG4CPLUS_SYSLOG_APPENDER_HEADER_
#define _LOG4CPLUS_SYSLOG_APPENDER_HEADER_

#include "dcmtk/oflog/config.h"

#if defined(LOG4CPLUS_HAVE_SYSLOG_H) && !defined(_WIN32)
#include "dcmtk/oflog/appender.h"

namespace log4cplus {

    /**
     * Appends log events to a file.
     *
     * <h3>Properties</h3>
     * <dl>
     * <dt><tt>ident</tt></dt>
     * <dd>First argument to <code>openlog()</code>, a string that
     * will be prepended to every message.</dd>
     * </dl>
     */
    class LOG4CPLUS_EXPORT SysLogAppender : public Appender {
    public:
      // Ctors
        SysLogAppender(const tstring& ident);
        SysLogAppender(const log4cplus::helpers::Properties properties, log4cplus::tstring& error);

      // Dtor
        virtual ~SysLogAppender();

      // Methods
        virtual void close();

    protected:
        virtual int getSysLogLevel(const LogLevel& ll) const;
        virtual void append(const spi::InternalLoggingEvent& event);

      // Data
        tstring ident;

    private:
      // Disallow copying of instances of this class
        SysLogAppender(const SysLogAppender&);
        SysLogAppender& operator=(const SysLogAppender&);
    };

} // end namespace log4cplus

#endif // defined(HAVE_SYSLOG_H)

#endif // _LOG4CPLUS_SYSLOG_APPENDER_HEADER_

