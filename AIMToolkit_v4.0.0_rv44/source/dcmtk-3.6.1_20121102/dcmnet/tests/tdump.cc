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
#include "dcmtk/dcmnet/dimse.h"


OFTEST(dcmnet_dimseDump_nullByte)
{
    const char expected[] = "===================== INCOMING DIMSE MESSAGE ====================\nMessage Type                  : C-ECHO RQ\nMessage ID                    : 42\nData Set                      : present\n-----------------------------------------------------------------(fffe,e000) na (Item with explicit length #=1)          #   0, 1 Item\n(0010,0010) PN [1.2\0]                                   #   4, 1 PatientName\n(fffe,e00d) na (ItemDelimitationItem for re-encoding)   #   0, 0 ItemDelimitationItem\n======================= END DIMSE MESSAGE =======================";
    OFString result;
    T_DIMSE_C_EchoRQ rq = { 42, "1.2.3\0", DIMSE_DATASET_PRESENT };

    dcmEnableAutomaticInputDataCorrection.set(OFFalse);
    DcmUniqueIdentifier* id = new DcmUniqueIdentifier(DCM_PatientName);
    id->putString("1.2\0", 4);
    dcmEnableAutomaticInputDataCorrection.set(OFTrue);

    DcmItem item;
    OFCondition cond = item.insert(id);
    OFCHECK(cond.good());

    // There was a bug in DIMSE_dumpMessage() where the \0-byte caused the
    // message to be cut off. This is what we are testing for.
    DIMSE_dumpMessage(result, rq, DIMSE_INCOMING, &item, 0);
    OFCHECK_EQUAL(OFString(expected, sizeof(expected)-1), result);
}
