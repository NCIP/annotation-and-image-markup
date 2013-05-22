/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef SITSTAMP_H
#define SITSTAMP_H

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmsign/sitypes.h"

#ifdef WITH_OPENSSL

class DcmItem;
 
/** pure virtual base class for a timestamp client.
 *  Instances of derived classes are able to request timestamps from a timestamp service.
 *  Timestamps are not supported (yet).
 */
class DCMTK_DCMSIGN_EXPORT SiTimeStamp
{    
public:

  /// default constructor
  SiTimeStamp() { }
  
  /// destructor
  virtual ~SiTimeStamp() { }

  /** takes a block of raw data and requests a time stamp for this raw data.
   *  @param inputData pointer to raw data
   *  @param inputDataSize length of raw data block in bytes
   *  @return status code
   */
  virtual OFCondition stamp(
    const unsigned char *inputData, 
    unsigned long inputDataSize) = 0;

  /** writes the current timestamp into an item of the Digital Signatures Sequence
   *  and creates the timestamp type information in the item.
   *  @param item item of the DigitalSignatureSQ to which the timestamp is written
   *  @return dcmdata OFCondition status code
   */
  virtual OFCondition write(DcmItem& item) = 0;

};

#endif
#endif
