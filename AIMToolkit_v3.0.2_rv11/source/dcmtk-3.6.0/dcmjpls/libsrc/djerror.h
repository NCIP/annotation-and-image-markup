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
  static const OFCondition& convert(JLS_ERROR error)
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

/*
 * CVS/RCS Log:
 * $Log: djerror.h,v $
 * Revision 1.5  2010-10-14 13:20:24  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.4  2010-02-25 08:50:38  uli
 * Updated to latest CharLS version.
 *
 * Revision 1.3  2010-01-19 15:19:06  uli
 * Made file names fit into 8.3 format.
 *
 * Revision 1.2  2009-10-07 13:16:47  uli
 * Switched to logging mechanism provided by the "new" oflog module.
 *
 * Revision 1.1  2009-07-31 09:05:43  meichel
 * Added more detailed error messages, minor code clean-up
 *
 *
 */
