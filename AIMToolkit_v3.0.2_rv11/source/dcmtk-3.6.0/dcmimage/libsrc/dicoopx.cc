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


/*
 *
 * CVS/RCS Log:
 * $Log: dicoopx.cc,v $
 * Revision 1.13  2010-10-14 13:14:14  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.12  2005/12/08 15:42:22  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.11  2003/12/23 10:54:28  joergr
 * Updated copyright header.
 *
 * Revision 1.10  2001/06/01 15:49:35  meichel
 * Updated copyright header
 *
 * Revision 1.9  2000/03/08 16:21:56  meichel
 * Updated copyright header.
 *
 * Revision 1.8  1999/07/23 13:18:49  joergr
 * Enhanced handling of corrupted pixel data (wrong length).
 *
 * Revision 1.7  1999/04/29 09:32:33  joergr
 * Moved color related image files back to non-public part.
 *
 * Revision 1.1  1999/04/28 14:57:58  joergr
 * Moved files from dcmimage module to dcmimgle to support new pastel color
 * output format.
 *
 * Revision 1.5  1999/01/20 14:50:26  joergr
 * Replaced invocation of getCount() by member variable Count where possible.
 *
 * Revision 1.4  1998/11/27 14:27:58  joergr
 * Added copyright message.
 *
 * Revision 1.3  1998/05/11 14:52:26  joergr
 * Added CVS/RCS header to each file.
 *
 *
 */
