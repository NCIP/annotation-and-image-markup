/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/oflog/spi/factory.h"
#include "dcmtk/oflog/spi/logfact.h"
#include "dcmtk/oflog/consap.h"
#include "dcmtk/oflog/fileap.h"
#include "dcmtk/oflog/nullap.h"
#include "dcmtk/oflog/socketap.h"
#include "dcmtk/oflog/syslogap.h"
#include "dcmtk/oflog/helpers/loglog.h"
#include "dcmtk/oflog/helpers/threads.h"

#if defined (_WIN32)
#  if defined (DCMTK_LOG4CPLUS_HAVE_NT_EVENT_LOG)
#    include "dcmtk/oflog/ntelogap.h"
#  endif
#  if defined (DCMTK_LOG4CPLUS_HAVE_WIN32_CONSOLE)
#    include "dcmtk/oflog/winconap.h"
#  endif
#  include "dcmtk/oflog/windebap.h"
#endif


using namespace dcmtk::log4cplus;
using namespace dcmtk::log4cplus::helpers;
using namespace dcmtk::log4cplus::spi;


///////////////////////////////////////////////////////////////////////////////
// LOCAL file class definitions
///////////////////////////////////////////////////////////////////////////////

namespace dcmtk {

namespace log4cplus {

namespace spi {

    BaseFactory::~BaseFactory()
    { }


    AppenderFactory::AppenderFactory()
    { }

    AppenderFactory::~AppenderFactory()
    { }


    LayoutFactory::LayoutFactory()
    { }

    LayoutFactory::~LayoutFactory()
    { }


    FilterFactory::FilterFactory()
    { }

    FilterFactory::~FilterFactory()
    { }


    LoggerFactory::~LoggerFactory()
    { }


} // namespace spi


namespace
{


template <typename ProductFactoryBase>
class LocalFactoryBase
    : public ProductFactoryBase
{
public:
    LocalFactoryBase (tchar const * n)
        : name (n)
    { }

    virtual tstring getTypeName()
    {
        return name;
    }

private:
    tstring name;
};


template <typename LocalProduct, typename ProductFactoryBase>
class FactoryTempl
    : public LocalFactoryBase<ProductFactoryBase>
{
public:
    typedef typename ProductFactoryBase::ProductPtr ProductPtr;

    FactoryTempl (tchar const * n)
        : LocalFactoryBase<ProductFactoryBase> (n)
    { }

    virtual ProductPtr createObject (Properties const & props, tstring& error)
    {
        error.clear();
        ProductPtr ptr (new LocalProduct (props, error));
        if (!error.empty())
            return ProductPtr (0);
        return ptr;
    }
};


} // namespace


#define REG_PRODUCT(reg, productprefix, productname, productns, productfact) \
reg.put (                                                               \
    OFauto_ptr<productfact> (                                        \
        new FactoryTempl<productns productname, productfact> (          \
            DCMTK_LOG4CPLUS_TEXT(productprefix)                               \
            DCMTK_LOG4CPLUS_TEXT(#productname))))


#define REG_APPENDER(reg, appendername)                             \
REG_PRODUCT (reg, "log4cplus::", appendername, dcmtk::log4cplus::, AppenderFactory)

#define REG_LAYOUT(reg, layoutname)                                 \
REG_PRODUCT (reg, "log4cplus::", layoutname, dcmtk::log4cplus::, LayoutFactory)

#define REG_FILTER(reg, filtername)                                 \
REG_PRODUCT (reg, "log4cplus::spi::", filtername, spi::, FilterFactory)


void initializeFactoryRegistry();
void initializeFactoryRegistry()
{
    AppenderFactoryRegistry& reg = getAppenderFactoryRegistry();
    REG_APPENDER (reg, ConsoleAppender);
    REG_APPENDER (reg, NullAppender);
    REG_APPENDER (reg, FileAppender);
    REG_APPENDER (reg, RollingFileAppender);
    REG_APPENDER (reg, DailyRollingFileAppender);
    REG_APPENDER (reg, SocketAppender);
#if defined(_WIN32) && !defined(__MINGW32__)
#if defined(DCMTK_LOG4CPLUS_HAVE_NT_EVENT_LOG)
    REG_APPENDER (reg, NTEventLogAppender);
#  endif
#  if defined(DCMTK_LOG4CPLUS_HAVE_WIN32_CONSOLE)
    REG_APPENDER (reg, Win32ConsoleAppender);
#  endif
    REG_APPENDER (reg, Win32DebugAppender);
#elif defined(DCMTK_LOG4CPLUS_HAVE_SYSLOG_H)
    REG_APPENDER (reg, SysLogAppender);
#endif // defined(_WIN32) && !defined(__MINGW32__)

    LayoutFactoryRegistry& reg2 = getLayoutFactoryRegistry();
    REG_LAYOUT (reg2, SimpleLayout);
    REG_LAYOUT (reg2, TTCCLayout);
    REG_LAYOUT (reg2, PatternLayout);

    FilterFactoryRegistry& reg3 = getFilterFactoryRegistry();
    REG_FILTER (reg3, DenyAllFilter);
    REG_FILTER (reg3, LogLevelMatchFilter);
    REG_FILTER (reg3, LogLevelRangeFilter);
    REG_FILTER (reg3, StringMatchFilter);
}




///////////////////////////////////////////////////////////////////////////////
// public methods
///////////////////////////////////////////////////////////////////////////////

namespace spi
{


AppenderFactoryRegistry&
getAppenderFactoryRegistry()
{
    static AppenderFactoryRegistry singleton;
    return singleton;
}


LayoutFactoryRegistry&
getLayoutFactoryRegistry()
{
    static LayoutFactoryRegistry singleton;
    return singleton;
}


FilterFactoryRegistry&
getFilterFactoryRegistry()
{
    static FilterFactoryRegistry singleton;
    return singleton;
}


} // namespace spi


} // namespace log4cplus


} // namespace dcmtk
