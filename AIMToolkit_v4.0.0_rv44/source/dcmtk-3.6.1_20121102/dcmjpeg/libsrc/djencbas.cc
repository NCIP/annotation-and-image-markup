/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmjpeg/djencbas.h"
#include "dcmtk/dcmjpeg/djcparam.h"
#include "dcmtk/dcmjpeg/djrploss.h"
#include "dcmtk/dcmjpeg/djeijg8.h"


DJEncoderBaseline::DJEncoderBaseline()
: DJCodecEncoder()
{
}


DJEncoderBaseline::~DJEncoderBaseline()
{
}


E_TransferSyntax DJEncoderBaseline::supportedTransferSyntax() const
{
  return EXS_JPEGProcess1;
}


OFBool DJEncoderBaseline::isLosslessProcess() const
{
  return OFFalse;
}


void DJEncoderBaseline::createDerivationDescription(
  const DcmRepresentationParameter * toRepParam,
  const DJCodecParameter * /* cp */,
  Uint8 /* bitsPerSample */ ,
  double ratio,
  OFString& derivationDescription) const
{
  DJ_RPLossy defaultRP;
  const DJ_RPLossy *rp = toRepParam ? (const DJ_RPLossy *)toRepParam : &defaultRP ;
  char buf[64];
 
  derivationDescription =  "Lossy compression with JPEG baseline, IJG quality factor ";
  sprintf(buf, "%u", rp->getQuality());
  derivationDescription += buf;
  derivationDescription += ", compression ratio ";
  appendCompressionRatio(derivationDescription, ratio);
}


DJEncoder *DJEncoderBaseline::createEncoderInstance(
    const DcmRepresentationParameter * toRepParam,
    const DJCodecParameter *cp,
    Uint8 /* bitsPerSample */) const
{
  DJ_RPLossy defaultRP;
  const DJ_RPLossy *rp = toRepParam ? (const DJ_RPLossy *)toRepParam : &defaultRP ;
  DJCompressIJG8Bit *result = new DJCompressIJG8Bit(*cp, EJM_baseline, rp->getQuality());

  return result;
}
