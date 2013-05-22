/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef DJENCABS_H
#define DJENCABS_H

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctypes.h"
#include "dcmtk/dcmimgle/diutils.h" /* for EP_Interpretation */
#include "dcmtk/dcmjpeg/djutils.h" /* for enums */

/** abstract base class for compression classes. 
 */
class DJEncoder
{
public: 

  /// default constructor
  DJEncoder()
  {
  }

  /// destructor
  virtual ~DJEncoder()
  {
  }

  /** single frame compression routine for 16-bit raw pixel data.
   *  May only be called if bytesPerSample() == 2.
   *  @param columns columns of frame
   *  @param rows rows of frame
   *  @param interpr photometric interpretation of input frame
   *  @param samplesPerPixel samples per pixel of input frame
   *  @param image_buffer pointer to frame buffer
   *  @param to compressed frame returned in this parameter upon success
   *  @param length length of compressed frame (in bytes) returned in this parameter
   *    upon success; length guaranteed to be always even.
   *  @return EC_Normal if successful, an error code otherwise.
   */
  virtual OFCondition encode(
    Uint16 columns,
    Uint16 rows,
    EP_Interpretation interpr,
    Uint16 samplesPerPixel,
    Uint16 *image_buffer,
    Uint8 *&to,
    Uint32 &length) = 0;

  /** single frame compression routine for 8-bit raw pixel data.
   *  May only be called if bytesPerSample() == 1.
   *  @param columns columns of frame
   *  @param rows rows of frame
   *  @param interpr photometric interpretation of input frame
   *  @param samplesPerPixel samples per pixel of input frame
   *  @param image_buffer pointer to frame buffer
   *  @param to compressed frame returned in this parameter upon success
   *  @param length length of compressed frame (in bytes) returned in this parameter
   *    upon success; length guaranteed to be always even.
   *  @return EC_Normal if successful, an error code otherwise.
   */
  virtual OFCondition encode(
    Uint16 columns,
    Uint16 rows,
    EP_Interpretation interpr,
    Uint16 samplesPerPixel,
    Uint8 *image_buffer,
    Uint8 *&to,
    Uint32 &length) = 0;

  /** returns the number of bytes per sample that will be expected when encoding.
   */
  virtual Uint16 bytesPerSample() const = 0;

  /** returns the number of bits per sample that will be expected when encoding.
   */
  virtual Uint16 bitsPerSample() const = 0;

};


#endif

/*
 * CVS/RCS Log
 * $Log: djencabs.h,v $
 * Revision 1.3  2010-10-14 13:17:17  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.2  2005-12-08 16:59:28  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.1  2001/11/13 15:56:25  meichel
 * Initial release of module dcmjpeg
 *
 *
 */
