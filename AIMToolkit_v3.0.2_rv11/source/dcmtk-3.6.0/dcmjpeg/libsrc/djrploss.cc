/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmjpeg/djrploss.h"


DJ_RPLossy::DJ_RPLossy(int aQuality)
: DcmRepresentationParameter()
, quality(aQuality)
{
}

DJ_RPLossy::DJ_RPLossy(const DJ_RPLossy& arg)
: DcmRepresentationParameter(arg)
, quality(arg.quality)
{
}

DJ_RPLossy::~DJ_RPLossy()
{
}  

DcmRepresentationParameter *DJ_RPLossy::clone() const
{
  return new DJ_RPLossy(*this);
}

const char *DJ_RPLossy::className() const
{
  return "DJ_RPLossy";
}

OFBool DJ_RPLossy::operator==(const DcmRepresentationParameter &arg) const
{
  const char *argname = arg.className();
  if (argname)
  {
    OFString argstring(argname);
    if (argstring == className())
    {
      const DJ_RPLossy& argll = (const DJ_RPLossy &)arg;
      if (quality == argll.quality) return OFTrue;
    }   
  }
  return OFFalse;
}


/*
 * CVS/RCS Log
 * $Log: djrploss.cc,v $
 * Revision 1.3  2010-10-14 13:14:22  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.2  2005-12-08 15:43:50  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.1  2001/11/13 15:58:34  meichel
 * Initial release of module dcmjpeg
 *
 *
 */
