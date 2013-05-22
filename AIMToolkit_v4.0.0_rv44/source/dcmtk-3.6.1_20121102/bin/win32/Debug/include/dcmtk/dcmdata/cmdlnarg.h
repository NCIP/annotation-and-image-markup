/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef CMDLNARG_H
#define CMDLNARG_H

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#include "dcmtk/dcmdata/dcdefine.h"

/** this function is used on certain operating systems (in particular, classic MacOS)
 *  and allows command line arguments to be input from stdin.
 *  MT level: Thread unsafe!
 *  @param argc the argc parameter of main() is passed in this parameter
 *  @param argv the argv parameter of main() is passed in this parameter
 *  @param progname program name
 */
DCMTK_DCMDATA_EXPORT void prepareCmdLineArgs(int& argc, char** argv, const char* progname = "aProgram");

#ifdef HAVE_WINDOWS_H

/** this function is used on certain operating systems (in particular, classic MacOS)
 *  and allows command line arguments to be input from stdin.
 *  MT level: Thread unsafe!
 *  This is a Windows-specific version supporting the wide character encoding (UTF-16).
 *  @param argc the argc parameter of main() is passed in this parameter (not used)
 *  @param argv the argv parameter of main() is passed in this parameter (not used)
 *  @param progname program name (not used)
 */
DCMTK_DCMDATA_EXPORT void prepareCmdLineArgs(int& argc, wchar_t** argv, const char* progname = "aProgram");

#endif  // HAVE_WINDOWS_H

#endif
