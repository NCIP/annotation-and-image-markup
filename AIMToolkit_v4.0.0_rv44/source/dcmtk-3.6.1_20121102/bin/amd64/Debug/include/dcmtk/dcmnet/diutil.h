/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef DIUTIL_H
#define DIUTIL_H

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#include "dcmtk/dcmnet/dicom.h"
#include "dcmtk/dcmdata/dcdatset.h"
#include "dcmtk/dcmnet/dimse.h"
#include "dcmtk/oflog/oflog.h"


extern DCMTK_DCMNET_EXPORT OFLogger DCM_dcmnetLogger;

#define DCMNET_LOGGER_NAME "dcmtk.dcmnet"

#define DCMNET_TRACE(msg) OFLOG_TRACE(DCM_dcmnetLogger, msg)
#define DCMNET_DEBUG(msg) OFLOG_DEBUG(DCM_dcmnetLogger, msg)
#define DCMNET_INFO(msg)  OFLOG_INFO(DCM_dcmnetLogger, msg)
#define DCMNET_WARN(msg)  OFLOG_WARN(DCM_dcmnetLogger, msg)
#define DCMNET_ERROR(msg) OFLOG_ERROR(DCM_dcmnetLogger, msg)
#define DCMNET_FATAL(msg) OFLOG_FATAL(DCM_dcmnetLogger, msg)


DCMTK_DCMNET_EXPORT void DU_stripTrailingSpaces(char *s);
DCMTK_DCMNET_EXPORT void DU_stripLeadingSpaces(char *s);
DCMTK_DCMNET_EXPORT void DU_stripLeadingAndTrailingSpaces(char *s);

DCMTK_DCMNET_EXPORT OFBool DU_getStringDOElement(DcmItem *obj, DcmTagKey t, char *s);
DCMTK_DCMNET_EXPORT OFBool DU_putStringDOElement(DcmItem *obj, DcmTagKey t, const char *s);
DCMTK_DCMNET_EXPORT OFBool DU_getShortDOElement(DcmItem *obj, DcmTagKey t, Uint16 *us);
DCMTK_DCMNET_EXPORT OFBool DU_putShortDOElement(DcmItem *obj, DcmTagKey t, Uint16 us);

DCMTK_DCMNET_EXPORT OFBool DU_findSOPClassAndInstanceInDataSet(
  DcmItem *obj,
  char* sopClass,
  char* sopInstance,
  OFBool tolerateSpacePaddedUIDs = OFFalse);

DCMTK_DCMNET_EXPORT OFBool DU_findSOPClassAndInstanceInFile(
  const char *fname,
  char* sopClass,
  char* sopInstance,
  OFBool tolerateSpacePaddedUIDs = OFFalse);

DCMTK_DCMNET_EXPORT const char *DU_cechoStatusString(Uint16 statusCode);
DCMTK_DCMNET_EXPORT const char *DU_cstoreStatusString(Uint16 statusCode);
DCMTK_DCMNET_EXPORT const char *DU_cfindStatusString(Uint16 statusCode);
DCMTK_DCMNET_EXPORT const char *DU_cmoveStatusString(Uint16 statusCode);
DCMTK_DCMNET_EXPORT const char *DU_cgetStatusString(Uint16 statusCode);

DCMTK_DCMNET_EXPORT const char *DU_ncreateStatusString(Uint16 statusCode);
DCMTK_DCMNET_EXPORT const char *DU_ngetStatusString(Uint16 statusCode);
DCMTK_DCMNET_EXPORT const char *DU_nsetStatusString(Uint16 statusCode);
DCMTK_DCMNET_EXPORT const char *DU_nactionStatusString(Uint16 statusCode);
DCMTK_DCMNET_EXPORT const char *DU_ndeleteStatusString(Uint16 statusCode);
DCMTK_DCMNET_EXPORT const char *DU_neventReportStatusString(Uint16 statusCode);

#endif
