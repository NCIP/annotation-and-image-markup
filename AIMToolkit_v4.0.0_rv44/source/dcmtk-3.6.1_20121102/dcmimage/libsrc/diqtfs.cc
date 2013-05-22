/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmimage/diqtfs.h"
#include "dcmtk/ofstd/ofstd.h"       /* for OFStandard::myrand_r */

#define INCLUDE_CTIME
#include "dcmtk/ofstd/ofstdinc.h"

BEGIN_EXTERN_C
#include <sys/types.h> // needed for time()
END_EXTERN_C


DcmQuantFloydSteinberg::DcmQuantFloydSteinberg()
: thisrerr(NULL)
, nextrerr(NULL)
, thisgerr(NULL)
, nextgerr(NULL)
, thisberr(NULL)
, nextberr(NULL)
, temperr (NULL)
, fs_direction(0)
, columns(0)
{
}


DcmQuantFloydSteinberg::~DcmQuantFloydSteinberg()
{
  cleanup();
}


void DcmQuantFloydSteinberg::cleanup()
{
  delete[] thisrerr;
  delete[] nextrerr;
  delete[] thisgerr;
  delete[] nextgerr;
  delete[] thisberr;
  delete[] nextberr;
}


OFCondition DcmQuantFloydSteinberg::initialize(unsigned long cols)
{
  columns = cols;
  cleanup();
  unsigned int now = OFstatic_cast(unsigned int, time(NULL));

  /* Initialize Floyd-Steinberg error vectors. */
  thisrerr = new long[columns+2];
  if (! thisrerr) return EC_MemoryExhausted;

  nextrerr = new long[columns+2];
  if (! nextrerr) return EC_MemoryExhausted;

  thisgerr = new long[columns+2];
  if (! thisgerr) return EC_MemoryExhausted;

  nextgerr = new long[columns+2];
  if (! nextgerr) return EC_MemoryExhausted;

  thisberr = new long[columns+2];
  if (! thisberr) return EC_MemoryExhausted;

  nextberr = new long[columns+2];
  if (! nextberr) return EC_MemoryExhausted;

  for (unsigned long col = 0; col < columns + 2; ++col)
  {
      thisrerr[col] = OFStandard::rand_r(now) % ( DcmQuantFloydSteinbergScale * 2 ) - DcmQuantFloydSteinbergScale;
      thisgerr[col] = OFStandard::rand_r(now) % ( DcmQuantFloydSteinbergScale * 2 ) - DcmQuantFloydSteinbergScale;
      thisberr[col] = OFStandard::rand_r(now) % ( DcmQuantFloydSteinbergScale * 2 ) - DcmQuantFloydSteinbergScale;
      /* (random errors in [-1 .. 1]) */
  }
  fs_direction = 1;

  return EC_Normal;
}
