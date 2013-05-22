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

OFLogger DCM_dcmimageGetLogger();

#define DCMIMAGE_TRACE(msg) OFLOG_TRACE(DCM_dcmimageGetLogger(), msg)
#define DCMIMAGE_DEBUG(msg) OFLOG_DEBUG(DCM_dcmimageGetLogger(), msg)
#define DCMIMAGE_INFO(msg)  OFLOG_INFO(DCM_dcmimageGetLogger(), msg)
#define DCMIMAGE_WARN(msg)  OFLOG_WARN(DCM_dcmimageGetLogger(), msg)
#define DCMIMAGE_ERROR(msg) OFLOG_ERROR(DCM_dcmimageGetLogger(), msg)
#define DCMIMAGE_FATAL(msg) OFLOG_FATAL(DCM_dcmimageGetLogger(), msg)

#endif


/*
 *
 * CVS/RCS Log:
 * $Log: dilogger.h,v $
 * Revision 1.2  2010-10-14 13:16:29  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.1  2009-11-25 14:32:47  joergr
 * Added new source and header file for the module logger.
 *
 *
 */
