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


/*
 *
 * CVS/RCS Log:
 * $Log: didislut.cc,v $
 * Revision 1.8  2010-10-14 13:14:17  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.7  2005/12/08 15:42:46  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.6  2003/12/08 17:43:04  joergr
 * Updated copyright header.
 *
 * Revision 1.5  2002/07/02 16:24:37  joergr
 * Added support for hardcopy devices to the calibrated output routines.
 *
 * Revision 1.4  2001/06/01 15:49:54  meichel
 * Updated copyright header
 *
 * Revision 1.3  2000/03/08 16:24:26  meichel
 * Updated copyright header.
 *
 * Revision 1.2  1999/10/21 17:47:13  joergr
 * Added underflow check to ambient light value.
 *
 * Revision 1.1  1999/09/10 08:54:48  joergr
 * Added support for CIELAB display function. Restructured class hierarchy
 * for display functions.
 *
 *
 *
 */
