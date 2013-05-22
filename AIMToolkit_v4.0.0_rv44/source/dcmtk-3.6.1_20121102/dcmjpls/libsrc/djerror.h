/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef DJERROR_H
#define DJERROR_H

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmjpls/djlsutil.h" /* For the OFCondition codes */
#include "intrface.h" /* CharLS include */

/** Helper class for converting between dcmjpls and CharLS error codes
 */
class DJLSError
{
private:
  /// private undefined constructor
  DJLSError();

public:

  /** This method converts a CharLS error code into a dcmjpls OFCondition
   *  @param error The CharLS error code
   *  @return The OFCondition
   */
  static const OFConditionConst& convert(JLS_ERROR error)
  {
    switch (error)
    {
      case OK:
        return EC_Normal;
      case UncompressedBufferTooSmall:
        return EC_JLSUncompressedBufferTooSmall;
      case CompressedBufferTooSmall:
        return EC_JLSCompressedBufferTooSmall;
      case ImageTypeNotSupported:
        return EC_JLSCodecUnsupportedImageType;
      case InvalidJlsParameters:
        return EC_JLSCodecInvalidParameters;
      case ParameterValueNotSupported:
        return EC_JLSCodecUnsupportedValue;
      case InvalidCompressedData:
        return EC_JLSInvalidCompressedData;
      case UnsupportedBitDepthForTransform:
        return EC_JLSUnsupportedBitDepthForTransform;
      case UnsupportedColorTransform:
        return EC_JLSUnsupportedColorTransform;
      case TooMuchCompressedData:
        return EC_JLSTooMuchCompressedData;
      default:
        return EC_IllegalParameter;
    }
  }
};

#endif
