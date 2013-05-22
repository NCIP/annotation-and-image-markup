/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef DJDECBAS_H
#define DJDECBAS_H

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmjpeg/djcodecd.h" /* for class DJCodecDecoder */

/** Decoder class for JPEG Baseline (lossy, 8-bit)
 */
class DJDecoderBaseline : public DJCodecDecoder
{
public: 

  /// default constructor
  DJDecoderBaseline();

  /// destructor
  virtual ~DJDecoderBaseline();

  /** returns the transfer syntax that this particular codec
   *  is able to encode and decode.
   *  @return supported transfer syntax
   */
  virtual E_TransferSyntax supportedTransferSyntax() const;

private:

  /** creates an instance of the compression library to be used for decoding.
   *  @param toRepParam representation parameter passed to decode()
   *  @param cp codec parameter passed to decode()
   *  @param bitsPerSample bits per sample for the image data
   *  @param isYBR flag indicating whether DICOM photometric interpretation is YCbCr
   *  @return pointer to newly allocated decoder object
   */
  virtual DJDecoder *createDecoderInstance(
    const DcmRepresentationParameter * toRepParam,
    const DJCodecParameter *cp,
    Uint8 bitsPerSample,
    OFBool isYBR) const;

};

#endif

/*
 * CVS/RCS Log
 * $Log: djdecbas.h,v $
 * Revision 1.3  2010-10-14 13:17:17  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.2  2005-12-08 16:59:15  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.1  2001/11/13 15:56:18  meichel
 * Initial release of module dcmjpeg
 *
 *
 */
