/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"

#include "dcmtk/dcmimgle/dimopx.h"
#include "dcmtk/dcmimgle/dimomod.h"
#include "dcmtk/dcmimgle/diinpx.h"
#include "dcmtk/dcmimgle/dimoopx.h"


/*----------------*
 *  constructors  *
 *----------------*/

DiMonoPixel::DiMonoPixel(const unsigned long count)
  : DiPixel(count),
    Modality(NULL)
{
}


DiMonoPixel::DiMonoPixel(const DiInputPixel *pixel,
                         DiMonoModality *modality)
  : DiPixel((pixel != NULL) ? pixel->getComputedCount() : 0,
            (pixel != NULL) ? pixel->getPixelCount() : 0),
    Modality(modality)
{
}


DiMonoPixel::DiMonoPixel(const DiPixel *pixel,
                         DiMonoModality *modality)
  : DiPixel(pixel->getCount(), pixel->getInputCount()),
    Modality(modality)
{
}


DiMonoPixel::DiMonoPixel(const DiMonoPixel *pixel,
                         const unsigned long count)
  : DiPixel(count, pixel->getInputCount()),
    Modality(pixel->Modality)
{
    if (Modality != NULL)
        Modality->addReference();
}


DiMonoPixel::DiMonoPixel(DiMonoOutputPixel *pixel,
                         DiMonoModality *modality)
  : DiPixel(pixel->getCount()),
    Modality(modality)
{
}


/*--------------*
 *  destructor  *
 *--------------*/

DiMonoPixel::~DiMonoPixel()
{
    if (Modality != NULL)
        Modality->removeReference();
}


/*********************************************************************/


DiMonoModality *DiMonoPixel::addReferenceToModality()
{
    if (Modality != NULL)
        Modality->addReference();
    return Modality;
}
