/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef OFCAST_H
#define OFCAST_H

#include "dcmtk/config/osconfig.h"

#ifdef HAVE_CONST_CAST
#define OFconst_cast(x,y) (const_cast< x >(y))
#else
#define OFconst_cast(x,y) ((x)(y))
#endif

#ifdef HAVE_DYNAMIC_CAST
#define OFdynamic_cast(x,y) (dynamic_cast< x >(y))
#else
#define OFdynamic_cast(x,y) ((x)(y))
#endif

#ifdef HAVE_REINTERPRET_CAST
#define OFreinterpret_cast(x,y) (reinterpret_cast< x >(y))
#else
#define OFreinterpret_cast(x,y) ((x)(y))
#endif

#ifdef HAVE_STATIC_CAST
#define OFstatic_cast(x,y) (static_cast< x >(y))
#else
#define OFstatic_cast(x,y) ((x)(y))
#endif

#endif

/*
 * CVS/RCS Log:
 * $Log: ofcast.h,v $
 * Revision 1.3  2010-10-14 13:15:50  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.2  2005/12/08 16:05:47  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.1  2003/07/09 12:26:02  meichel
 * Added new header file ofcast.h which defines portable macros
 *   for new-style typecast operators
 *
 *
 */
