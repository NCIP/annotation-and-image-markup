/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */
#include "dcmtk/dcmnet/dcmlayer.h"
#include "dcmtk/dcmnet/dcmtrans.h"

DcmTransportLayer::~DcmTransportLayer()
{
}

DcmTransportConnection * DcmTransportLayer::createConnection(int openSocket, OFBool useSecureLayer)
{
  if (useSecureLayer) return NULL;  /* secure layer connections not supported */
  else return new DcmTCPConnection(openSocket);
}


/*
 *  $Log: dcmlayer.cc,v $
 *  Revision 1.4  2010-10-14 13:14:28  joergr
 *  Updated copyright header. Added reference to COPYRIGHT file.
 *
 *  Revision 1.3  2005/12/08 15:44:34  meichel
 *  Changed include path schema for all DCMTK header files
 *
 *  Revision 1.2  2001/06/01 15:50:05  meichel
 *  Updated copyright header
 *
 *  Revision 1.1  2000/08/10 14:50:56  meichel
 *  Added initial OpenSSL support.
 *
 *
 */

