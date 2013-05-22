/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/** @file */

#ifndef DCMTK__LOG4CPLUS_HELPERS_APPENDER_ATTACHABLE_IMPL_HEADER_
#define DCMTK__LOG4CPLUS_HELPERS_APPENDER_ATTACHABLE_IMPL_HEADER_

#include "dcmtk/oflog/config.h"
#include "dcmtk/oflog/layout.h"
#include "dcmtk/oflog/tstring.h"
#include "dcmtk/oflog/helpers/lloguser.h"
#include "dcmtk/oflog/helpers/pointer.h"
#include "dcmtk/oflog/helpers/threads.h"
#include "dcmtk/oflog/spi/apndatch.h"

//#include <memory>
//#include <vector>


namespace dcmtk {
namespace log4cplus {
    namespace helpers {

        /**
         * This Interface is for attaching Appenders to objects.
         */
        class DCMTK_LOG4CPLUS_EXPORT AppenderAttachableImpl
                                   : public spi::AppenderAttachable,
                                     protected helpers::LogLogUser
        {
        public:
          // Data
            DCMTK_LOG4CPLUS_MUTEX_PTR_DECLARE appender_list_mutex;

          // Ctors
            AppenderAttachableImpl();

          // Dtor
            virtual ~AppenderAttachableImpl();

          // Methods
            /**
             * Add an appender.  If the appender is already in the list in
             * won't be added again.
             */
            virtual void addAppender(SharedAppenderPtr newAppender);

            /**
             * Get all previously added appenders as an vectory.
             */
            virtual SharedAppenderPtrList getAllAppenders();

            /**
             * Look for an attached appender named as <code>name</code>.
             *
             * Return the appender with that name if in the list. Return null
             * otherwise.
             */
            virtual SharedAppenderPtr getAppender(const tstring& name);

            /**
             * Remove all previously added appenders.
             */
            virtual void removeAllAppenders();

            /**
             * Remove the appender passed as parameter from the list of appenders.
             */
            virtual void removeAppender(SharedAppenderPtr appender);

            /**
             * Remove the appender with the name passed as parameter from the
             * list of appenders.
             */
            virtual void removeAppender(const tstring& name);

            /**
             * Call the <code>doAppend</code> method on all attached appenders.
             */
            int appendLoopOnAppenders(const spi::InternalLoggingEvent& event) const;

        protected:
          // Types
            typedef OFList<SharedAppenderPtr> ListType;
            typedef OFListIterator(SharedAppenderPtr) ListIteratorType;
            typedef OFListConstIterator(SharedAppenderPtr) ListConstIteratorType;

          // Data
            /** Array of appenders. */
            ListType appenderList;
        };  // end class AppenderAttachableImpl

    } // end namespace helpers
} // end namespace log4cplus
} // namespace dcmtk

#endif // DCMTK__LOG4CPLUS_HELPERS_APPENDER_ATTACHABLE_IMPL_HEADER_

