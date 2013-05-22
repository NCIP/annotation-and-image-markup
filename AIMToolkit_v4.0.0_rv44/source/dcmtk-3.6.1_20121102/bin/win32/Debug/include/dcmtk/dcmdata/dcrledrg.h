/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef DCRLEDRG_H
#define DCRLEDRG_H

#include "dcmtk/config/osconfig.h"
#include "dcmtk/ofstd/oftypes.h"    /* for OFBool */
#include "dcmtk/dcmdata/dcdefine.h"

class DcmRLECodecParameter;
class DcmRLECodecDecoder;

/** singleton class that registers an RLE decoder.
 */
class DCMTK_DCMDATA_EXPORT DcmRLEDecoderRegistration
{
public:
  /** registers RLE decoder.
   *  If already registered, call is ignored unless cleanup() has
   *  been performed before.
   *  @param pCreateSOPInstanceUID flag indicating whether or not
   *    a new SOP Instance UID should be assigned upon decompression.
   *  @param pReverseDecompressionByteOrder flag indicating whether the byte order should
   *    be reversed upon decompression. Needed to correctly decode some incorrectly encoded
   *    images with more than one byte per sample.
   */
  static void registerCodecs(
    OFBool pCreateSOPInstanceUID = OFFalse,
    OFBool pReverseDecompressionByteOrder = OFFalse);

  /** deregisters decoder.
   *  Attention: Must not be called while other threads might still use
   *  the registered codecs, e.g. because they are currently decoding
   *  DICOM data sets through dcmdata.
   */
  static void cleanup();

private:

  /// private undefined copy constructor
  DcmRLEDecoderRegistration(const DcmRLEDecoderRegistration&);

  /// private undefined copy assignment operator
  DcmRLEDecoderRegistration& operator=(const DcmRLEDecoderRegistration&);

  /// flag indicating whether the decoder is already registered.
  static OFBool registered;

  /// pointer to codec parameter
  static DcmRLECodecParameter *cp;

  /// pointer to RLE decoder
  static DcmRLECodecDecoder *codec;

  // dummy friend declaration to prevent gcc from complaining
  // that this class only defines private constructors and has no friends.
  friend class DcmRLEDecoderRegistrationDummyFriend;

};

#endif
