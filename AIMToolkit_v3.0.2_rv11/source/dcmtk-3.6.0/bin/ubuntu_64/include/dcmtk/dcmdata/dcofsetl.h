/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef DCOFSETL_H
#define DCOFSETL_H

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */
#include "dcmtk/ofstd/oflist.h"      /* for class OFList<T> */

/** list of Uint32 values which are interpreted as the offsets
 *  in a Pixel Data offset table
 */
typedef OFList<Uint32> DcmOffsetList;

#endif

/*
 * CVS/RCS Log
 * $Log: dcofsetl.h,v $
 * Revision 1.4  2010-10-14 13:15:41  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.3  2009-11-04 09:58:07  uli
 * Switched to logging mechanism provided by the "new" oflog module
 *
 * Revision 1.2  2005-12-08 16:28:23  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.1  2002/05/24 14:51:43  meichel
 * Moved helper methods that are useful for different compression techniques
 *   from module dcmjpeg to module dcmdata
 *
 *
 */
