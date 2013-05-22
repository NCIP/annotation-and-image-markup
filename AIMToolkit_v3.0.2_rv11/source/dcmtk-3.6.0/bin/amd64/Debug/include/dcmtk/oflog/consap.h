/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/** @file */

#ifndef _LOG4CPLUS_CONSOLE_APPENDER_HEADER_
#define _LOG4CPLUS_CONSOLE_APPENDER_HEADER_

#include "dcmtk/oflog/config.h"
#include "dcmtk/oflog/appender.h"

namespace log4cplus {
    /**
     * ConsoleAppender appends log events to <code>STD_NAMESPACE cout</code> or
     * <code>STD_NAMESPACE cerr</code> using a layout specified by the
     * user. The default target is <code>STD_NAMESPACE cout</code>.
     *
     * <h3>Properties</h3>
     * <dl>
     * <dt><tt>logToStdErr</tt></dt>
     * <dd>When it is set true, the output stream will be
     * <code>STD_NAMESPACE cerr</code> instead of <code>STD_NAMESPACE cout</code>.</dd>
     *
     * <dt><tt>ImmediateFlush</tt></dt>
     * <dd>When it is set true, output stream will be flushed after
     * each appended event.</dd>
     *
     * </dl>
     */
    class LOG4CPLUS_EXPORT ConsoleAppender : public Appender {
    public:
      // Ctors
        ConsoleAppender(bool logToStdErr = false, bool immediateFlush = false);
        ConsoleAppender(const log4cplus::helpers::Properties properties, log4cplus::tstring& error);

      // Dtor
        ~ConsoleAppender();

      // Methods
        virtual void close();

    protected:
        virtual void append(const spi::InternalLoggingEvent& event);

      // Data
        bool logToStdErr;
        /**
         * Immediate flush means that the underlying output stream
         * will be flushed at the end of each append operation.
         */
        bool immediateFlush;
    };

} // end namespace log4cplus

#endif // _LOG4CPLUS_CONSOLE_APPENDER_HEADER_

