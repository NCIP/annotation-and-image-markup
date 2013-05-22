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


/*
 * CVS/RCS Log
 * $Log: dcrlerp.cc,v $
 * Revision 1.4  2010-10-14 13:14:09  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.3  2009-11-04 09:58:10  uli
 * Switched to logging mechanism provided by the "new" oflog module
 *
 * Revision 1.2  2005-12-08 15:41:35  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.1  2002/06/06 14:52:43  meichel
 * Initial release of the new RLE codec classes
 *   and the dcmcrle/dcmdrle tools in module dcmdata
 *
 *
 */
