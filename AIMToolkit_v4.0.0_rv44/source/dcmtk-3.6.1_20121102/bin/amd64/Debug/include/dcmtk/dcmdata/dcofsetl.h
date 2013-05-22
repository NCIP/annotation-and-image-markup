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
