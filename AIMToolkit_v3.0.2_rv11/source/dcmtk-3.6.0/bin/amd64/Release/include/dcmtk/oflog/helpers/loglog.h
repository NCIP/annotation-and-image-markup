/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/** @file */

#ifndef _LOG4CPLUS_HELPERS_LOGLOG
#define _LOG4CPLUS_HELPERS_LOGLOG

#include "dcmtk/oflog/config.h"
#include "dcmtk/oflog/tstring.h"
#include "dcmtk/oflog/helpers/pointer.h"
#include "dcmtk/oflog/helpers/threads.h"


namespace log4cplus {
    namespace helpers {

        /**
         * This class used to output log statements from within the log4cplus package.
         *
         * Log4cplus components cannot make log4cplus logging calls. However, it is
         * sometimes useful for the user to learn about what log4cplus is
         * doing. You can enable log4cplus internal logging by defining the
         * <b>log4cplus.configDebug</b> variable.
         *
         * All log4cplus internal debug calls go to <code>cout</code>
         * where as internal error messages are sent to
         * <code>cerr</code>. All internal messages are prepended with
         * the string "log4clus: ".
         */
        class LOG4CPLUS_EXPORT LogLog
            : public virtual log4cplus::helpers::SharedObject
        {
        public:
          // Static methods
            /**
             * Returns a reference to the <code>LogLog</code> singleton.
             */
            static log4cplus::helpers::SharedObjectPtr<LogLog> getLogLog();


            /**
             * Allows to enable/disable log4cplus internal logging.
             */
            void setInternalDebugging(bool enabled);

            /**
             * In quite mode no LogLog generates strictly no output, not even
             * for errors.
             *
             * @param quietMode A true for not
             */
            void setQuietMode(bool quietMode);

            /**
             * This method is used to output log4cplus internal debug
             * statements. Output goes to <code>STD_NAMESPACE cout</code>.
             */
            void debug(const log4cplus::tstring& msg);

            /**
             * This method is used to output log4cplus internal error
             * statements. There is no way to disable error statements.
             * Output goes to <code>STD_NAMESPACE cerr</code>.
             */
            void error(const log4cplus::tstring& msg);

            /**
             * This method is used to output log4cplus internal warning
             * statements. There is no way to disable warning statements.
             * Output goes to <code>STD_NAMESPACE cerr</code>.
             */
            void warn(const log4cplus::tstring& msg);

          // Dtor
            virtual ~LogLog();

          // Data
            LOG4CPLUS_MUTEX_PTR_DECLARE mutex;

        private:
          // Data
            bool debugEnabled;
            bool quietMode;

          // Ctors
            LogLog();
            LogLog(const LogLog&);
        };

    } // end namespace helpers
} // end namespace log4cplus


#endif // _LOG4CPLUS_HELPERS_LOGLOG

