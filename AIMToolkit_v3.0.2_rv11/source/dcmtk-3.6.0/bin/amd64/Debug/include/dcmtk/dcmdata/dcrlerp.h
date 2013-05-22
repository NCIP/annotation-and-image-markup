/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef DCRLERP_H
#define DCRLERP_H

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dcpixel.h" /* for class DcmRepresentationParameter */

/** representation parameter for RLE.
 *  This is actually a dummy class since there are no compression
 *  options in the RLE algorithm.
 */
class DcmRLERepresentationParameter: public DcmRepresentationParameter
{
public:

  /// constructor
  DcmRLERepresentationParameter();

  /// copy constructor
  DcmRLERepresentationParameter(const DcmRLERepresentationParameter& arg);

  /// destructor
  virtual ~DcmRLERepresentationParameter();
  
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

};

#endif

/*
 * CVS/RCS Log
 * $Log: dcrlerp.h,v $
 * Revision 1.4  2010-10-14 13:15:42  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.3  2009-11-04 09:58:07  uli
 * Switched to logging mechanism provided by the "new" oflog module
 *
 * Revision 1.2  2005-12-08 16:28:40  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.1  2002/06/06 14:52:38  meichel
 * Initial release of the new RLE codec classes
 *   and the dcmcrle/dcmdrle tools in module dcmdata
 *
 *
 */
