/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/** @file */

#ifndef _LOG4CPLUS_HELPERS_LOGLOG_USER
#define _LOG4CPLUS_HELPERS_LOGLOG_USER

#include "dcmtk/oflog/config.h"


namespace log4cplus {
    namespace helpers {
        // forward declarations
        class LogLog;

        /**
         * This class used to simplify the use of the LogLog class.  Any class
         * that uses the LogLog class should extend this class and retrieve
         * their reference to LogLog using the method provided.
         */
        class LOG4CPLUS_EXPORT LogLogUser {
        public:
          // ctor and dtor
            LogLogUser();
            LogLogUser(const LogLogUser&);
            virtual ~LogLogUser();

          // public methods
            LogLog& getLogLog() const;

          // operators
            LogLogUser& operator=(const LogLogUser& rhs);

        private:
          // Data
            void* loglogRef;
        };

    } // end namespace helpers
} // end namespace log4cplus


#endif // _LOG4CPLUS_HELPERS_LOGLOG_USER

