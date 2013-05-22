/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmjpls/djrparam.h"
#include "dcmtk/ofstd/ofstd.h"

DJLSRepresentationParameter::DJLSRepresentationParameter(
    Uint16 nearlosslessDeviation,
    OFBool losslessProcess)
: DcmRepresentationParameter()
, nearlosslessDeviation_(nearlosslessDeviation)
, losslessProcess_(losslessProcess)
{
}

DJLSRepresentationParameter::DJLSRepresentationParameter(const DJLSRepresentationParameter& arg)
: DcmRepresentationParameter(arg)
, nearlosslessDeviation_(arg.nearlosslessDeviation_)
, losslessProcess_(arg.losslessProcess_)
{
}

DJLSRepresentationParameter::~DJLSRepresentationParameter()
{
}  

DcmRepresentationParameter *DJLSRepresentationParameter::clone() const
{
  return new DJLSRepresentationParameter(*this);
}

const char *DJLSRepresentationParameter::className() const
{
  return "DJLSRepresentationParameter";
}

OFBool DJLSRepresentationParameter::operator==(const DcmRepresentationParameter &arg) const
{
  const char *argname = arg.className();
  if (argname)
  {
    OFString argstring(argname);
    if (argstring == className())
    {
      const DJLSRepresentationParameter& argll = OFreinterpret_cast(const DJLSRepresentationParameter &, arg);
      if (losslessProcess_ && argll.losslessProcess_) return OFTrue;
      else if (losslessProcess_ != argll.losslessProcess_) return OFFalse;
	  else if (nearlosslessDeviation_ != argll.nearlosslessDeviation_) return OFFalse;
      return OFTrue;
    }	
  }
  return OFFalse;
}
