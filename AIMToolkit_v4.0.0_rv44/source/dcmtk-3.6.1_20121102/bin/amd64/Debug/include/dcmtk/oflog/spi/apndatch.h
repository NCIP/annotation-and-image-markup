/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/** @file */

#ifndef DCMTK__LOG4CPLUS_SPI_APPENDER_ATTACHABLE_HEADER_
#define DCMTK__LOG4CPLUS_SPI_APPENDER_ATTACHABLE_HEADER_

#include "dcmtk/oflog/config.h"
#include "dcmtk/oflog/appender.h"
#include "dcmtk/oflog/tstring.h"
#include "dcmtk/oflog/helpers/pointer.h"
//#include <vector>

namespace dcmtk {
namespace log4cplus {
    // Forward Declarations
    typedef helpers::SharedObjectPtr<Appender> SharedAppenderPtr;
    typedef OFList<SharedAppenderPtr> SharedAppenderPtrList;
    typedef OFListIterator(SharedAppenderPtr) SharedAppenderPtrListIterator;

    namespace spi {

        /**
         * This Interface is for attaching Appenders to objects.
         */
        class DCMTK_LOG4CPLUS_EXPORT AppenderAttachable {
        public:
          // Methods
            /**
             * Add an appender.
             */
            virtual void addAppender(SharedAppenderPtr newAppender) = 0;

            /**
             * Get all previously added appenders as an Enumeration.
             */
            virtual SharedAppenderPtrList getAllAppenders() = 0;

            /**
             * Get an appender by name.
             */
            virtual SharedAppenderPtr getAppender(const tstring& name) = 0;

            /**
             * Remove all previously added appenders.
             */
            virtual void removeAllAppenders() = 0;

            /**
             * Remove the appender passed as parameter from the list of appenders.
             */
            virtual void removeAppender(SharedAppenderPtr appender) = 0;

            /**
             * Remove the appender with the name passed as parameter from the
             * list of appenders.
             */
            virtual void removeAppender(const tstring& name) = 0;

          // Dtor
            virtual ~AppenderAttachable() = 0;
        };

    } // end namespace spi
} // end namespace log4cplus
} // end namespace dcmtk

#endif // DCMTK__LOG4CPLUS_SPI_APPENDER_ATTACHABLE_HEADER_

