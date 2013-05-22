/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmjpeg/djenclol.h"
#include "dcmtk/dcmjpeg/djcparam.h"
#include "dcmtk/dcmjpeg/djrplol.h"
#include "dcmtk/dcmjpeg/djeijg8.h"
#include "dcmtk/dcmjpeg/djeijg12.h"
#include "dcmtk/dcmjpeg/djeijg16.h"


DJEncoderLossless::DJEncoderLossless()
: DJCodecEncoder()
{
}


DJEncoderLossless::~DJEncoderLossless()
{
}


E_TransferSyntax DJEncoderLossless::supportedTransferSyntax() const
{
  return EXS_JPEGProcess14;
}


OFBool DJEncoderLossless::isLosslessProcess() const
{
  return OFTrue;
}


void DJEncoderLossless::createDerivationDescription(
  const DcmRepresentationParameter * toRepParam,
  const DJCodecParameter *cp,
  Uint8 /* bitsPerSample */ ,
  double ratio,
  OFString& derivationDescription) const
{
  DJ_RPLossless defaultRP;
  const DJ_RPLossless *rp = toRepParam ? (const DJ_RPLossless *)toRepParam : &defaultRP ;
  char buf[64];

  if (cp->getTrueLosslessMode())
    derivationDescription = "Lossless JPEG compression, selection value ";
  else
    derivationDescription = "Pseudo-Lossless JPEG compression, selection value ";
  sprintf(buf, "%u", rp->getPrediction());
  derivationDescription += buf;
  derivationDescription += ", point transform ";
  sprintf(buf, "%u", rp->getPointTransformation());
  derivationDescription += buf;
  derivationDescription += ", compression ratio ";
  appendCompressionRatio(derivationDescription, ratio);
}


DJEncoder *DJEncoderLossless::createEncoderInstance(
  const DcmRepresentationParameter * toRepParam,
  const DJCodecParameter *cp,
  Uint8 bitsPerSample) const
{
  DJ_RPLossless defaultRP;
  const DJ_RPLossless *rp = toRepParam ? (const DJ_RPLossless *)toRepParam : &defaultRP ;
  DJEncoder *result = NULL;
  if (bitsPerSample > 12)
    result = new DJCompressIJG16Bit(*cp, EJM_lossless, rp->getPrediction(), rp->getPointTransformation());
  else if (bitsPerSample > 8)
    result = new DJCompressIJG12Bit(*cp, EJM_lossless, rp->getPrediction(), rp->getPointTransformation());
  else
    result = new DJCompressIJG8Bit(*cp, EJM_lossless, rp->getPrediction(), rp->getPointTransformation());
  return result;
}
