/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */
#include "dcmtk/dcmpstat/dvpsvl.h"
#include "dcmtk/dcmpstat/dvpssv.h"      /* for DVPSSoftcopyVOI */
#include "dcmtk/dcmpstat/dvpsdef.h"     /* for constants and macros */
#include "dcmtk/dcmpstat/dvpsri.h"      /* for DVPSReferencedImage, needed by MSVC5 with STL */


/* --------------- class DVPSVOILUT --------------- */

DVPSVOILUT::DVPSVOILUT()
: voiLUTDescriptor(DCM_LUTDescriptor)
, voiLUTExplanation(DCM_LUTExplanation)
, voiLUTData(DCM_LUTData)
{
}

DVPSVOILUT::DVPSVOILUT(const DVPSVOILUT& copy)
: voiLUTDescriptor(copy.voiLUTDescriptor)
, voiLUTExplanation(copy.voiLUTExplanation)
, voiLUTData(copy.voiLUTData)
{
}

DVPSVOILUT::~DVPSVOILUT()
{
}

void DVPSVOILUT::clear()
{
  voiLUTDescriptor.clear();
  voiLUTExplanation.clear();
  voiLUTData.clear();
}

OFCondition DVPSVOILUT::read(DcmItem &dset)
{
  OFCondition result = EC_Normal;
  DcmStack stack;

  READ_FROM_DATASET(DcmUnsignedShort, voiLUTDescriptor)
  READ_FROM_DATASET(DcmLongString, voiLUTExplanation)
  READ_FROM_DATASET(DcmUnsignedShort, voiLUTData)

  if (EC_Normal == result)
  {
    if (voiLUTData.getLength() == 0) result=EC_IllegalCall;
    if (voiLUTDescriptor.getVM() != 3) result=EC_IllegalCall;
  }
  if ((EC_Normal==result) && (voiLUTExplanation.getLength() == 0))
  {
    Uint16 numEntries=0, bits=0;
    voiLUTDescriptor.getUint16(numEntries,0);
    voiLUTDescriptor.getUint16(bits,2);
    char descr[100];
    sprintf(descr, "VOI LUT entries=%u bits=%u", (unsigned int)numEntries, (unsigned int)bits);
    voiLUTExplanation.putString(descr);
  }
  return result;
}

const char *DVPSVOILUT::getExplanation()
{
  char *value = NULL;
  if (EC_Normal != voiLUTExplanation.getString(value)) return NULL;
  return value;
}

OFCondition DVPSVOILUT::assign(DVPSSoftcopyVOI& voi)
{
  return voi.setVOILUT(voiLUTDescriptor, voiLUTData, voiLUTExplanation);
}
