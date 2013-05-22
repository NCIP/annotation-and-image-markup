/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctypes.h"

#include "dcmtk/dcmimgle/diovlay.h"
#include "dcmtk/dcmimgle/diovpln.h"

#include "dcmtk/ofstd/ofbmanip.h"


/*---------------*
 *  constructor  *
 *---------------*/

DiOverlayData::DiOverlayData(unsigned int entries,
                             unsigned int count)
  : Count(count),
    ArrayEntries(entries),
    Planes(NULL),
    DataBuffer(NULL)
{
    if ((entries > 0) && (entries <= DiOverlay::MaxOverlayCount))
    {
        Planes = new DiOverlayPlane *[entries];
        if (Planes != NULL)
            OFBitmanipTemplate<DiOverlayPlane *>::zeroMem(Planes, entries);
    }
}


/*---------------*
 *  destructors  *
 *---------------*/

DiOverlayData::~DiOverlayData()
{
    if (Planes != NULL)
    {
        register unsigned int i;
        for (i = 0; i < ArrayEntries; ++i)
            delete Planes[i];
    }
    delete[] Planes;
    delete[] DataBuffer;
}
