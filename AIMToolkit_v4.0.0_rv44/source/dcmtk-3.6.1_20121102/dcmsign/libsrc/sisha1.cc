/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"

#ifdef WITH_OPENSSL

#include "dcmtk/dcmsign/sisha1.h"
#include "dcmtk/dcmdata/dcerror.h"

#define INCLUDE_CSTDLIB
#include "dcmtk/ofstd/ofstdinc.h"

BEGIN_EXTERN_C
#include <openssl/sha.h>
END_EXTERN_C

 
SiSHA1::SiSHA1()
: ctx(new SHA_CTX())
{
  initialize();
}

SiSHA1::~SiSHA1()
{
  delete ctx;
}

unsigned long SiSHA1::getSize() const
{
  return SHA_DIGEST_LENGTH;
}

OFCondition SiSHA1::initialize()
{
  SHA1_Init(ctx);
  return EC_Normal;
}

OFCondition SiSHA1::digest(const unsigned char *data, unsigned long length)
{
  if (length == 0) return EC_Normal;
  if ((data == NULL)||(ctx == NULL)) return EC_IllegalCall;
  SHA1_Update(ctx, data, length);
  return EC_Normal;
}

OFCondition SiSHA1::finalize(unsigned char *result)
{
  if ((result == NULL)||(ctx == NULL)) return EC_IllegalCall;
  SHA1_Final(result, ctx);
  return EC_Normal;  
}

E_MACType SiSHA1::macType() const
{
  return EMT_SHA1;
}

const char *SiSHA1::getDefinedTerm() const
{
  return SI_DEFTERMS_SHA1;
}

#else /* WITH_OPENSSL */

int sisha1_cc_dummy_to_keep_linker_from_moaning = 0;

#endif
