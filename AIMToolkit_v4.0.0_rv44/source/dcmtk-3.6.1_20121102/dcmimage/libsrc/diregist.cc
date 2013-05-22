/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"

#include "dcmtk/dcmimage/diregist.h"
#include "dcmtk/dcmimage/dipalimg.h"
#include "dcmtk/dcmimage/dirgbimg.h"
#include "dcmtk/dcmimage/dihsvimg.h"
#include "dcmtk/dcmimage/diargimg.h"
#include "dcmtk/dcmimage/dicmyimg.h"
#include "dcmtk/dcmimage/diybrimg.h"
#include "dcmtk/dcmimage/diyf2img.h"
#include "dcmtk/dcmimage/diyp2img.h"
#include "dcmtk/dcmimage/dicomot.h"
#include "dcmtk/dcmimgle/didocu.h"


/*----------------*
 *  constructors  *
 *----------------*/

DiRegister::DiRegister()
{
    DiRegisterBase::Pointer = this;
}


/*--------------*
 *  destructor  *
 *--------------*/

DiRegister::~DiRegister()
{
}


/*--------------*/

DiImage *DiRegister::createImage(const DiDocument *docu,
                                 const EI_Status status,
                                 const EP_Interpretation photo)
{
    DiImage *image = NULL;
    switch (photo)
    {
        case EPI_PaletteColor:
            image = new DiPaletteImage(docu, status);
            break;
        case EPI_RGB:
            image = new DiRGBImage(docu, status);
            break;
        case EPI_HSV:
            image = new DiHSVImage(docu, status);
            break;
        case EPI_ARGB:
            image = new DiARGBImage(docu, status);
            break;
        case EPI_CMYK:
            image = new DiCMYKImage(docu, status);
            break;
        case EPI_YBR_Full:
            image = new DiYBRImage(docu, status);
            break;
        case EPI_YBR_Full_422:
            image = new DiYBR422Image(docu, status);
            break;
        case EPI_YBR_Partial_422:
            image = new DiYBRPart422Image(docu, status);
            break;
        default:
            ;
    }
    return image;
}


DiMonoPixel *DiRegister::createMonoImageData(const DiColorImage *image,
                                             const double red,
                                             const double green,
                                             const double blue)
{
    DiMonoPixel *inter = NULL;
    if (image != NULL)
    {
        const DiColorPixel *color = image->getColorInterData();
        if (color != NULL)
        {
            DiMonoModality *modality = new DiMonoModality(image->getBits());
            if (modality != NULL)
            {
                switch (color->getRepresentation())
                {
                    case EPR_Uint8:
                        inter = new DiColorMonoTemplate<Uint8>(color, modality, red, green, blue);
                        break;
                    case EPR_Sint8:
                        inter = new DiColorMonoTemplate<Sint8>(color, modality, red, green, blue);
                        break;
                    case EPR_Uint16:
                        inter = new DiColorMonoTemplate<Uint16>(color, modality, red, green, blue);
                        break;
                    case EPR_Sint16:
                        inter = new DiColorMonoTemplate<Sint16>(color, modality, red, green, blue);
                        break;
                    case EPR_Uint32:
                        inter = new DiColorMonoTemplate<Uint32>(color, modality, red, green, blue);
                        break;
                    case EPR_Sint32:
                        inter = new DiColorMonoTemplate<Sint32>(color, modality, red, green, blue);
                        break;
                }
            }
        }
    }
    return inter;
}
