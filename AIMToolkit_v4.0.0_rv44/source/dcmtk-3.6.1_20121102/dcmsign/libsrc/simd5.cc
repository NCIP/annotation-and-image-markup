/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"

#ifdef WITH_OPENSSL

#include "dcmtk/dcmsign/simd5.h"
#include "dcmtk/dcmdata/dcerror.h"

#define INCLUDE_CSTDLIB
#include "dcmtk/ofstd/ofstdinc.h"

BEGIN_EXTERN_C
#include <openssl/md5.h>
END_EXTERN_C

 
SiMD5::SiMD5()
: ctx(new MD5_CTX())
{
  initialize();
}

SiMD5::~SiMD5()
{
  delete ctx;
}

unsigned long SiMD5::getSize() const
{
  return MD5_DIGEST_LENGTH;
}

OFCondition SiMD5::initialize()
{
  MD5_Init(ctx);
  return EC_Normal;
}

OFCondition SiMD5::digest(const unsigned char *data, unsigned long length)
{
  if (length == 0) return EC_Normal;
  if ((data == NULL)||(ctx == NULL)) return EC_IllegalCall;
  MD5_Update(ctx, data, length);
  return EC_Normal;
}

OFCondition SiMD5::finalize(unsigned char *result)
{
  if ((result == NULL)||(ctx == NULL)) return EC_IllegalCall;
  MD5_Final(result, ctx);
  return EC_Normal;  
}

E_MACType SiMD5::macType() const
{
  return EMT_MD5;
}

const char *SiMD5::getDefinedTerm() const
{
  return SI_DEFTERMS_MD5;
}


#else /* WITH_OPENSSL */

int simd5_cc_dummy_to_keep_linker_from_moaning = 0;

#endif
