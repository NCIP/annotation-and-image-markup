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
#include "jlossls8.h"		/* Private declarations for lossless codec */


#ifdef C_LOSSLESS_SUPPORTED

METHODDEF(void)
simple_downscale(j_compress_ptr cinfo,
		 JSAMPROW input_buf, JSAMPROW output_buf, JDIMENSION width)
{
  /* j_lossless_c_ptr losslsc = (j_lossless_c_ptr) cinfo->codec; */
  unsigned int xindex;
  SHIFT_TEMPS

  for (xindex = 0; xindex < width; xindex++)
    output_buf[xindex] = (JSAMPLE) RIGHT_SHIFT(GETJSAMPLE(input_buf[xindex]),
					       cinfo->Al);
}


METHODDEF(void)
noscale(j_compress_ptr cinfo,
	JSAMPROW input_buf, JSAMPROW output_buf, JDIMENSION width)
{
  MEMCOPY(output_buf, input_buf, width * SIZEOF(JSAMPLE));
  return;
}


METHODDEF(void)
scaler_start_pass (j_compress_ptr cinfo)
{
  j_lossless_c_ptr losslsc = (j_lossless_c_ptr) cinfo->codec;

  /* Set scaler function based on Pt */
  if (cinfo->Al)
    losslsc->scaler_scale = simple_downscale;
  else
    losslsc->scaler_scale = noscale;
}


GLOBAL(void)
jinit_c_scaler (j_compress_ptr cinfo)
{
  j_lossless_c_ptr losslsc = (j_lossless_c_ptr) cinfo->codec;

  losslsc->scaler_start_pass = scaler_start_pass;
}

#endif /* C_LOSSLESS_SUPPORTED */
