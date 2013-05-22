/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"

#ifdef WITH_OPENSSL

#include "dcmtk/dcmsign/sinullpr.h"

OFBool SiNullProfile::isAllowableMACType(E_MACType /* macType */) const
{
  return OFTrue;
}

OFBool SiNullProfile::isAllowableAlgorithmType(E_KeyType keyType) const
{
  if (keyType == EKT_none) return OFFalse;
  return OFTrue;
}

OFBool SiNullProfile::attributeRequired(const DcmTagKey& /* key */) const
{
  return OFFalse;
}

OFBool SiNullProfile::attributeForbidden(const DcmTagKey& /* key */) const
{
  return OFFalse;
}

OFBool SiNullProfile::isAllowableTransferSyntax(E_TransferSyntax xfer) const
{
  if ((xfer == EXS_LittleEndianImplicit)||(xfer == EXS_BigEndianExplicit)) return OFFalse;
  return OFTrue;
}

#else /* WITH_OPENSSL */

int sinullpr_cc_dummy_to_keep_linker_from_moaning = 0;

#endif

/*
 *  $Log: sinullpr.cc,v $
 *  Revision 1.6  2010-10-14 13:14:38  joergr
 *  Updated copyright header. Added reference to COPYRIGHT file.
 *
 *  Revision 1.5  2005-12-08 15:47:26  meichel
 *  Changed include path schema for all DCMTK header files
 *
 *  Revision 1.4  2002/12/16 12:57:52  meichel
 *  Minor modification to shut up linker on MacOS X when compiling
 *    without OpenSSL support
 *
 *  Revision 1.3  2001/11/16 15:50:54  meichel
 *  Adapted digital signature code to final text of supplement 41.
 *
 *  Revision 1.2  2001/06/01 15:50:54  meichel
 *  Updated copyright header
 *
 *  Revision 1.1  2000/11/07 16:49:06  meichel
 *  Initial release of dcmsign module for DICOM Digital Signatures
 *
 *
 */

