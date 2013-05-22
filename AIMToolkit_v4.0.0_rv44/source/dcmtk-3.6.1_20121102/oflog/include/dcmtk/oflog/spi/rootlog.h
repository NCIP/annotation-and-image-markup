/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/** @file */

#ifndef DCMTK__LOG4CPLUS_SPI_ROOT_LOGGER_HEADER_
#define DCMTK__LOG4CPLUS_SPI_ROOT_LOGGER_HEADER_

#include "dcmtk/oflog/config.h"
#include "dcmtk/oflog/helpers/loglog.h"
#include "dcmtk/oflog/spi/logimpl.h"

namespace dcmtk {
namespace log4cplus {
    namespace spi {

        /**
         * RootLogger sits at the top of the logger hierachy. It is a
         * regular logger except that it provides several guarantees.
         *
         * First, it cannot be assigned a <code>NOT_SET_LOG_LEVEL</code>
         * LogLevel. Second, since root logger cannot have a parent, the
         * getChainedLogLevel method always returns the value of the
         * ll field without walking the hierarchy.
         */
        class DCMTK_LOG4CPLUS_EXPORT RootLogger : public LoggerImpl {
        public:
          // Ctors
            /**
             * The root logger names itself as "root". However, the root
             * logger cannot be retrieved by name.
             */
            RootLogger(Hierarchy& h, LogLevel ll);

          // Methods
            /**
             * Return the assigned LogLevel value without walking the logger
             * hierarchy.
             */
            virtual LogLevel getChainedLogLevel() const;

            /**
             * Setting a NOT_SET_LOG_LEVEL value to the LogLevel of the root logger
             * may have catastrophic results. We prevent this here.
             */
            void setLogLevel(LogLevel ll);

        };

    } // end namespace spi
} // end namespace log4cplus
} // end namespace dcmtk

#endif // DCMTK__LOG4CPLUS_SPI_ROOT_LOGGER_HEADER_

