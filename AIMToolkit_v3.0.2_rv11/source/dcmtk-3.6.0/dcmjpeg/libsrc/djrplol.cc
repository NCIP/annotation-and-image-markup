/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmjpeg/djrplol.h"


DJ_RPLossless::DJ_RPLossless(int aPrediction, int aPt)
: DcmRepresentationParameter()
, prediction(aPrediction)
, pt(aPt)
{
}

DJ_RPLossless::DJ_RPLossless(const DJ_RPLossless& arg)
: DcmRepresentationParameter(arg)
, prediction(arg.prediction)
, pt(arg.pt)
{
}

DJ_RPLossless::~DJ_RPLossless()
{
}  

DcmRepresentationParameter *DJ_RPLossless::clone() const
{
  return new DJ_RPLossless(*this);
}

const char *DJ_RPLossless::className() const
{
  return "DJ_RPLossless";
}

OFBool DJ_RPLossless::operator==(const DcmRepresentationParameter &arg) const
{
  const char *argname = arg.className();
  if (argname)
  {
    OFString argstring(argname);
    if (argstring == className())
    {
      const DJ_RPLossless& argll = (const DJ_RPLossless &)arg;
      if ((prediction == argll.prediction) && (pt == argll.pt)) return OFTrue;
    }   
  }
  return OFFalse;
}


/*
 * CVS/RCS Log
 * $Log: djrplol.cc,v $
 * Revision 1.3  2010-10-14 13:14:22  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.2  2005-12-08 15:43:49  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.1  2001/11/13 15:58:34  meichel
 * Initial release of module dcmjpeg
 *
 *
 */
