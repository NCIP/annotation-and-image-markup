/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
