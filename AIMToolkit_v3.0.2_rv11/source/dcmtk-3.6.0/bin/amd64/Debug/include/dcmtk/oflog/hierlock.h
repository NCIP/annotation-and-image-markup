/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/** @file */

#ifndef _LOG4CPLUS_HIERARCHY_LOCKER_HEADER_
#define _LOG4CPLUS_HIERARCHY_LOCKER_HEADER_

#include "dcmtk/oflog/hierarchy.h"


namespace log4cplus {

    /**
     * This is used to lock a Hierarchy.  The dtor unlocks the Hierarchy.
     */
    class LOG4CPLUS_EXPORT HierarchyLocker {
    public:
      // ctor & dtor
        HierarchyLocker(Hierarchy& h);
        ~HierarchyLocker();

        /**
         * Calls the <code>resetConfiguration()</code> method on the locked Hierarchy.
         */
        void resetConfiguration();

        /**
         * Calls the <code>getInstance()</code> method on the locked Hierarchy.
         */
        Logger getInstance(const log4cplus::tstring& name);

        /**
         * Calls the <code>getInstance()</code> method on the locked Hierarchy.
         */
        Logger getInstance(const log4cplus::tstring& name, spi::LoggerFactory& factory);

        void addAppender(Logger &logger, log4cplus::SharedAppenderPtr& appender);

    private:
      // Data
        Hierarchy& h;
        log4cplus::thread::Guard hierarchyLocker;
        LoggerList loggerList;
    };

} // end namespace log4cplus

#endif // _LOG4CPLUS_HIERARCHY_LOCKER_HEADER_

