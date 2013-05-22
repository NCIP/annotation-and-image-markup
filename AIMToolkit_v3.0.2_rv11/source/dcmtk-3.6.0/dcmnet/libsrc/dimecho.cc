/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#define INCLUDE_CSTDLIB
#define INCLUDE_CSTDIO
#define INCLUDE_CSTRING
#include "dcmtk/ofstd/ofstdinc.h"

#include "dcmtk/dcmnet/diutil.h"
#include "dcmtk/dcmnet/dimse.h"		/* always include the module header */
#include "dcmtk/dcmnet/cond.h"


OFCondition
DIMSE_echoUser(
	/* in */
	T_ASC_Association *assoc, DIC_US msgId,
	/* blocking info for response */
	T_DIMSE_BlockingMode blockMode, int timeout,
	/* out */
	DIC_US *status, DcmDataset **statusDetail)
{
    T_DIMSE_Message req, rsp;
    T_ASC_PresentationContextID presID;
    const char *sopClass;

    /* which SOP class  */
    sopClass = UID_VerificationSOPClass;

    /* which presentation context should be used */
    presID = ASC_findAcceptedPresentationContextID(assoc, sopClass);
    if (presID == 0)
    {
        char buf[1024];
        sprintf(buf, "DIMSE: No Presentation Context for: %s", sopClass);
        return makeDcmnetCondition(DIMSEC_NOVALIDPRESENTATIONCONTEXTID, OF_error, buf);
    }

    bzero((char*)&req, sizeof(req));
    bzero((char*)&rsp, sizeof(rsp));

    req.CommandField = DIMSE_C_ECHO_RQ;
    req.msg.CEchoRQ.MessageID = msgId;
    strcpy(req.msg.CEchoRQ.AffectedSOPClassUID,
	   sopClass);
    req.msg.CEchoRQ.DataSetType = DIMSE_DATASET_NULL;

    OFCondition cond = DIMSE_sendMessageUsingMemoryData(assoc, presID, &req, NULL, NULL, NULL, NULL);
    if (cond.bad()) return cond;

    /* receive response */
    cond = DIMSE_receiveCommand(assoc, blockMode, timeout, &presID, &rsp, statusDetail);
    if (cond.bad()) return cond;

    if (rsp.CommandField != DIMSE_C_ECHO_RSP)
    {
        char buf1[256];
        sprintf(buf1, "DIMSE: Unexpected Response Command Field: 0x%x", (unsigned)rsp.CommandField);
        return makeDcmnetCondition(DIMSEC_UNEXPECTEDRESPONSE, OF_error, buf1);
    }

    if (rsp.msg.CEchoRSP.MessageIDBeingRespondedTo != msgId)
    {
        char buf1[256];
        sprintf(buf1, "DIMSE: Unexpected Response MsgId: %d (expected: %d)", rsp.msg.CEchoRSP.MessageIDBeingRespondedTo, msgId);
        return makeDcmnetCondition(DIMSEC_UNEXPECTEDRESPONSE, OF_error, buf1);
    }

    *status = rsp.msg.CEchoRSP.DimseStatus;

    return EC_Normal;
}

OFCondition
DIMSE_sendEchoResponse(T_ASC_Association * assoc,
	T_ASC_PresentationContextID presID,
	T_DIMSE_C_EchoRQ *req, DIC_US status, DcmDataset *statusDetail)
{
    T_DIMSE_Message rsp;

    bzero((char*)&rsp, sizeof(rsp));

    rsp.CommandField = DIMSE_C_ECHO_RSP;
    rsp.msg.CEchoRSP.MessageIDBeingRespondedTo = req->MessageID;
    strcpy(rsp.msg.CEchoRSP.AffectedSOPClassUID,
	req->AffectedSOPClassUID);
    rsp.msg.CEchoRSP.opts = O_ECHO_AFFECTEDSOPCLASSUID;
    rsp.msg.CEchoRSP.DataSetType = DIMSE_DATASET_NULL;
    rsp.msg.CEchoRSP.DimseStatus = status;

    return DIMSE_sendMessageUsingMemoryData(assoc, presID, &rsp, statusDetail, NULL, NULL, NULL);
}



/*
** CVS Log
** $Log: dimecho.cc,v $
** Revision 1.11  2010-12-01 08:26:36  joergr
** Added OFFIS copyright header (beginning with the year 1994).
**
** Revision 1.10  2010-10-14 13:14:28  joergr
** Updated copyright header. Added reference to COPYRIGHT file.
**
** Revision 1.9  2005/12/08 15:44:41  meichel
** Changed include path schema for all DCMTK header files
**
** Revision 1.8  2002/11/27 13:04:40  meichel
** Adapted module dcmnet to use of new header file ofstdinc.h
**
** Revision 1.7  2001/10/12 10:18:33  meichel
** Replaced the CONDITION types, constants and functions in the dcmnet module
**   by an OFCondition based implementation which eliminates the global condition
**   stack.  This is a major change, caveat emptor!
**
** Revision 1.6  2000/02/23 15:12:33  meichel
** Corrected macro for Borland C++ Builder 4 workaround.
**
** Revision 1.5  2000/02/01 10:24:09  meichel
** Avoiding to include <stdlib.h> as extern "C" on Borland C++ Builder 4,
**   workaround for bug in compiler header files.
**
** Revision 1.4  1999/03/29 11:20:03  meichel
** Cleaned up dcmnet code for char* to const char* assignments.
**
** Revision 1.3  1998/08/10 08:53:43  meichel
** renamed member variable in DIMSE structures from "Status" to
**   "DimseStatus". This is required if dcmnet is used together with
**   <X11/Xlib.h> where Status is #define'd as int.
**
** Revision 1.2  1996/04/25 16:11:14  hewett
** Added parameter casts to char* for bzero calls.  Replaced some declarations
** of DIC_UL with unsigned long (reduces mismatch problems with 32 & 64 bit
** architectures).  Added some protection to inclusion of sys/socket.h (due
** to MIPS/Ultrix).
**
** Revision 1.1.1.1  1996/03/26 18:38:46  hewett
** Initial Release.
**
**
*/
