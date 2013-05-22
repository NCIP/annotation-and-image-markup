/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#include "dcmtk/dcmsr/dsriodcc.h"


DSRIODConstraintChecker::DSRIODConstraintChecker()
{
}


DSRIODConstraintChecker::~DSRIODConstraintChecker()
{
}


/*
 *  CVS/RCS Log:
 *  $Log: dsriodcc.cc,v $
 *  Revision 1.4  2010-10-14 13:14:41  joergr
 *  Updated copyright header. Added reference to COPYRIGHT file.
 *
 *  Revision 1.3  2005-12-08 15:47:56  meichel
 *  Changed include path schema for all DCMTK header files
 *
 *  Revision 1.2  2003/10/09 13:00:41  joergr
 *  Added check for root template identifier when reading an SR document.
 *
 *  Revision 1.1  2003/09/15 14:16:50  joergr
 *  Introduced new class to facilitate checking of SR IOD relationship content
 *  constraints. Replaced old implementation distributed over numerous classes.
 *
 */
