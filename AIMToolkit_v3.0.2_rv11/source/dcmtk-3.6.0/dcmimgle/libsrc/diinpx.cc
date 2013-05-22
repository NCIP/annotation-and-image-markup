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


/*
 *
 * CVS/RCS Log:
 * $Log: diinpx.cc,v $
 * Revision 1.10  2010-10-14 13:14:18  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.9  2009-11-25 16:31:18  joergr
 * Adapted code for new approach to access individual frames of a DICOM image.
 *
 * Revision 1.8  2005/12/08 15:42:52  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.7  2003/12/08 17:43:04  joergr
 * Updated copyright header.
 *
 * Revision 1.6  2002/06/26 16:11:34  joergr
 * Enhanced handling of corrupted pixel data and/or length.
 *
 * Revision 1.5  2001/06/01 15:49:56  meichel
 * Updated copyright header
 *
 * Revision 1.4  2000/04/27 13:10:28  joergr
 * Dcmimgle library code now consistently uses ofConsole for error output.
 *
 * Revision 1.3  2000/03/08 16:24:29  meichel
 * Updated copyright header.
 *
 * Revision 1.2  1999/02/03 17:39:20  joergr
 * Added member variable and related methods to store number of bits used for
 * pixel data.
 *
 * Revision 1.1  1998/11/27 16:02:13  joergr
 * Added copyright message.
 *
 * Revision 1.2  1998/05/11 14:52:29  joergr
 * Added CVS/RCS header to each file.
 *
 *
 */
