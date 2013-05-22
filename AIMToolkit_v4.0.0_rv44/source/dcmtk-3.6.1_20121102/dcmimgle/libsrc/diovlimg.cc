/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctypes.h"

#include "dcmtk/dcmimgle/diovlimg.h"
#include "dcmtk/dcmimgle/dimopxt.h"
#include "dcmtk/dcmimgle/didocu.h"


/*----------------*
 *  constructors  *
 *----------------*/

DiOverlayImage::DiOverlayImage(const DiDocument *docu,
                               const EI_Status status)
  : DiMono2Image(docu, status, 0)
{
    if (Document != NULL)
    {
        Overlays[0] = new DiOverlay(Document);
        if (Overlays[0] != NULL)
        {
            BitsPerSample = 1;
            register unsigned int i;
            register DiOverlayPlane *plane;
            for (i = 0; i < Overlays[0]->getCount(); ++i)
            {
                plane = Overlays[0]->getPlane(i);
                if (plane != NULL)
                {
                    plane->show();
                    if (plane->getNumberOfFrames() > NumberOfFrames)
                        NumberOfFrames = plane->getNumberOfFrames();
                    if (plane->getRight() > Columns)                // determine image's width and height
                        Columns = plane->getRight();
                    if (plane->getBottom() > Rows)
                        Rows = plane->getBottom();
                }
            }
            if ((Rows > 0) && (Columns > 0))
            {
                InterData = new DiMonoPixelTemplate<Uint8>(OFstatic_cast(unsigned long, Rows) *
                    OFstatic_cast(unsigned long, Columns) * NumberOfFrames);
                if (InterData == NULL)
                {
                    ImageStatus = EIS_MemoryFailure;
                    DCMIMGLE_ERROR("can't allocate memory for inter-representation");
                }
                else if (InterData->getData() == NULL)
                    ImageStatus = EIS_InvalidImage;
            }
            else
            {
                ImageStatus = EIS_InvalidValue;
                DCMIMGLE_ERROR("invalid value for 'Rows' (" << Rows << ") and/or 'Columns' (" << Columns << ")");
            }
        }
    }
    else
    {
        ImageStatus = EIS_InvalidDocument;
        DCMIMGLE_ERROR("this DICOM document is invalid");
    }
}


/*--------------*
 *  destructor  *
 *--------------*/

DiOverlayImage::~DiOverlayImage()
{
}
