/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dcrlecp.h"

DcmRLECodecParameter::DcmRLECodecParameter(
    OFBool pCreateSOPInstanceUID,
    Uint32 pFragmentSize,
    OFBool pCreateOffsetTable,
    OFBool pConvertToSC,
    OFBool pReverseDecompressionByteOrder)
: DcmCodecParameter()
, fragmentSize(pFragmentSize)
, createOffsetTable(pCreateOffsetTable)
, convertToSC(pConvertToSC)
, createInstanceUID(pCreateSOPInstanceUID)
, reverseDecompressionByteOrder(pReverseDecompressionByteOrder)
{
}


DcmRLECodecParameter::DcmRLECodecParameter(const DcmRLECodecParameter& arg)
: DcmCodecParameter(arg)
, fragmentSize(arg.fragmentSize)
, createOffsetTable(arg.createOffsetTable)
, convertToSC(arg.convertToSC)
, createInstanceUID(arg.createInstanceUID)
, reverseDecompressionByteOrder(arg.reverseDecompressionByteOrder)
{
}

DcmRLECodecParameter::~DcmRLECodecParameter()
{
}
  
DcmCodecParameter *DcmRLECodecParameter::clone() const
{
  return new DcmRLECodecParameter(*this);
} 

const char *DcmRLECodecParameter::className() const
{
  return "DcmRLECodecParameter";
}
