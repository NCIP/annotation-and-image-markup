/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmjpeg/djdecbas.h"
#include "dcmtk/dcmjpeg/djcparam.h"
#include "dcmtk/dcmjpeg/djrploss.h"

#include "dcmtk/dcmjpeg/djdijg8.h"


DJDecoderBaseline::DJDecoderBaseline()
: DJCodecDecoder()
{
}


DJDecoderBaseline::~DJDecoderBaseline()
{
}


E_TransferSyntax DJDecoderBaseline::supportedTransferSyntax() const
{
  return EXS_JPEGProcess1TransferSyntax;
}


DJDecoder *DJDecoderBaseline::createDecoderInstance(
    const DcmRepresentationParameter * /* toRepParam */,
    const DJCodecParameter *cp,
    Uint8 /* bitsPerSample */,
    OFBool isYBR) const
{
  return new DJDecompressIJG8Bit(*cp, isYBR);
}


/*
 * CVS/RCS Log
 * $Log: djdecbas.cc,v $
 * Revision 1.3  2010-10-14 13:14:21  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.2  2005-12-08 15:43:29  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.1  2001/11/13 15:58:25  meichel
 * Initial release of module dcmjpeg
 *
 *
 */
