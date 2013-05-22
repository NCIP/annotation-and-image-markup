/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"

#include "dcmtk/dcmimgle/didislut.h"


/*----------------*
 *  constructors  *
 *----------------*/

DiDisplayLUT::DiDisplayLUT(const unsigned long count,
                           const Uint16 max,
                           const double amb,
                           const double illum)
  : DiBaseLUT(count, DicomImageClass::tobits(max, 0)),
    AmbientLight((amb > 0) ? amb : 0),
    Illumination((illum > 0) ? illum : 0)
{
}


/*--------------*
 *  destructor  *
 *--------------*/

DiDisplayLUT::~DiDisplayLUT()
{
}
