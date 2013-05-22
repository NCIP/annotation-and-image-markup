/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#ifndef VRSCAN_H
#define VRSCAN_H

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#include "dcmtk/ofstd/ofstring.h"

#include "dcmtk/dcmdata/dcdefine.h"

class DCMTK_DCMDATA_EXPORT vrscan
{
public:
    static int scan(const OFString& vr, const OFString& value);
private:
    static char* makeBuffer(const OFString& vr, const OFString& value, size_t& size);
};

#endif // VRSCAN_H
