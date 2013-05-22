/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/oflog/hierlock.h"
#include "dcmtk/oflog/helpers/loglog.h"
#include "dcmtk/oflog/spi/logimpl.h"


using namespace dcmtk::log4cplus;
using namespace dcmtk::log4cplus::helpers;



//////////////////////////////////////////////////////////////////////////////
// dcmtk::log4cplus::HierarchyLocker ctor and dtor
//////////////////////////////////////////////////////////////////////////////

HierarchyLocker::HierarchyLocker(Hierarchy& _h)
: h(_h),
  hierarchyLocker(h.hashtable_mutex),
  loggerList()
{
    // Get a copy of all of the Hierarchy's Loggers (except the Root Logger)
    h.initializeLoggerList(loggerList);

    // Lock all of the Hierarchy's Loggers' mutexs
    try {
            for(LoggerListIterator it=loggerList.begin(); it!=loggerList.end(); ++it) {
                DCMTK_LOG4CPLUS_MUTEX_LOCK( (*it).value->appender_list_mutex ) ;
            }
        }
        catch(...) {
            h.getLogLog().error(DCMTK_LOG4CPLUS_TEXT("HierarchyLocker::ctor()- An error occurred while locking"));
            // TODO --> We need to unlock any Logger mutex that we were able to lock
            throw;
        }
    }


    HierarchyLocker::~HierarchyLocker()
    {
        try {
            for(LoggerListIterator it=loggerList.begin(); it!=loggerList.end(); ++it) {
            DCMTK_LOG4CPLUS_MUTEX_UNLOCK( (*it).value->appender_list_mutex ) ;
        }
    }
    catch(...) {
        h.getLogLog().error(DCMTK_LOG4CPLUS_TEXT("HierarchyLocker::dtor()- An error occurred while unlocking"));
        throw;
    }
}

void
HierarchyLocker::resetConfiguration()
{
    Logger root = h.getRoot();
    h.disable(Hierarchy::DISABLE_OFF);

    // begin by closing nested appenders
    // then, remove all appenders
    root.setLogLevel(DEBUG_LOG_LEVEL);
    root.closeNestedAppenders();
    root.removeAllAppenders();

    // repeat
    for(LoggerListIterator it=loggerList.begin(); it!=loggerList.end(); ++it) {
        DCMTK_LOG4CPLUS_MUTEX_UNLOCK( (*it).value->appender_list_mutex ) ;
        (*it).closeNestedAppenders();
        (*it).removeAllAppenders();
        DCMTK_LOG4CPLUS_MUTEX_LOCK( (*it).value->appender_list_mutex ) ;
        (*it).setLogLevel(NOT_SET_LOG_LEVEL);
        (*it).setAdditivity(true);
    }
}


Logger
HierarchyLocker::getInstance(const tstring& name)
{
    return h.getInstanceImpl(name, *h.getLoggerFactory());
}


Logger
HierarchyLocker::getInstance(const tstring& name, spi::LoggerFactory& factory)
{
    return h.getInstanceImpl(name, factory);
}


void
HierarchyLocker::addAppender(Logger& logger, SharedAppenderPtr& appender)
{
    for(LoggerListIterator it=loggerList.begin(); it!=loggerList.end(); ++it) {
        if((*it).value == logger.value) {
            DCMTK_LOG4CPLUS_MUTEX_UNLOCK( logger.value->appender_list_mutex );
            logger.addAppender(appender);
            DCMTK_LOG4CPLUS_MUTEX_LOCK( logger.value->appender_list_mutex );
            return;
        }
    }

    // I don't have this Logger locked
    logger.addAppender(appender);
}


