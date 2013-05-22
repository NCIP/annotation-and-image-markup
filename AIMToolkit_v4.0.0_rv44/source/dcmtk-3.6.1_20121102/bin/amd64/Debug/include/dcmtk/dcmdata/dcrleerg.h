/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef DCRLEERG_H
#define DCRLEERG_H

#include "dcmtk/config/osconfig.h"
#include "dcmtk/ofstd/oftypes.h"    /* for OFBool */
#include "dcmtk/dcmdata/dcdefine.h"

class DcmRLECodecParameter;
class DcmRLECodecEncoder;

/** singleton class that registers an RLE encoder.
 */
class DCMTK_DCMDATA_EXPORT DcmRLEEncoderRegistration
{
public:

  /** registers RLE encoder.
   *  If already registered, call is ignored unless cleanup() has
   *  been performed before.
   *  @param pCreateSOPInstanceUID flag indicating whether or not
   *    a new SOP Instance UID should be assigned upon compression.
   *  @param pFragmentSize maximum fragment size (in kbytes) for compression, 0 for unlimited.
   *  @param pCreateOffsetTable create offset table during image compression?
   *  @param pConvertToSC flag indicating whether image should be converted to
   *    Secondary Capture upon compression
   */
  static void registerCodecs(
    OFBool pCreateSOPInstanceUID = OFFalse,
    Uint32 pFragmentSize = 0,
    OFBool pCreateOffsetTable = OFTrue,
    OFBool pConvertToSC = OFFalse);

  /** deregisters encoder.
   *  Attention: Must not be called while other threads might still use
   *  the registered codecs, e.g. because they are currently encoding
   *  DICOM data sets through dcmdata.
   */
  static void cleanup();

private:

  /// private undefined copy constructor
  DcmRLEEncoderRegistration(const DcmRLEEncoderRegistration&);

  /// private undefined copy assignment operator
  DcmRLEEncoderRegistration& operator=(const DcmRLEEncoderRegistration&);

  /// flag indicating whether the encoder is already registered.
  static OFBool registered;

  /// pointer to codec parameter
  static DcmRLECodecParameter *cp;

  /// pointer to RLE encoder
  static DcmRLECodecEncoder *codec;

  // dummy friend declaration to prevent gcc from complaining
  // that this class only defines private constructors and has no friends.
  friend class DcmRLEEncoderRegistrationDummyFriend;

};

#endif
