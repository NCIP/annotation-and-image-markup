/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#ifndef DICOFLT_H
#define DICOFLT_H

#include "dcmtk/config/osconfig.h"

#include "dcmtk/dcmimage/dicopxt.h"
#include "dcmtk/dcmimgle/diflipt.h"


/*---------------------*
 *  class declaration  *
 *---------------------*/

/** Template class to flip color images (on pixel data level)
 *  horizontally and vertically
 */
template<class T>
class DiColorFlipTemplate
  : public DiColorPixelTemplate<T>,
    protected DiFlipTemplate<T>
{

 public:

    /** constructor
     *
     ** @param  pixel    pointer to intermediate pixel representation
     *  @param  columns  number of columns
     *  @param  rows     number of rows
     *  @param  frames   number of frames
     *  @param  horz     flip horizontally if true
     *  @param  vert     flip vertically if true
     */
    DiColorFlipTemplate(const DiColorPixel *pixel,
                        const Uint16 columns,
                        const Uint16 rows,
                        const Uint32 frames,
                        const int horz,
                        const int vert)
      : DiColorPixelTemplate<T>(pixel, OFstatic_cast(unsigned long, columns) * OFstatic_cast(unsigned long, rows) * frames),
        DiFlipTemplate<T>(3, columns, rows, frames)
    {
        if ((pixel != NULL) && (pixel->getCount() > 0))
        {
            if (pixel->getCount() == OFstatic_cast(unsigned long, columns) * OFstatic_cast(unsigned long, rows) * frames)
                flip(OFstatic_cast(const T **, OFconst_cast(void *, pixel->getData())), horz, vert);
            else {
                DCMIMAGE_WARN("could not flip image ... corrupted data");
            }
        }
    }

    /** destructor
     */
    ~DiColorFlipTemplate()
    {
    }


 private:

    /** choose flipping algorithm depending on given parameters
     *
     ** @param  pixel  pointer to pixel data (3 components) which should be flipped
     *  @param  horz   flip horizontally if true
     *  @param  vert   flip vertically if true
     */
    inline void flip(const T *pixel[3],
                     const int horz,
                     const int vert)
    {
        if (this->Init(pixel))
        {
            if (horz && vert)
                this->flipHorzVert(pixel, this->Data);
            else if (horz)
                this->flipHorz(pixel, this->Data);
            else if (vert)
                this->flipVert(pixel, this->Data);
        }
    }
};


#endif
