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
