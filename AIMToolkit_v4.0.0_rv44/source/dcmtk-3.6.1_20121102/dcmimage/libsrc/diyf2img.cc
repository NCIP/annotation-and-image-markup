/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"

#include "dcmtk/dcmdata/dctypes.h"

#include "dcmtk/dcmimage/diyf2img.h"
#include "dcmtk/dcmimage/diyf2pxt.h"
#include "dcmtk/dcmimage/dilogger.h"
#include "dcmtk/dcmimgle/diinpx.h"
#include "dcmtk/dcmimgle/didocu.h"


/*----------------*
 *  constructors  *
 *----------------*/

DiYBR422Image::DiYBR422Image(const DiDocument *docu,
                             const EI_Status status)
  : DiColorImage(docu, status, 2, !(docu->getFlags() & CIF_KeepYCbCrColorModel) /* RGBColorModel */)
{
    if ((Document != NULL) && (InputData != NULL) && (ImageStatus == EIS_Normal))
    {
        Init();                                                 // create intermediate representation
    }
}


/*--------------*
 *  destructor  *
 *--------------*/

DiYBR422Image::~DiYBR422Image()
{
}


/*********************************************************************/


void DiYBR422Image::Init()
{
    switch (InputData->getRepresentation())
    {
        case EPR_Uint8:
            InterData = new DiYBR422PixelTemplate<Uint8, Uint8>(Document, InputData, ImageStatus, BitsPerSample, RGBColorModel);
            break;
        case EPR_Sint8:
            InterData = new DiYBR422PixelTemplate<Sint8, Uint8>(Document, InputData, ImageStatus, BitsPerSample, RGBColorModel);
            break;
        case EPR_Uint16:
            InterData = new DiYBR422PixelTemplate<Uint16, Uint16>(Document, InputData, ImageStatus, BitsPerSample, RGBColorModel);
            break;
        case EPR_Sint16:
            InterData = new DiYBR422PixelTemplate<Sint16, Uint16>(Document, InputData, ImageStatus, BitsPerSample, RGBColorModel);
            break;
        case EPR_Uint32:
            InterData = new DiYBR422PixelTemplate<Uint32, Uint32>(Document, InputData, ImageStatus, BitsPerSample, RGBColorModel);
            break;
        case EPR_Sint32:
            InterData = new DiYBR422PixelTemplate<Sint32, Uint32>(Document, InputData, ImageStatus, BitsPerSample, RGBColorModel);
            break;
    }
    deleteInputData();
    checkInterData();
}


/*********************************************************************/


int DiYBR422Image::processNextFrames(const unsigned long fcount)
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
