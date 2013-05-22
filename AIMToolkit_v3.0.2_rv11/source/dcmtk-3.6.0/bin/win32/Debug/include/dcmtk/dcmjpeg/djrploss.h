/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef DJRPLOSS_H
#define DJRPLOSS_H

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dcpixel.h" /* for class DcmRepresentationParameter */

/** representation parameter for lossy JPEG
 */
class DJ_RPLossy: public DcmRepresentationParameter
{
public:

  /** constructor
   *  @param aQuality quality factor
   */
  DJ_RPLossy(int aQuality=90);

  /// copy constructor
  DJ_RPLossy(const DJ_RPLossy& arg);

  /// destructor
  virtual ~DJ_RPLossy();
  
  /** this methods creates a copy of type DcmRepresentationParameter *
   *  it must be overweritten in every subclass.
   *  @return copy of this object
   */
  virtual DcmRepresentationParameter *clone() const;

  /** returns the class name as string.
   *  can be used in operator== as poor man's RTTI replacement.
   */
  virtual const char *className() const;

  /** compares an object to another DcmRepresentationParameter.
   *  Implementation must make sure that classes are comparable.
   *  @param arg representation parameter to compare with
   *  @return true if equal, false otherwise.
   */
  virtual OFBool operator==(const DcmRepresentationParameter &arg) const;

  /** returns the compression quality factor
   *  @return compression quality factor
   */
  int getQuality() const
  {
    return quality;
  }

private:

  /// compression quality factor
  int quality;

};


#endif

/*
 * CVS/RCS Log
 * $Log: djrploss.h,v $
 * Revision 1.3  2010-10-14 13:17:17  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.2  2005-12-08 16:59:37  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.1  2001/11/13 15:56:29  meichel
 * Initial release of module dcmjpeg
 *
 *
 */
