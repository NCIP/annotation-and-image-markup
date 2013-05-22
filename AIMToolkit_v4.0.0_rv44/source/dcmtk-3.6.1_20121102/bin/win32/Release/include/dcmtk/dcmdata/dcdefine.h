/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#ifndef DCDEFINE_H
#define DCDEFINE_H

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#include "dcmtk/ofstd/ofdefine.h"


#ifdef dcmdata_EXPORTS
#define DCMTK_DCMDATA_EXPORT DCMTK_DECL_EXPORT
#else
#define DCMTK_DCMDATA_EXPORT DCMTK_DECL_IMPORT
#endif


#endif // DCDEFINE_H
