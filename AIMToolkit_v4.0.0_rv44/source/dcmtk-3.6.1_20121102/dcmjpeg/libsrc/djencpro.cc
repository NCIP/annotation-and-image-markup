/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmjpeg/djencpro.h"
#include "dcmtk/dcmjpeg/djcparam.h"
#include "dcmtk/dcmjpeg/djrploss.h"
#include "dcmtk/dcmjpeg/djeijg8.h"
#include "dcmtk/dcmjpeg/djeijg12.h"


DJEncoderProgressive::DJEncoderProgressive()
: DJCodecEncoder()
{
}


DJEncoderProgressive::~DJEncoderProgressive()
{
}


E_TransferSyntax DJEncoderProgressive::supportedTransferSyntax() const
{
  return EXS_JPEGProcess10_12;
}


OFBool DJEncoderProgressive::isLosslessProcess() const
{
  return OFFalse;
}


void DJEncoderProgressive::createDerivationDescription(
  const DcmRepresentationParameter * toRepParam,
  const DJCodecParameter * /* cp */ ,
  Uint8 bitsPerSample,
  double ratio,
  OFString& derivationDescription) const
{
  DJ_RPLossy defaultRP;
  const DJ_RPLossy *rp = toRepParam ? (const DJ_RPLossy *)toRepParam : &defaultRP ;
  char buf[64];
 
  derivationDescription =  "Lossy compression with JPEG full progression ";
  if (bitsPerSample > 8) derivationDescription += "12 bit"; else derivationDescription += "8 bit";
  derivationDescription += ", IJG quality factor ";
  sprintf(buf, "%u", rp->getQuality());
  derivationDescription += buf;
  derivationDescription += ", compression ratio ";
  appendCompressionRatio(derivationDescription, ratio);
}


DJEncoder *DJEncoderProgressive::createEncoderInstance(
    const DcmRepresentationParameter * toRepParam,
    const DJCodecParameter *cp,
    Uint8 bitsPerSample) const
{
  DJ_RPLossy defaultRP;
  const DJ_RPLossy *rp = toRepParam ? (const DJ_RPLossy *)toRepParam : &defaultRP ;
  DJEncoder *result = NULL;
  if (bitsPerSample > 8)
    result = new DJCompressIJG12Bit(*cp, EJM_progressive, rp->getQuality());
    else result = new DJCompressIJG8Bit(*cp, EJM_progressive, rp->getQuality());
  return result;
}
