/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/** @file */

#ifndef DCMTK_LOG4CPLUS_CONFIG_MACOSX_HEADER_
#define DCMTK_LOG4CPLUS_CONFIG_MACOSX_HEADER_

#if (defined(__APPLE__) || (defined(__MWERKS__) && defined(__MACOS__)))

#define DCMTK_LOG4CPLUS_HAVE_GETTIMEOFDAY 1
#define socklen_t int

#endif // MACOSX
#endif // DCMTK_LOG4CPLUS_CONFIG_MACOSX_HEADER_
