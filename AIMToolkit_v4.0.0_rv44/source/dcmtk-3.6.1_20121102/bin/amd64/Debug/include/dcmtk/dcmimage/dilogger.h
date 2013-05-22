/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#ifndef DILOGGER_H
#define DILOGGER_H

#include "dcmtk/config/osconfig.h"

#include "dcmtk/oflog/oflog.h"

#include "dcmtk/dcmimage/dicdefin.h"

extern DCMTK_DCMIMAGE_EXPORT OFLogger DCM_dcmimageLogger;

#define DCMIMAGE_TRACE(msg) OFLOG_TRACE(DCM_dcmimageLogger, msg)
#define DCMIMAGE_DEBUG(msg) OFLOG_DEBUG(DCM_dcmimageLogger, msg)
#define DCMIMAGE_INFO(msg)  OFLOG_INFO(DCM_dcmimageLogger, msg)
#define DCMIMAGE_WARN(msg)  OFLOG_WARN(DCM_dcmimageLogger, msg)
#define DCMIMAGE_ERROR(msg) OFLOG_ERROR(DCM_dcmimageLogger, msg)
#define DCMIMAGE_FATAL(msg) OFLOG_FATAL(DCM_dcmimageLogger, msg)

#endif
