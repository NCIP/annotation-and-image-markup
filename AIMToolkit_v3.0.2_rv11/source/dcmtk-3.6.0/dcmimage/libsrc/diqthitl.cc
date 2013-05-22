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


/*
 *
 * CVS/RCS Log:
 * $Log: diqthitl.cc,v $
 * Revision 1.4  2010-10-14 13:14:14  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.3  2005/12/08 15:42:31  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.2  2003/12/17 16:34:14  joergr
 * Renamed parameters/variables "list" to avoid name clash with STL class.
 *
 * Revision 1.1  2002/01/25 13:32:11  meichel
 * Initial release of new color quantization classes and
 *   the dcmquant tool in module dcmimage.
 *
 *
 */
