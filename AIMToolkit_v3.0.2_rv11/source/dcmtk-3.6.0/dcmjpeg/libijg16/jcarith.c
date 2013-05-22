/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#define JPEG_INTERNALS
#include "jinclude16.h"
#include "jpeglib16.h"


/*
 * Module initialization routine for arithmetic entropy encoding.
 */

GLOBAL(void)
jinit_arith_encoder (j_compress_ptr cinfo)
{
  ERREXIT(cinfo, JERR_ARITH_NOTIMPL);
}
