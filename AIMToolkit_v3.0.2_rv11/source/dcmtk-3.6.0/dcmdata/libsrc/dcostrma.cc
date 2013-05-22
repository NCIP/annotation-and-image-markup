/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dcostrma.h"
#include "dcmtk/dcmdata/dcostrmz.h" /* for DcmZLibOutputFilter */
#include "dcmtk/dcmdata/dcerror.h"  /* for EC_IllegalCall */

DcmOutputStream::DcmOutputStream(DcmConsumer *initial)
: current_(initial)
, compressionFilter_(NULL)
, tell_(0)
{
}

DcmOutputStream::~DcmOutputStream()
{
  // we cannot access the stream anymore at this point because the
  // consumer has most probably already been deleted.
  delete compressionFilter_;
}

OFCondition DcmOutputStream::installCompressionFilter(E_StreamCompression filterType)
{
  OFCondition result = EC_Normal;
  if (compressionFilter_) result = EC_DoubleCompressionFilters;
  else
  {
    switch (filterType)
    {
#ifdef WITH_ZLIB
      case ESC_zlib:
        compressionFilter_ = new DcmZLibOutputFilter();
        if (compressionFilter_) 
        {
          compressionFilter_->append(*current_);
          current_ = compressionFilter_;
        } else result = EC_MemoryExhausted;        
        break;
#endif
      case ESC_none:
      case ESC_unsupported:
        result = EC_UnsupportedEncoding; 
        break;
    }
  }
  return result;
}

OFBool DcmOutputStream::good() const
{
  return current_->good();
}

OFCondition DcmOutputStream::status() const
{
  return current_->status();
}

OFBool DcmOutputStream::isFlushed() const
{
  return current_->isFlushed();
}

offile_off_t DcmOutputStream::avail() const
{
  return current_->avail();
}

offile_off_t DcmOutputStream::write(const void *buf, offile_off_t buflen)
{
  offile_off_t result = current_->write(buf, buflen);
  tell_ += result;
  return result;
}

void DcmOutputStream::flush()
{
  current_->flush();
}

offile_off_t DcmOutputStream::tell() const
{
  return tell_;
}


/*
 * CVS/RCS Log:
 * $Log: dcostrma.cc,v $
 * Revision 1.5  2010-10-14 13:14:08  joergr
 * Updated copyright header. Added reference to COPYRIGHT file.
 *
 * Revision 1.4  2009-11-04 09:58:10  uli
 * Switched to logging mechanism provided by the "new" oflog module
 *
 * Revision 1.3  2007-02-19 16:06:10  meichel
 * Class DcmOutputStream and related classes are now safe for use with
 *   large files (2 GBytes or more) if supported by compiler and operating system.
 *
 * Revision 1.2  2005/12/08 15:41:20  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.1  2002/08/27 16:55:52  meichel
 * Initial release of new DICOM I/O stream classes that add support for stream
 *   compression (deflated little endian explicit VR transfer syntax)
 *
 *
 */
