/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"
#include "dcmtk/ofstd/ofcast.h"
#include "dcmtk/dcmimage/diqtpbox.h"   /* for DcmQuantPixelBoxArray */

#ifdef USE_STD_CXX_INCLUDES
// Solaris defines qsort() in namespace std, other compilers don't...
namespace std { }
using namespace std;
#endif


BEGIN_EXTERN_C
static int sumcompare(const void *x1, const void *x2)
{
  return (*(DcmQuantPixelBoxPointer *) x2)->sum
       - (*(DcmQuantPixelBoxPointer *) x1)->sum;
}
END_EXTERN_C


void DcmQuantPixelBoxArray::sort(unsigned long boxes)
{
#ifdef DEBUG
  assert(boxes <= length);
#endif
  qsort(OFreinterpret_cast(char *, array), OFstatic_cast(unsigned int, boxes),  sizeof(DcmQuantPixelBoxPointer), sumcompare);
}


DcmQuantPixelBoxArray::DcmQuantPixelBoxArray(unsigned long entries)
: array(NULL)
, length(entries)
{
  array = new DcmQuantPixelBoxPointer[entries];
  for (unsigned long i=0; i<entries; i++) array[i] = new DcmQuantPixelBox();
}


DcmQuantPixelBoxArray::~DcmQuantPixelBoxArray()
{
  for (unsigned long i=0; i<length; i++) delete array[i];
  delete[] array;
}
