/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dcostrmb.h"
#include "dcmtk/dcmdata/dcerror.h"


DcmBufferConsumer::DcmBufferConsumer(void *buf, offile_off_t bufLen)
: DcmConsumer()
, buffer_(OFstatic_cast(unsigned char *, buf))
, bufSize_(bufLen)
, filled_(0)
, status_(EC_Normal)
{
  if ((buffer_ == NULL) || (bufSize_ == 0)) status_ = EC_IllegalCall;
}

DcmBufferConsumer::~DcmBufferConsumer()
{
}

OFBool DcmBufferConsumer::good() const
{
  return status_.good();
}

OFCondition DcmBufferConsumer::status() const
{
  return status_;
}

OFBool DcmBufferConsumer::isFlushed() const
{
  return (filled_ == 0);
}

offile_off_t DcmBufferConsumer::avail() const
{
  return bufSize_ - filled_;
}

offile_off_t DcmBufferConsumer::write(const void *buf, offile_off_t buflen)
{
  offile_off_t result = 0;
  if (status_.good() && buf && buflen)
  {
    result = bufSize_ - filled_;
    if (result > buflen) result = buflen;
    memcpy(buffer_+ filled_, buf, OFstatic_cast(size_t, result));
    filled_ += result;
  }
  return result;
}

void DcmBufferConsumer::flush()
{
  // nothing to flush
}

void DcmBufferConsumer::flushBuffer(void *& buffer, offile_off_t& length)
{
  buffer = buffer_;
  length = filled_;
  filled_ = 0;
}

/* ======================================================================= */

DcmOutputBufferStream::DcmOutputBufferStream(void *buf, offile_off_t bufLen)
: DcmOutputStream(&consumer_) // safe because DcmOutputStream only stores pointer
, consumer_(buf, bufLen)
{
}

DcmOutputBufferStream::~DcmOutputBufferStream()
{
#ifdef DEBUG
  if (! isFlushed())
  {
    DCMDATA_WARN("DcmOutputBufferStream: Closing unflushed DcmOutputBufferStream, loss of data!");
  }
#endif
}

void DcmOutputBufferStream::flushBuffer(void *& buffer, offile_off_t& length)
{
  consumer_.flushBuffer(buffer, length);
}
