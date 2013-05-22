/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#include "dcmtk/dcmdata/libi2d/i2dplsc.h"
#include "dcmtk/dcmdata/libi2d/i2doutpl.h"
#include "dcmtk/dcmdata/dcdeftag.h"        /* for DCM_ defines */
#include "dcmtk/dcmdata/dcuid.h"           /* for UID_ defines */


I2DOutputPlugSC::I2DOutputPlugSC()
{
  DCMDATA_LIBI2D_DEBUG("I2DOutputPlugSC: Output plugin for Secondary Capture initialized");
}

OFString I2DOutputPlugSC::ident()
{
  return "Secondary Capture Image SOP Class";
}

void I2DOutputPlugSC::supportedSOPClassUIDs(OFList<OFString>& suppSOPs)
{
  suppSOPs.push_back(UID_SecondaryCaptureImageStorage);
}


OFCondition I2DOutputPlugSC::convert(DcmDataset &dataset) const
{
  DCMDATA_LIBI2D_DEBUG("I2DOutputPlugSC: Inserting SC specific attributes");
  OFCondition cond;
  cond = dataset.putAndInsertOFStringArray(DCM_SOPClassUID, UID_SecondaryCaptureImageStorage);

  return EC_Normal;
}


OFString I2DOutputPlugSC::isValid(DcmDataset& dataset) const
{
  OFString err;
  // Just return if checking was disabled
  if (!m_doAttribChecking)
    return err;

  DCMDATA_LIBI2D_DEBUG("I2DOutputPlugSC: Checking SC specific attributes");
  err += checkAndInventType1Attrib(DCM_ConversionType, &dataset, "WSD"); // WSD="Workstation"

  return err;
}


I2DOutputPlugSC::~I2DOutputPlugSC()
{
}
