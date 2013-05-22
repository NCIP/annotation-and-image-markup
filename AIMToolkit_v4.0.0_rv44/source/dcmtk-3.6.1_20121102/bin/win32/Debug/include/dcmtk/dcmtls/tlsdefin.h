/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#ifndef TLSDEFIN_H
#define TLSDEFIN_H

#include "dcmtk/config/osconfig.h"

#include "dcmtk/ofstd/ofdefine.h"


#ifdef dcmtls_EXPORTS
#define DCMTK_DCMTLS_EXPORT DCMTK_DECL_EXPORT
#else
#define DCMTK_DCMTLS_EXPORT DCMTK_DECL_IMPORT
#endif


#endif
