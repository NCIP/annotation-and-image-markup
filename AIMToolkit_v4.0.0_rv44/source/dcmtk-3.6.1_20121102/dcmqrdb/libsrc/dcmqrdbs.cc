/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */
#include "dcmtk/dcmqrdb/dcmqrdbs.h"
#include "dcmtk/dcmdata/dcdatset.h"    /* for class DcmDataset */

#define INCLUDE_CSTDDEF
#include "dcmtk/ofstd/ofstdinc.h"


DcmQueryRetrieveDatabaseStatus::DcmQueryRetrieveDatabaseStatus(Uint16 s)
: status_(s)
, statusDetail_(NULL)
{
}

DcmQueryRetrieveDatabaseStatus::DcmQueryRetrieveDatabaseStatus(const DcmQueryRetrieveDatabaseStatus& org)
: status_(org.status_)
, statusDetail_(NULL)
{
  if (org.statusDetail_) statusDetail_ = OFstatic_cast(DcmDataset *, org.statusDetail_->clone());
}

DcmQueryRetrieveDatabaseStatus::~DcmQueryRetrieveDatabaseStatus()
{
  delete statusDetail_;
}

DcmQueryRetrieveDatabaseStatus& DcmQueryRetrieveDatabaseStatus::operator=(const DcmQueryRetrieveDatabaseStatus& org)
{
  if (this != &org)
  {
    status_ = org.status_;
    if (org.statusDetail_ != statusDetail_)
    {
      delete statusDetail_;
      if (org.statusDetail_) statusDetail_ = OFstatic_cast(DcmDataset *, org.statusDetail_->clone()); else statusDetail_ = NULL;
    }
  }
  return *this;
}

void DcmQueryRetrieveDatabaseStatus::deleteStatusDetail()
{
  delete statusDetail_;
  statusDetail_ = NULL;
}

DcmDataset *DcmQueryRetrieveDatabaseStatus::extractStatusDetail()
{
  DcmDataset *result = statusDetail_;
  statusDetail_ = NULL;
  return result;
}
