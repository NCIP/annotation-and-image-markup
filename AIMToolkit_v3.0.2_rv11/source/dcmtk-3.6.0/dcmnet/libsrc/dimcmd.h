/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef DIMCMD_H
#define DIMCMD_H

/*
 * Required Include Files
 */

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#include "dcmtk/dcmnet/dimse.h"

/*
 * Function Prototypes
 */

OFCondition
DIMSE_buildCmdObject(T_DIMSE_Message *msg, DcmDataset **obj);

OFCondition
DIMSE_parseCmdObject(T_DIMSE_Message *msg, DcmDataset *obj);

OFBool
DIMSE_isDataSetPresent(T_DIMSE_Message *msg);

unsigned long
DIMSE_countElements(DcmDataset *obj);

#endif

/*
** CVS Log
** $Log: dimcmd.h,v $
** Revision 1.6  2010-12-01 08:26:36  joergr
** Added OFFIS copyright header (beginning with the year 1994).
**
** Revision 1.5  2010-10-14 13:19:29  joergr
** Updated copyright header. Added reference to COPYRIGHT file.
**
** Revision 1.4  2005/12/08 15:48:09  meichel
** Updated Makefiles to correctly install header files
**
** Revision 1.3  2001/10/12 10:18:32  meichel
** Replaced the CONDITION types, constants and functions in the dcmnet module
**   by an OFCondition based implementation which eliminates the global condition
**   stack.  This is a major change, caveat emptor!
**
** Revision 1.2  1997/07/21 08:47:17  andreas
** - Replace all boolean types (BOOLEAN, CTNBOOLEAN, DICOM_BOOL, BOOL)
**   with one unique boolean type OFBool.
**
** Revision 1.1.1.1  1996/03/26 18:38:45  hewett
** Initial Release.
**
**
*/
