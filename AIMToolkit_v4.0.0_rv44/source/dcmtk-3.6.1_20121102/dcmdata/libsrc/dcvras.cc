/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#include "dcmtk/dcmdata/dcvras.h"


// ********************************


DcmAgeString::DcmAgeString(const DcmTag &tag,
                           const Uint32 len)
  : DcmByteString(tag, len)
{
    setMaxLength(4);
}


DcmAgeString::DcmAgeString(const DcmAgeString &old)
  : DcmByteString(old)
{
}


DcmAgeString::~DcmAgeString()
{
}

DcmAgeString &DcmAgeString::operator=(const DcmAgeString &obj)
{
    DcmByteString::operator=(obj);
    return *this;
}


OFCondition DcmAgeString::copyFrom(const DcmObject& rhs)
{
  if (this != &rhs)
  {
    if (rhs.ident() != ident()) return EC_IllegalCall;
    *this = OFstatic_cast(const DcmAgeString &, rhs);
  }
  return EC_Normal;
}


// ********************************


DcmEVR DcmAgeString::ident() const
{
    return EVR_AS;
}


OFCondition DcmAgeString::checkValue(const OFString &vm,
                                     const OFBool /*oldFormat*/)
{
    OFString strVal;
    /* get "raw value" without any modifications (if possible) */
    OFCondition l_error = getStringValue(strVal);
    if (l_error.good())
        l_error = DcmAgeString::checkStringValue(strVal, vm);
    return l_error;
}


// ********************************


OFCondition DcmAgeString::checkStringValue(const OFString &value,
                                           const OFString &vm)
{
    return DcmByteString::checkStringValue(value, vm, "as", 1);
}
