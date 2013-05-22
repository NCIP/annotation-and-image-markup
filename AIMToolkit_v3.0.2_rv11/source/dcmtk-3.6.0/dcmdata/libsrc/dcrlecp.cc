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


/*
 * CVS/RCS Log
 * $Log: dcrlecp.cc,v $
 * Revision 1.5  2010-10-14 13:14:09  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.4  2009-11-04 09:58:10  uli
 * Switched to logging mechanism provided by the "new" oflog module
 *
 * Revision 1.3  2005-12-08 15:41:31  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.2  2005/07/26 17:08:35  meichel
 * Added option to RLE decoder that allows to correctly decode images with
 *   incorrect byte order of byte segments (LSB instead of MSB).
 *
 * Revision 1.1  2002/06/06 14:52:41  meichel
 * Initial release of the new RLE codec classes
 *   and the dcmcrle/dcmdrle tools in module dcmdata
 *
 *
 */
