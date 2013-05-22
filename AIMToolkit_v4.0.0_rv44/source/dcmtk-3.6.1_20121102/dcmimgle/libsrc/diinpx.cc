/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"

#include "dcmtk/dcmimgle/diinpx.h"


/*----------------*
 *  constructors  *
 *----------------*/

DiInputPixel::DiInputPixel(const unsigned int bits,
                           const unsigned long first,
                           const unsigned long number,
                           const unsigned long fsize)
  : Count(0),
    Bits(bits),
    FirstFrame(first),
    NumberOfFrames(number),
    FrameSize(fsize),
    PixelStart(first * fsize),
    PixelCount(number * fsize),
    ComputedCount(number * fsize),
    AbsMinimum(0),
    AbsMaximum(0)
{
}


/*--------------*
 *  destructor  *
 *--------------*/

DiInputPixel::~DiInputPixel()
{
}
