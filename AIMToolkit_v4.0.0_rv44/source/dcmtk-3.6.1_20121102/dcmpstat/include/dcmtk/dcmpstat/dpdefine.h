/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#ifndef DPDEFINE_H
#define DPDEFINE_H

#include "dcmtk/config/osconfig.h"

#include "dcmtk/ofstd/ofdefine.h"


#ifdef dcmpstat_EXPORTS
#define DCMTK_DCMPSTAT_EXPORT DCMTK_DECL_EXPORT
#else
#define DCMTK_DCMPSTAT_EXPORT DCMTK_DECL_IMPORT
#endif


#endif
