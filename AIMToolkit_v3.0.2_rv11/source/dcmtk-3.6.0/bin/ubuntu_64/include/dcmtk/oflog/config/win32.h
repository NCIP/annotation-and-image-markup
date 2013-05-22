/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/** @file */

#ifndef LOG4CPLUS_CONFIG_WIN32_HEADER_
#define LOG4CPLUS_CONFIG_WIN32_HEADER_

#ifdef _WIN32
#include <windows.h>

/* Define if you have the ftime function.  */
#define LOG4CPLUS_HAVE_FTIME 1

#if defined (_WIN32_WCE)
#  define LOG4CPLUS_DLLMAIN_HINSTANCE HANDLE
#  undef LOG4CPLUS_HAVE_NT_EVENT_LOG
#else
#  define LOG4CPLUS_DLLMAIN_HINSTANCE HINSTANCE
#  define LOG4CPLUS_HAVE_NT_EVENT_LOG
#  define LOG4CPLUS_HAVE_WIN32_CONSOLE
#endif

// log4cplus_EXPORTS is used by the CMake build system.  DLL_EXPORT is
// used by the autotools build system.
#if defined (log4cplus_EXPORTS) || defined (DLL_EXPORT)
#  undef LOG4CPLUS_BUILD_DLL
#  define LOG4CPLUS_BUILD_DLL
#endif

#if ! defined (LOG4CPLUS_BUILD_DLL)
#  undef LOG4CPLUS_STATIC
#  define LOG4CPLUS_STATIC
#endif

#if defined (LOG4CPLUS_STATIC) && defined (LOG4CPLUS_BUILD_DLL)
#  error LOG4CPLUS_STATIC and LOG4CPLUS_BUILD_DLL cannot be defined both.
#endif

#if defined (LOG4CPLUS_BUILD_DLL)
#  if defined (INSIDE_LOG4CPLUS)
#    define LOG4CPLUS_EXPORT __declspec(dllexport)
#  else
#    define LOG4CPLUS_EXPORT __declspec(dllimport)
#  endif
#else
#  define LOG4CPLUS_EXPORT
#endif

#ifndef LOG4CPLUS_SINGLE_THREADED
#  define LOG4CPLUS_USE_WIN32_THREADS
#endif

#if defined(_MSC_VER)
  // Warning about: identifier was truncated to '255' characters in the debug information
#  pragma warning( disable : 4786 )
  // Warning about: <type1> needs to have dll-interface to be used by clients of class <type2>
#  pragma warning( disable : 4251 )

#  if _MSC_VER >= 1400
#    define LOG4CPLUS_WORKING_LOCALE
#  endif

#endif


#endif // _WIN32
#endif // LOG4CPLUS_CONFIG_WIN32_HEADER_

