/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef DCMTK_LOG4CPLUS_WIN32CONSOLEAPPENDER_H
#define DCMTK_LOG4CPLUS_WIN32CONSOLEAPPENDER_H


#include "dcmtk/oflog/config.h"
#if defined(_WIN32) && defined (DCMTK_LOG4CPLUS_HAVE_WIN32_CONSOLE)

#include "dcmtk/oflog/appender.h"
#include "dcmtk/oflog/helpers/property.h"


namespace dcmtk
{
namespace log4cplus
{

   /**
    * Prints events to Win32 console.
    *
    * <h3>Properties</h3>
    * <dl>
    * <dt><tt>AllocConsole</tt></dt>
    * <dd>This boolean property specifies whether or not this appender
    * will try to allocate new console using the
    * <code>AllocConsole()</code> Win32 function.</dd>
    *
    * </dl>
    */
    class DCMTK_LOG4CPLUS_EXPORT Win32ConsoleAppender
        : public Appender
    {
    public:
        explicit Win32ConsoleAppender (bool allocConsole = true);
        Win32ConsoleAppender (helpers::Properties const & properties, tstring& error);
        virtual ~Win32ConsoleAppender ();

        virtual void close ();

    protected:
        virtual void append (spi::InternalLoggingEvent const &);

        void write_handle (HANDLE, tchar const *, size_t);
        void write_console (HANDLE, tchar const *, size_t);

        bool alloc_console;

    private:
        Win32ConsoleAppender (Win32ConsoleAppender const &);
        Win32ConsoleAppender & operator = (Win32ConsoleAppender const &);
    };

} // namespace log4cplus
} // namespace dcmtk

#endif

#endif // DCMTK_LOG4CPLUS_WIN32CONSOLEAPPENDER_H
