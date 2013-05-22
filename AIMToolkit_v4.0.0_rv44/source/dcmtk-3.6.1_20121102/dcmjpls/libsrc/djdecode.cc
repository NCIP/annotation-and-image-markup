/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmjpls/djdecode.h"
#include "dcmtk/dcmdata/dccodec.h"  /* for DcmCodecStruct */
#include "dcmtk/dcmjpls/djcparam.h"
#include "dcmtk/dcmjpls/djcodecd.h"

// initialization of static members
OFBool DJLSDecoderRegistration::registered_                            = OFFalse;
DJLSCodecParameter *DJLSDecoderRegistration::cp_                       = NULL;
DJLSLosslessDecoder *DJLSDecoderRegistration::losslessdecoder_         = NULL;
DJLSNearLosslessDecoder *DJLSDecoderRegistration::nearlosslessdecoder_ = NULL;

void DJLSDecoderRegistration::registerCodecs(
    JLS_UIDCreation uidcreation,
    JLS_PlanarConfiguration planarconfig,
    OFBool ignoreOffsetTable)
{
  if (! registered_)
  {
    cp_ = new DJLSCodecParameter(uidcreation, planarconfig, ignoreOffsetTable);
    if (cp_)
    {
      losslessdecoder_ = new DJLSLosslessDecoder();
      if (losslessdecoder_) DcmCodecList::registerCodec(losslessdecoder_, NULL, cp_);

      nearlosslessdecoder_ = new DJLSNearLosslessDecoder();
      if (nearlosslessdecoder_) DcmCodecList::registerCodec(nearlosslessdecoder_, NULL, cp_);
      registered_ = OFTrue;
    }
  }
}

void DJLSDecoderRegistration::cleanup()
{
  if (registered_)
  {
    DcmCodecList::deregisterCodec(losslessdecoder_);
    DcmCodecList::deregisterCodec(nearlosslessdecoder_);
    delete losslessdecoder_;
    delete nearlosslessdecoder_;
    delete cp_;
    registered_ = OFFalse;
#ifdef DEBUG
    // not needed but useful for debugging purposes
    losslessdecoder_ = NULL;
    nearlosslessdecoder_ = NULL;
    cp_      = NULL;
#endif
  }
}

OFString DJLSDecoderRegistration::getLibraryVersionString()
{
    return DCMJPLS_CHARLS_VERSION_STRING;
}
