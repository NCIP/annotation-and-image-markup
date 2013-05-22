/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/oflog/config.h"
#include "dcmtk/oflog/logger.h"
#include "dcmtk/oflog/ndc.h"
#include "dcmtk/oflog/helpers/loglog.h"


// Forward Declarations
namespace dcmtk
{

namespace log4cplus
{


void initializeFactoryRegistry();


void initializeLog4cplus();
void initializeLog4cplus()
{
    static bool initialized = false;
    if (initialized)
        return;

    helpers::LogLog::getLogLog();
    getLogLevelManager ();
    getNDC();
    Logger::getRoot();
    initializeFactoryRegistry();

    initialized = true;
}


} // namespace log4cplus

} // namespace dcmtk


#if defined (_WIN32) && defined (DCMTK_LOG4CPLUS_BUILD_DLL)

BOOL WINAPI DllMain(DCMTK_LOG4CPLUS_DLLMAIN_HINSTANCE hinstDLL,  // handle to DLL module
                    DWORD fdwReason,     // reason for calling function
                    LPVOID lpReserved )  // reserved
{
    // Perform actions based on the reason for calling.
    switch( fdwReason )
    {
        case DLL_PROCESS_ATTACH:
            dcmtk::log4cplus::initializeLog4cplus();
            break;

        case DLL_THREAD_ATTACH:
         // Do thread-specific initialization.
            break;

        case DLL_THREAD_DETACH:
         // Do thread-specific cleanup.
            break;

        case DLL_PROCESS_DETACH:
         // Perform any necessary cleanup.
            break;
    }

    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}

#else

namespace {

    class _static_log4cplus_initializer {
    public:
        _static_log4cplus_initializer() {
            dcmtk::log4cplus::initializeLog4cplus();
        }
    } static initializer;
}

#endif
