/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#include "dcmtk/ofstd/oftest.h"
#include "dcmtk/dcmdata/dcvrui.h"
#include "dcmtk/dcmdata/dcdeftag.h"


OFTEST(dcmdata_uniqueIdentifier_1)
{
  /* test UI value with 0-byte padding */
  OFString value;
  DcmUniqueIdentifier sopInstanceUID(DCM_SOPInstanceUID);
  dcmEnableAutomaticInputDataCorrection.set(OFTrue);
  OFCHECK(sopInstanceUID.putString("1.2.3.4\0", 8).good());
  OFCHECK(sopInstanceUID.checkValue("1").good());
  OFCHECK(sopInstanceUID.getOFString(value, 0).good());
  OFCHECK_EQUAL(value, "1.2.3.4");
  // switch automatic data correct off
  dcmEnableAutomaticInputDataCorrection.set(OFFalse);
  OFCHECK(sopInstanceUID.putString("1.2.3.4\\5.6.7.8").good());
  OFCHECK(sopInstanceUID.checkValue("2").good());
  OFCHECK(sopInstanceUID.putString("1.2.3.4\\5.6.7.8\0", 16).good());
  // the trailing 0-byte is still there, which leads to an error
  OFCHECK(sopInstanceUID.checkValue("2").bad());
  OFCHECK(sopInstanceUID.getOFString(value, 1 /*, normalize = OFTrue */).good());
  OFCHECK_EQUAL(value, "5.6.7.8");
  OFCHECK(sopInstanceUID.getOFString(value, 1, OFFalse /*normalize*/).good());
  OFCHECK_EQUAL(value, OFString("5.6.7.8\0", 8));
}


OFTEST(dcmdata_uniqueIdentifier_2)
{
  /* test UI value with space character padding */
  OFString value;
  DcmUniqueIdentifier sopInstanceUID(DCM_SOPInstanceUID);
  dcmEnableAutomaticInputDataCorrection.set(OFTrue);
  OFCHECK(sopInstanceUID.putString("1.2.3.4 ").good());
  OFCHECK(sopInstanceUID.checkValue("1").good());
  OFCHECK(sopInstanceUID.putString("1.2.3.4  ").good());
  OFCHECK(sopInstanceUID.checkValue("1").good());
  OFCHECK(sopInstanceUID.getOFString(value, 0).good());
  OFCHECK_EQUAL(value, "1.2.3.4");
  // we also accept leading and embedded space characters
  OFCHECK(sopInstanceUID.putString(" 1.2.3.4 ").good());
  OFCHECK(sopInstanceUID.checkValue("1").good());
  OFCHECK(sopInstanceUID.putString("1.2. 3.4").good());
  OFCHECK(sopInstanceUID.checkValue("1").good());
  OFCHECK(sopInstanceUID.getOFString(value, 0).good());
  OFCHECK_EQUAL(value, "1.2.3.4");
  // switch automatic data correct off
  dcmEnableAutomaticInputDataCorrection.set(OFFalse);
  OFCHECK(sopInstanceUID.putString("1.2.3.4 ").good());
  OFCHECK(sopInstanceUID.checkValue("1").bad());
  OFCHECK(sopInstanceUID.getOFString(value, 0).good());
  OFCHECK_EQUAL(value, "1.2.3.4 ");
  OFCHECK(sopInstanceUID.putString("1.2.3.4\\5.6.7.8 ").good());
  OFCHECK(sopInstanceUID.checkValue("2").bad());
  OFCHECK(sopInstanceUID.getOFString(value, 0).good());
  OFCHECK_EQUAL(value, "1.2.3.4");
  OFCHECK(sopInstanceUID.getOFString(value, 1).good());
  OFCHECK_EQUAL(value, "5.6.7.8 ");
}
