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
