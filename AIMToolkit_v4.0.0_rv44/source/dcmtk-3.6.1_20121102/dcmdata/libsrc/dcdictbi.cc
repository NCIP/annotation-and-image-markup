/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/dcmdata/dcdict.h"

/* There is no builtin data dictionary */
const char* dcmBuiltinDictBuildDate = NULL;

void
DcmDataDictionary::loadBuiltinDictionary()
{
    /*
    ** Empty Stub.
    **
    ** We don't want a builtin data dictionary or
    ** it is not yet created.
    ** A complete builtin dictionary can be created
    ** by mkdictbi (see mkdictbi.cc)
    */
}
