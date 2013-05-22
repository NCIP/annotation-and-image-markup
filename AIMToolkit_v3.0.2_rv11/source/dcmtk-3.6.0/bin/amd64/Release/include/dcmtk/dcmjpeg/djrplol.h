/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef DJRPLOL_H
#define DJRPLOL_H

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dcpixel.h" /* for class DcmRepresentationParameter */

/** representation parameter for lossless JPEG
 */
class DJ_RPLossless: public DcmRepresentationParameter
{
public:

  /** constructor
   *  @param aPrediction prediction value
   *  @param aPt point transform value
   */
  DJ_RPLossless(int aPrediction=1, int aPt=0);

  /// copy constructor
  DJ_RPLossless(const DJ_RPLossless& arg);

  /// destructor
  virtual ~DJ_RPLossless();
  
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

  /** returns the prediction value
   *  @return prediction value
   */
  int getPrediction() const
  {
    return prediction;
  }

  /** returns the point transform 
   *  @return point transform 
   */
  int getPointTransformation() const 
  {
    return pt;
  }

private:

  /// prediction value
  int prediction; 

  /// point transform value
  int pt;
};

#endif

/*
 * CVS/RCS Log
 * $Log: djrplol.h,v $
 * Revision 1.3  2010-10-14 13:17:17  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.2  2005-12-08 16:59:36  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.1  2001/11/13 15:56:29  meichel
 * Initial release of module dcmjpeg
 *
 *
 */
