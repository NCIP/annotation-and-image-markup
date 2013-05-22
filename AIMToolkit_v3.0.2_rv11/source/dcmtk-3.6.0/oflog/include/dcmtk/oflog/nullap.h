/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/** @file */

#ifndef _LOG4CPLUS_NULL_APPENDER_HEADER_
#define _LOG4CPLUS_NULL_APPENDER_HEADER_

#include "dcmtk/oflog/config.h"
#include "dcmtk/oflog/appender.h"
#include "dcmtk/oflog/helpers/property.h"


namespace log4cplus {

    /**
     * Appends log events to a file.
     */
    class LOG4CPLUS_EXPORT NullAppender : public Appender {
    public:
      // Ctors
        NullAppender();
        NullAppender(const log4cplus::helpers::Properties& properties, log4cplus::tstring& error);

      // Dtor
        virtual ~NullAppender();

      // Methods
        virtual void close();

    protected:
        virtual void append(const log4cplus::spi::InternalLoggingEvent& event);

    private:
      // Disallow copying of instances of this class
        NullAppender(const NullAppender&);
        NullAppender& operator=(const NullAppender&);
    };

} // end namespace log4cplus

#endif // _LOG4CPLUS_NULL_APPENDER_HEADER_

