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
#define INCLUDE_CERRNO
#include "dcmtk/ofstd/ofstdinc.h"

#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef HAVE_SYS_SELECT_H
#include <sys/select.h>
#endif

#include "dcmtk/dcmnet/dicom.h"
#include "dcmtk/dcmnet/lst.h"
#include "dcmtk/dcmnet/cond.h"
#include "dcmtk/dcmnet/dul.h"
#include "dulstruc.h"
#include "dulpriv.h"
#include "dcmtk/dcmnet/dcmtrans.h"

OFBool
DUL_dataWaiting(DUL_ASSOCIATIONKEY * callerAssociation, int timeout)
{
    PRIVATE_ASSOCIATIONKEY * association = (PRIVATE_ASSOCIATIONKEY *)callerAssociation;
    if ((association==NULL)||(association->connection == NULL)) return OFFalse;
    return association->connection->networkDataAvailable(timeout);
}

DcmTransportConnection *DUL_getTransportConnection(DUL_ASSOCIATIONKEY * callerAssociation)
{
  if (callerAssociation == NULL) return NULL;
  else return ((PRIVATE_ASSOCIATIONKEY *)callerAssociation)->connection;
}

int
DUL_networkSocket(DUL_NETWORKKEY * callerNet)
{
    if (callerNet == NULL) return -1;
    PRIVATE_NETWORKKEY *net = (PRIVATE_NETWORKKEY*)callerNet;
    return net->networkSpecific.TCP.listenSocket;
}

OFBool
DUL_associationWaiting(DUL_NETWORKKEY * callerNet, int timeout)
{
    PRIVATE_NETWORKKEY *net;
    int                 s;
    OFBool             assocWaiting = OFFalse;
    struct timeval      t;
    fd_set              fdset;
    int                 nfound;

    if (callerNet == NULL)
        return OFFalse;

    net = (PRIVATE_NETWORKKEY*)callerNet;

    s = net->networkSpecific.TCP.listenSocket;

    FD_ZERO(&fdset);
#ifdef __MINGW32__
    // on MinGW, FD_SET expects an unsigned first argument
    FD_SET((unsigned int) s, &fdset);
#else
    FD_SET(s, &fdset);
#endif

    t.tv_sec = timeout;
    t.tv_usec = 0;
#ifdef HAVE_INTP_SELECT
    nfound = select(s + 1, (int *)(&fdset), NULL, NULL, &t);
#else
    nfound = select(s + 1, &fdset, NULL, NULL, &t);
#endif
    if (nfound <= 0) assocWaiting = OFFalse;
    else
    {
        if (FD_ISSET(s, &fdset))
            assocWaiting = OFTrue;
        else                /* This one should not really happen */
            assocWaiting = OFFalse;
    }

    return assocWaiting;
}
