/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#define JPEG_INTERNALS
#include "jinclude8.h"
#include "jpeglib8.h"
#include "jlossy8.h"


/*
 * Initialize for a processing pass.
 */

METHODDEF(void)
start_pass (j_compress_ptr cinfo, J_BUF_MODE pass_mode)
{
  j_lossy_c_ptr lossyc = (j_lossy_c_ptr) cinfo->codec;

  (*lossyc->fdct_start_pass) (cinfo);
  (*lossyc->coef_start_pass) (cinfo, pass_mode);
}


/*
 * Initialize the lossy compression codec.
 * This is called only once, during master selection.
 */

GLOBAL(void)
jinit_lossy_c_codec (j_compress_ptr cinfo)
{
  j_lossy_c_ptr lossyc;

  /* Create subobject in permanent pool */
  lossyc = (j_lossy_c_ptr)
    (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT,
				SIZEOF(jpeg_lossy_c_codec));
  cinfo->codec = (struct jpeg_c_codec *) lossyc;

  /* Initialize sub-modules */

  /* Forward DCT */
  jinit_forward_dct(cinfo);
  /* Entropy encoding: either Huffman or arithmetic coding. */
  if (cinfo->arith_code) {
#ifdef WITH_ARITHMETIC_PATCH
    jinit_arith_encoder(cinfo);
#else
    ERREXIT(cinfo, JERR_ARITH_NOTIMPL);
#endif
  } else {
    if (cinfo->process == JPROC_PROGRESSIVE) {
#ifdef C_PROGRESSIVE_SUPPORTED
      jinit_phuff_encoder(cinfo);
#else
      ERREXIT(cinfo, JERR_NOT_COMPILED);
#endif
    } else
      jinit_shuff_encoder(cinfo);
  }

  /* Need a full-image coefficient buffer in any multi-pass mode. */
  jinit_c_coef_controller(cinfo,
			  (boolean) (cinfo->num_scans > 1 ||
				     cinfo->optimize_coding));

  /* Initialize method pointers.
   *
   * Note: entropy_start_pass and entropy_finish_pass are assigned in
   * jcshuff.c or jcphuff.c and compress_data is assigned in jccoefct.c.
   */
  lossyc->pub.start_pass = start_pass;
}
