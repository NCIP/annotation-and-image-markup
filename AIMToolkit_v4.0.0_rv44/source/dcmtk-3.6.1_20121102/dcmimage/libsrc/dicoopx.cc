/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"

#include "dcmtk/dcmimage/dicoopx.h"
#include "dcmtk/dcmimgle/dipixel.h"


/*----------------*
 *  constructors  *
 *----------------*/

DiColorOutputPixel::DiColorOutputPixel(const DiPixel *pixel,
                                       const unsigned long size,
                                       const unsigned long frame)
  : Count(0),
    FrameSize(size)
{
    if (pixel != NULL)
    {
        if (pixel->getCount() > frame * size)
            Count = pixel->getCount() - frame * size;       // number of pixels remaining for this 'frame'
    }
    if (Count > FrameSize)
        Count = FrameSize;                                  // cut off at frame 'size'
}


/*--------------*
 *  destructor  *
 *--------------*/

DiColorOutputPixel::~DiColorOutputPixel()
{
}
