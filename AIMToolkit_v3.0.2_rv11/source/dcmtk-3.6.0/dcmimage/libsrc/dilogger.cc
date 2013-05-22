/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"

#include "dcmtk/dcmimage/dilogger.h"


OFLogger DCM_dcmimageGetLogger()
{
    static OFLogger DCM_dcmimageLogger = OFLog::getLogger("dcmtk.dcmimage");
    return DCM_dcmimageLogger;
}


/*
 *
 * CVS/RCS Log:
 * $Log: dilogger.cc,v $
 * Revision 1.2  2010-10-14 13:14:14  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.1  2009-11-25 16:48:46  joergr
 * Added new source and header file for the module logger.
 *
 *
 */
