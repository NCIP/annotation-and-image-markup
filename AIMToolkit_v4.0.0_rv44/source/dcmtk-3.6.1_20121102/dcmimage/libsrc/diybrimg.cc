/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"

#include "dcmtk/dcmdata/dctypes.h"

#include "dcmtk/dcmimage/diybrimg.h"
#include "dcmtk/dcmimage/diybrpxt.h"
#include "dcmtk/dcmimage/dilogger.h"
#include "dcmtk/dcmimgle/diinpx.h"
#include "dcmtk/dcmimgle/didocu.h"


/*----------------*
 *  constructors  *
 *----------------*/

DiYBRImage::DiYBRImage(const DiDocument *docu,
                       const EI_Status status)
  : DiColorImage(docu, status, 3, !(docu->getFlags() & CIF_KeepYCbCrColorModel) /* RGBColorModel */)
{
    if ((Document != NULL) && (InputData != NULL) && (ImageStatus == EIS_Normal))
    {
        Init();                                                 // create intermediate representation
    }
}


/*--------------*
 *  destructor  *
 *--------------*/

DiYBRImage::~DiYBRImage()
{
}


/*********************************************************************/


void DiYBRImage::Init()
{
    /* number of pixels per plane */
    const unsigned long planeSize = OFstatic_cast(unsigned long, Columns) * OFstatic_cast(unsigned long, Rows);
    switch (InputData->getRepresentation())
    {
        case EPR_Uint8:
            InterData = new DiYBRPixelTemplate<Uint8, Uint8>(Document, InputData, ImageStatus, planeSize, BitsPerSample, RGBColorModel);
            break;
        case EPR_Sint8:
            InterData = new DiYBRPixelTemplate<Sint8, Uint8>(Document, InputData, ImageStatus, planeSize, BitsPerSample, RGBColorModel);
            break;
        case EPR_Uint16:
            InterData = new DiYBRPixelTemplate<Uint16, Uint16>(Document, InputData, ImageStatus, planeSize, BitsPerSample, RGBColorModel);
            break;
        case EPR_Sint16:
            InterData = new DiYBRPixelTemplate<Sint16, Uint16>(Document, InputData, ImageStatus, planeSize, BitsPerSample, RGBColorModel);
            break;
        case EPR_Uint32:
            InterData = new DiYBRPixelTemplate<Uint32, Uint32>(Document, InputData, ImageStatus, planeSize, BitsPerSample, RGBColorModel);
            break;
        case EPR_Sint32:
            InterData = new DiYBRPixelTemplate<Sint32, Uint32>(Document, InputData, ImageStatus, planeSize, BitsPerSample, RGBColorModel);
            break;
    }
    deleteInputData();
    checkInterData();
}


/*********************************************************************/


int DiYBRImage::processNextFrames(const unsigned long fcount)
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
