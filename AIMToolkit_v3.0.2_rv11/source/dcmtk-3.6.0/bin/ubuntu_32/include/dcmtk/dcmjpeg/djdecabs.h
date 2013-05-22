/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef DJDECABS_H
#define DJDECABS_H

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctypes.h"
#include "dcmtk/dcmjpeg/djutils.h" /* for enums */
#include "dcmtk/dcmimgle/diutils.h" /* for EP_Interpretation */

/** abstract base class for decompression classes.
 *  Implementations of this class must support suspended decompression
 *  in which compressed data for one frame is fed block by block
 *  into the decompression routine, see description below.
 */
class DJDecoder
{
public:

  /// default constructor
  DJDecoder()
  {
  }

  /// destructor
  virtual ~DJDecoder()
  {
  }

  /** initializes internal object structures.
   *  Must be called before a new frame is decompressed.
   *  @return EC_Normal if successful, an error code otherwise
   */
  virtual OFCondition init() = 0;

  /** suspended decompression routine. Decompresses a JPEG frame
   *  until finished or out of data. Can be called with new data
   *  until a frame is complete.
   *  @param compressedFrameBuffer pointer to compressed input data, must not be NULL
   *  @param compressedFrameBufferSize size of buffer, in bytes
   *  @param uncompressedFrameBuffer pointer to uncompressed output data, must not be NULL.
   *     This buffer must not change between multiple decode() calls for a single frame.
   *  @param uncompressedFrameBufferSize size of buffer, in words???
   *     Buffer must be large enough to contain a complete frame.
   *  @param isSigned OFTrue, if uncompressed pixel data is signed, OFFalse otherwise
   *  @return EC_Normal if successful, EC_Suspend if more data is needed, an error code otherwise.
   */
  virtual OFCondition decode(
    Uint8 *compressedFrameBuffer,
    Uint32 compressedFrameBufferSize,
    Uint8 *uncompressedFrameBuffer,
    Uint32 uncompressedFrameBufferSize,
    OFBool isSigned) = 0;

  /** returns the number of bytes per sample that will be written when decoding.
   */
  virtual Uint16 bytesPerSample() const = 0;

  /** after successful compression,
   *  returns the color model of the decompressed image
   */
  virtual EP_Interpretation getDecompressedColorModel() const = 0;

};

#endif

/*
 * CVS/RCS Log
 * $Log: djdecabs.h,v $
 * Revision 1.4  2010-10-14 13:17:17  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.3  2005-12-08 16:59:14  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.2  2005/11/30 14:12:27  onken
 * Added decode() parameter denoting whether input is signed or unsigned
 *
 * Revision 1.1  2001/11/13 15:56:18  meichel
 * Initial release of module dcmjpeg
 *
 *
 */
