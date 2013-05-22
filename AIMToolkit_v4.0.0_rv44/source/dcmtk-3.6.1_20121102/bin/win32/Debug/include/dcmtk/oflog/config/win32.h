/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/** @file */

#ifndef DCMTK_LOG4CPLUS_CONFIG_WIN32_HEADER_
#define DCMTK_LOG4CPLUS_CONFIG_WIN32_HEADER_

#ifdef _WIN32
#include <windows.h>

/* Define if you have the ftime function.  */
#define DCMTK_LOG4CPLUS_HAVE_FTIME 1

#if defined (_WIN32_WCE)
#  define DCMTK_LOG4CPLUS_DLLMAIN_HINSTANCE HANDLE
#  undef DCMTK_LOG4CPLUS_HAVE_NT_EVENT_LOG
#else
#  define DCMTK_LOG4CPLUS_DLLMAIN_HINSTANCE HINSTANCE
#  define DCMTK_LOG4CPLUS_HAVE_NT_EVENT_LOG
#  define DCMTK_LOG4CPLUS_HAVE_WIN32_CONSOLE
#endif

// This was moved to config.h
//#define DCMTK_LOG4CPLUS_EXPORT

#ifndef DCMTK_LOG4CPLUS_SINGLE_THREADED
#  define DCMTK_LOG4CPLUS_USE_WIN32_THREADS
#endif

#if defined(_MSC_VER)
  // Warning about: identifier was truncated to '255' characters in the debug information
#  pragma warning( disable : 4786 )
  // Warning about: <type1> needs to have dll-interface to be used by clients of class <type2>
#  pragma warning( disable : 4251 )

#  if _MSC_VER >= 1400
#    define DCMTK_LOG4CPLUS_WORKING_LOCALE
#  endif

#endif


#endif // _WIN32
#endif // DCMTK_LOG4CPLUS_CONFIG_WIN32_HEADER_

