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
#include "jlossy16.h"
#include "jlossls16.h"


/*
 * Initialize the compression codec.
 * This is called only once, during master selection.
 */

GLOBAL(void)
jinit_c_codec (j_compress_ptr cinfo)
{
  if (cinfo->process == JPROC_LOSSLESS) {
#ifdef C_LOSSLESS_SUPPORTED
    jinit_lossless_c_codec(cinfo);
#else
    ERREXIT(cinfo, JERR_NOT_COMPILED);
#endif
  } else
    jinit_lossy_c_codec(cinfo);
}


/*
 * Initialize the decompression codec.
 * This is called only once, during master selection.
 */

GLOBAL(void)
jinit_d_codec (j_decompress_ptr cinfo)
{
  if (cinfo->process == JPROC_LOSSLESS) {
#ifdef D_LOSSLESS_SUPPORTED
    jinit_lossless_d_codec(cinfo);
#else
    ERREXIT(cinfo, JERR_NOT_COMPILED);
#endif
  } else
    jinit_lossy_d_codec(cinfo);
}
