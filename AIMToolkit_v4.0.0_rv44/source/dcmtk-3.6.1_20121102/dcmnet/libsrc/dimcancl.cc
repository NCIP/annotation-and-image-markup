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
#define INCLUDE_CSTDARG
#include "dcmtk/ofstd/ofstdinc.h"

#ifdef HAVE_FCNTL_H
#include <fcntl.h>
#endif

#include "dcmtk/dcmnet/diutil.h"
#include "dcmtk/dcmnet/dimse.h"		/* always include the module header */
#include "dcmtk/dcmnet/cond.h"

OFCondition
DIMSE_sendCancelRequest(T_ASC_Association * assoc,
	T_ASC_PresentationContextID presId, DIC_US msgId)
{
    T_DIMSE_Message req;
    bzero((char*)&req, sizeof(req));

    req.CommandField = DIMSE_C_CANCEL_RQ;
    req.msg.CCancelRQ.MessageIDBeingRespondedTo = msgId;
    req.msg.CCancelRQ.DataSetType = DIMSE_DATASET_NULL;

    return DIMSE_sendMessageUsingMemoryData(assoc, presId, &req, NULL, NULL, NULL, NULL);
}

OFCondition
DIMSE_checkForCancelRQ(T_ASC_Association * assoc,
    T_ASC_PresentationContextID presId, DIC_US msgId)
{
    T_DIMSE_Message msg;
    T_ASC_PresentationContextID presIdCmd;

    OFCondition cond = DIMSE_receiveCommand(assoc, DIMSE_NONBLOCKING, 0, &presIdCmd, &msg, NULL);

    if (cond.good()) /* could be DIMSE_NODATAAVAILABLE or some error condition */
    {
        if (presIdCmd != presId)
        {
          return makeDcmnetCondition(DIMSEC_INVALIDPRESENTATIONCONTEXTID, OF_error, "DIMSE: Checking for C-CANCEL-RQ, bad presId");
	}
        if (msg.CommandField != DIMSE_C_CANCEL_RQ)
        {
          char buf1[256];
          sprintf(buf1, "DIMSE: Checking for C-CANCEL-RQ, Protocol Error: Cmd=0x%x", msg.CommandField);
          return makeDcmnetCondition(DIMSEC_UNEXPECTEDREQUEST, OF_error, buf1);
	}
	if (msg.msg.CCancelRQ.MessageIDBeingRespondedTo != msgId)
	{
          char buf2[256];
          sprintf(buf2, "DIMSE: Checking for C-CANCEL-RQ, Protocol Error: msgId=%d", msg.msg.CCancelRQ.MessageIDBeingRespondedTo);
          return makeDcmnetCondition(DIMSEC_UNEXPECTEDREQUEST, OF_error, buf2);
	}
    }
    return cond;
}
