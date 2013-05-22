/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"
#include "dcmtk/ofstd/ofcond.h"


/* ---------- global condition constants ---------- */

makeOFConditionConst(EC_Normal,                      0, 0, OF_ok,      "Normal");
makeOFConditionConst(EC_IllegalParameter,            0, 1, OF_error,   "Illegal parameter");
makeOFConditionConst(EC_MemoryExhausted,             0, 2, OF_failure, "Virtual Memory exhausted");
makeOFConditionConst(EC_NoEncodingLibrary,           0, 3, OF_error,   "No character encoding library available");
makeOFConditionConst(EC_NoEncodingSelected,          0, 4, OF_error,   "No character encoding selected");
// codes 5..8 are used for dynamically created error messages (see below constants)
makeOFConditionConst(EC_CouldNotCreateTemporaryFile, 0, 9, OF_error,   "Could not create temporary file");
makeOFConditionConst(EC_InvalidFilename,             0, 10, OF_error,  "Invalid filename");


// NOTE:
// error codes 1024..2047 are reserved for inter-process communication
// errors defined elsewhere in module ofstd

const unsigned short EC_CODE_CannotOpenEncoding     = 5;
const unsigned short EC_CODE_CannotCloseEncoding    = 6;
const unsigned short EC_CODE_CannotConvertEncoding  = 7;
const unsigned short EC_CODE_CannotControlConverter = 8;
