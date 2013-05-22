/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dcrlerp.h"


DcmRLERepresentationParameter::DcmRLERepresentationParameter()
: DcmRepresentationParameter()
{
}

DcmRLERepresentationParameter::DcmRLERepresentationParameter(const DcmRLERepresentationParameter& arg)
: DcmRepresentationParameter(arg)
{
}

DcmRLERepresentationParameter::~DcmRLERepresentationParameter()
{
}  

DcmRepresentationParameter *DcmRLERepresentationParameter::clone() const
{
  return new DcmRLERepresentationParameter(*this);
}

const char *DcmRLERepresentationParameter::className() const
{
  return "DcmRLERepresentationParameter";
}

OFBool DcmRLERepresentationParameter::operator==(const DcmRepresentationParameter &arg) const
{
  const char *argname = arg.className();
  if (argname)
  {
    OFString argstring(argname);
    if (argstring == className()) return OFTrue;
  }
  return OFFalse;
}
