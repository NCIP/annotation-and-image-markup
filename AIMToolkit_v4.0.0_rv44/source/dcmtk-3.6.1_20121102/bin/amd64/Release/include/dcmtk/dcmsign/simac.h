/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef SIMAC_H
#define SIMAC_H

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmsign/sitypes.h"

#ifdef WITH_OPENSSL

/**
 * a base class for all classes that implement hash functions.
 */
class DCMTK_DCMSIGN_EXPORT SiMAC
{
public:

  /// default constructor
  SiMAC() { }

  /// destructor
  virtual ~SiMAC() { }

  /** initializes the MAC algorithm.
   *  @return status code
   */
  virtual OFCondition initialize() = 0;

  /** feeds data into the MAC algorithm
   *  @param data pointer to raw data to be fed into the MAC, must not be NULL
   *  @param length number of bytes in raw data array
   *  @return status code
   */
  virtual OFCondition digest(const unsigned char *data, unsigned long length) = 0;

  /** finalizes the MAC and writes it to the given output array,
   *  which must be at least getSize() bytes large.
   *  After a call to finalize, the MAC algorithm must be initialized
   *  again, see initialize().
   *  @param result pointer to array of getSize() bytes into which the MAC is written
   *  @return status code
   */
  virtual OFCondition finalize(unsigned char *result) = 0;

  /** returns the size of a MAC in bytes.
   *  @return block size for this MAC algorithm
   */
  virtual unsigned long getSize() const = 0;

  /** returns the type of MAC algorithm computed by this object
   *  @return type of MAC algorithm
   */
  virtual E_MACType macType() const = 0;

  /** returns the DICOM identifier for this MAC algorithm
   *  @return DICOM defined term for algorithm
   */
  virtual const char *getDefinedTerm() const = 0;

};

#endif
#endif
