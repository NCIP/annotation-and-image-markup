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
