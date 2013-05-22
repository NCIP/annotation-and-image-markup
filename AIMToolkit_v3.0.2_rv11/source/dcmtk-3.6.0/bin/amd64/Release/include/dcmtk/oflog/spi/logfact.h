/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/** @file */

#ifndef _LOG4CPLUS_SPI_LOGGER_FACTORY_HEADER
#define _LOG4CPLUS_SPI_LOGGER_FACTORY_HEADER

#include "dcmtk/oflog/config.h"
#include "dcmtk/oflog/tstring.h"
#include "dcmtk/oflog/helpers/pointer.h"


namespace log4cplus {
    // Forward Declarations
    class Logger;
    class Hierarchy;

    namespace spi {
        /**
         * Implement this interface to create new instances of Logger or
         * a sub-class of Logger.
         */
        class LOG4CPLUS_EXPORT LoggerFactory {
        public:
            /**
             * Creates a new <code>Logger</code> object.
             */
            virtual Logger makeNewLoggerInstance(const log4cplus::tstring& name,
                                                 Hierarchy& h) = 0;
            virtual ~LoggerFactory() = 0;
        };

    } // end namespace spi
} // end namespace log4cplus

#endif // _LOG4CPLUS_SPI_LOGGER_FACTORY_HEADER

