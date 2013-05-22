/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"

#include "dcmtk/dcmdata/dctypes.h"

OFLogger DCM_dcmdataLogger = OFLog::getLogger("dcmtk.dcmdata");

/* print flags */
const size_t DCMTypes::PF_shortenLongTagValues  = 1 << 0;
const size_t DCMTypes::PF_showTreeStructure     = 1 << 1;
const size_t DCMTypes::PF_doNotMapUIDsToNames   = 1 << 2;
const size_t DCMTypes::PF_convertToMarkup       = 1 << 3;
const size_t DCMTypes::PF_convertToOctalNumbers = 1 << 4;
const size_t DCMTypes::PF_useANSIEscapeCodes    = 1 << 5;

/* writeXML flags */
const size_t DCMTypes::XF_addDocumentType       = 1 << 0;
const size_t DCMTypes::XF_writeBinaryData       = 1 << 1;
const size_t DCMTypes::XF_encodeBase64          = 1 << 2;
const size_t DCMTypes::XF_useXMLNamespace       = 1 << 3;
const size_t DCMTypes::XF_embedDocumentType     = 1 << 4;
const size_t DCMTypes::XF_omitDataElementName   = 1 << 5;
const size_t DCMTypes::XF_convertNonASCII       = 1 << 6;
const size_t DCMTypes::XF_useNativeModel        = 1 << 7;
