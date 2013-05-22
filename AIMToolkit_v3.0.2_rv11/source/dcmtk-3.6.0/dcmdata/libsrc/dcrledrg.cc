/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dcrledrg.h"

#include "dcmtk/dcmdata/dccodec.h"  /* for DcmCodecStruct */
#include "dcmtk/dcmdata/dcrleccd.h" /* for class DcmRLECodecDecoder */
#include "dcmtk/dcmdata/dcrlecp.h"  /* for class DcmRLECodecParameter */

// initialization of static members
OFBool DcmRLEDecoderRegistration::registered                  = OFFalse;
DcmRLECodecParameter *DcmRLEDecoderRegistration::cp           = NULL;
DcmRLECodecDecoder *DcmRLEDecoderRegistration::codec          = NULL;

void DcmRLEDecoderRegistration::registerCodecs(
    OFBool pCreateSOPInstanceUID,
    OFBool pReverseDecompressionByteOrder)
{
  if (! registered)
  {
    cp = new DcmRLECodecParameter(
      pCreateSOPInstanceUID,
      0, OFTrue, OFFalse,
      pReverseDecompressionByteOrder);
      
    if (cp)
    {
      codec = new DcmRLECodecDecoder();
      if (codec) DcmCodecList::registerCodec(codec, NULL, cp);
      registered = OFTrue;
    }
  }
}

void DcmRLEDecoderRegistration::cleanup()
{
  if (registered)
  {
    DcmCodecList::deregisterCodec(codec);
    delete codec;
    delete cp;
    registered = OFFalse;
#ifdef DEBUG
    // not needed but useful for debugging purposes
    codec  = NULL;
    cp     = NULL;
#endif
  }
}


/*
 * CVS/RCS Log
 * $Log: dcrledrg.cc,v $
 * Revision 1.5  2010-10-14 13:14:09  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.4  2009-11-04 09:58:10  uli
 * Switched to logging mechanism provided by the "new" oflog module
 *
 * Revision 1.3  2005-12-08 15:41:33  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.2  2005/07/26 17:08:35  meichel
 * Added option to RLE decoder that allows to correctly decode images with
 *   incorrect byte order of byte segments (LSB instead of MSB).
 *
 * Revision 1.1  2002/06/06 14:52:42  meichel
 * Initial release of the new RLE codec classes
 *   and the dcmcrle/dcmdrle tools in module dcmdata
 *
 *
 */
