/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef SIAUTOPR_H
#define SIAUTOPR_H

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmsign/sibrsapr.h"   /* for SiBaseRSAProfile */

#ifdef WITH_OPENSSL

/** Authorization Digital Signature Profile
 */
class DCMTK_DCMSIGN_EXPORT SiAuthorizationProfile: public SiBaseRSAProfile
{
public:

  /// default constructor
  SiAuthorizationProfile() { }

  /// destructor
  virtual ~SiAuthorizationProfile() { }

  /** checks whether an attribute with the given tag is required to be signed
   *  for the current security profile.
   *  @param key tag key to be checked
   *  @return true if required, false otherwise.
   */
  virtual OFBool attributeRequired(const DcmTagKey& key) const;

};

#endif
#endif
