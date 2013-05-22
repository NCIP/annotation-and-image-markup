/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#ifndef DICOSCT_H
#define DICOSCT_H

#include "dcmtk/config/osconfig.h"

#include "dcmtk/dcmimage/dicopxt.h"
#include "dcmtk/dcmimgle/discalet.h"


/*---------------------*
 *  class declaration  *
 *---------------------*/

/** Template class to scale color images (on pixel data level).
 */
template<class T>
class DiColorScaleTemplate
  : public DiColorPixelTemplate<T>,
    protected DiScaleTemplate<T>
{

 public:

    /** constructor
     *
     ** @param  pixel        pointer to intermediate pixel representation
     *  @param  columns      width of source image
     *  @param  rows         height of source image
     *  @param  left_pos     left coordinate of clipping area
     *  @param  top_pos      top coordinate of clipping area
     *  @param  src_cols     width of clipping area
     *  @param  src_rows     height of clipping area
     *  @param  dest_cols    width of destination image (scaled image)
     *  @param  dest_rows    height of destination image
     *  @param  frames       number of frames
     *  @param  bits         number of bits per plane/pixel
     *  @param  interpolate  use of interpolation when scaling
     */
    DiColorScaleTemplate(const DiColorPixel *pixel,
                         const Uint16 columns,
                         const Uint16 rows,
                         const signed long left_pos,
                         const signed long top_pos,
                         const Uint16 src_cols,
                         const Uint16 src_rows,
                         const Uint16 dest_cols,
                         const Uint16 dest_rows,
                         const Uint32 frames,
                         const int bits,
                         const int interpolate)
      : DiColorPixelTemplate<T>(pixel, OFstatic_cast(unsigned long, dest_cols) * OFstatic_cast(unsigned long, dest_rows) * frames),
        DiScaleTemplate<T>(3, columns, rows, left_pos, top_pos, src_cols, src_rows, dest_cols, dest_rows, frames, bits)
   {
        if ((pixel != NULL) && (pixel->getCount() > 0))
        {
            if (pixel->getCount() == OFstatic_cast(unsigned long, columns) * OFstatic_cast(unsigned long, rows) * frames)
                scale(OFstatic_cast(const T **, OFconst_cast(void *, pixel->getData())), interpolate);
            else {
                DCMIMAGE_WARN("could not scale image ... corrupted data");
            }
        }
    }

    /** destructor
     */
    virtual ~DiColorScaleTemplate()
    {
    }


 private:

    /** scale pixel data
     *
     ** @param  pixel        pointer to pixel data (3 components9 to be scaled
     *  @param  interpolate  use of interpolation when scaling
     */
    inline void scale(const T *pixel[3],
                      const int interpolate)
    {
        if (this->Init(pixel))
            this->scaleData(pixel, this->Data, interpolate);
    }
};


#endif
