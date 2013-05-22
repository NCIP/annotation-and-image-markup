/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#ifndef WLDEFINE_H
#define WLDEFINE_H

#include "dcmtk/config/osconfig.h"

#include "dcmtk/ofstd/ofdefine.h"


#ifdef dcmwlm_EXPORTS
#define DCMTK_DCMWLM_EXPORT DCMTK_DECL_EXPORT
#else
#define DCMTK_DCMWLM_EXPORT DCMTK_DECL_IMPORT
#endif


#endif
