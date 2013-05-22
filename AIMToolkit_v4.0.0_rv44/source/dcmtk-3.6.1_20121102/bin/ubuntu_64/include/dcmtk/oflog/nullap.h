/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/** @file */

#ifndef DCMTK__LOG4CPLUS_NULL_APPENDER_HEADER_
#define DCMTK__LOG4CPLUS_NULL_APPENDER_HEADER_

#include "dcmtk/oflog/config.h"
#include "dcmtk/oflog/appender.h"
#include "dcmtk/oflog/helpers/property.h"


namespace dcmtk {
namespace log4cplus {

    /**
     * Appends log events to a file.
     */
    class DCMTK_LOG4CPLUS_EXPORT NullAppender : public Appender {
    public:
      // Ctors
        NullAppender();
        NullAppender(const helpers::Properties& properties, tstring& error);

      // Dtor
        virtual ~NullAppender();

      // Methods
        virtual void close();

    protected:
        virtual void append(const spi::InternalLoggingEvent& event);

    private:
      // Disallow copying of instances of this class
        NullAppender(const NullAppender&);
        NullAppender& operator=(const NullAppender&);
    };

} // end namespace log4cplus
} // end namespace dcmtk

#endif // DCMTK__LOG4CPLUS_NULL_APPENDER_HEADER_

