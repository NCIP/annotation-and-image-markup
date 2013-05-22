/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/oflog/helpers/sleep.h"

#include "dcmtk/ofstd/ofstd.h"

using namespace log4cplus;


///////////////////////////////////////////////////////////////////////////////
// public methods
///////////////////////////////////////////////////////////////////////////////

void
log4cplus::helpers::sleep(unsigned long secs)
{
    while (secs > 0) {
        secs = OFStandard::sleep(secs);
    }
}
