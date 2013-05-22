/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef DCMTK_LOG4CPLUS_CONFIG_HXX
#define DCMTK_LOG4CPLUS_CONFIG_HXX

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#include "dcmtk/ofstd/ofdefine.h"     /* We need DCMTK_DECL_EXPORT/_IMPORT */

#if defined (_WIN32)
#  include "dcmtk/oflog/config/win32.h"
#elif (defined(__MWERKS__) && defined(__MACOS__))
#  include "dcmtk/oflog/config/macosx.h"
#else
#  include "dcmtk/oflog/config/defines.h"
#endif

#if !defined(_WIN32)
#  if !defined(DCMTK_LOG4CPLUS_SINGLE_THREADED)
#    define DCMTK_LOG4CPLUS_USE_PTHREADS
#  endif
#  if defined (DCMTK_INSIDE_LOG4CPLUS)
#    define DCMTK_LOG4CPLUS_EXPORT DCMTK_LOG4CPLUS_DECLSPEC_EXPORT
#  else
#    define DCMTK_LOG4CPLUS_EXPORT DCMTK_LOG4CPLUS_DECLSPEC_IMPORT
#  endif // defined (DCMTK_INSIDE_LOG4CPLUS)
#endif // !_WIN32

#undef DCMTK_LOG4CPLUS_EXPORT
#ifdef oflog_EXPORTS
#define DCMTK_LOG4CPLUS_EXPORT DCMTK_DECL_EXPORT
#else
#define DCMTK_LOG4CPLUS_EXPORT DCMTK_DECL_IMPORT
#endif

#include "dcmtk/oflog/helpers/threadcf.h"


#endif // DCMTK_LOG4CPLUS_CONFIG_HXX
