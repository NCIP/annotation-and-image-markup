/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmimage/diqthitl.h"


DcmQuantHistogramItemList::DcmQuantHistogramItemList()
: list_()
, first(list_.end())
, last(list_.end())
{
}


DcmQuantHistogramItemList::~DcmQuantHistogramItemList()
{
  first = list_.begin();
  while (first != last)
  {
    delete *first;
    first = list_.erase(first);
  }
}


void DcmQuantHistogramItemList::moveto(DcmQuantHistogramItemPointer *array, unsigned long& counter, unsigned long numcolors)
{
  first = list_.begin();
  while ((first != last) && (counter < numcolors))
  {
    array[counter++] = *first;
    first = list_.erase(first);
  }
}
