/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"

#include "dcmtk/dcmdata/dctypes.h"

#include "dcmtk/dcmimage/dihsvimg.h"
#include "dcmtk/dcmimage/dihsvpxt.h"
#include "dcmtk/dcmimage/dilogger.h"
#include "dcmtk/dcmimgle/diinpx.h"


/*----------------*
 *  constructors  *
 *----------------*/

DiHSVImage::DiHSVImage(const DiDocument *docu,
                       const EI_Status status)
  : DiColorImage(docu, status, 3)
{
    if ((Document != NULL) && (InputData != NULL) && (ImageStatus == EIS_Normal))
    {
        Init();                                                 // create intermediate representation
    }
}


/*--------------*
 *  destructor  *
 *--------------*/

DiHSVImage::~DiHSVImage()
{
}


/*********************************************************************/


void DiHSVImage::Init()
{
    /* number of pixels per plane */
    const unsigned long planeSize = OFstatic_cast(unsigned long, Columns) * OFstatic_cast(unsigned long, Rows);
    switch (InputData->getRepresentation())
    {
        case EPR_Uint8:
            InterData = new DiHSVPixelTemplate<Uint8, Uint8>(Document, InputData, ImageStatus, planeSize, BitsPerSample);
            break;
        case EPR_Sint8:
            InterData = new DiHSVPixelTemplate<Sint8, Uint8>(Document, InputData, ImageStatus, planeSize, BitsPerSample);
            break;
        case EPR_Uint16:
            InterData = new DiHSVPixelTemplate<Uint16, Uint16>(Document, InputData, ImageStatus, planeSize, BitsPerSample);
            break;
        case EPR_Sint16:
            InterData = new DiHSVPixelTemplate<Sint16, Uint16>(Document, InputData, ImageStatus, planeSize, BitsPerSample);
            break;
        case EPR_Uint32:
            InterData = new DiHSVPixelTemplate<Uint32, Uint32>(Document, InputData, ImageStatus, planeSize, BitsPerSample);
            break;
        case EPR_Sint32:
            InterData = new DiHSVPixelTemplate<Sint32, Uint32>(Document, InputData, ImageStatus, planeSize, BitsPerSample);
            break;
    }
    deleteInputData();
    checkInterData();
}


/*********************************************************************/


int DiHSVImage::processNextFrames(const unsigned long fcount)
{
    if (DiImage::processNextFrames(fcount))
    {
        delete InterData;
        InterData = NULL;
        Init();
        return (ImageStatus == EIS_Normal);
    }
    return 0;
}
