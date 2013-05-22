/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#include "dcmtk/ofstd/oftest.h"
#include "dcmtk/dcmrt/drmplan.h"


OFTEST(dcmrt_search)
{
    DRTPlan plan;
    DRTBeamSequence &seq = plan.getBeamSequence();
    DRTBeamSequence::Item *item1, *item2, *item3;
    // Get the empty default item
    DRTBeamSequence::Item &empty = seq.getCurrentItem();

    // Add some elements
    OFCHECK(seq.addItem(item1).good());
    OFCHECK(item1->setBeamNumber("42").good());
    OFCHECK(seq.addItem(item2).good());
    OFCHECK(item2->setBeamNumber("1337").good());
    OFCHECK(seq.addItem(item3).good());
    OFCHECK(item3->setBeamNumber("21").good());

    // Check if finding works correctly
    OFCHECK_EQUAL(&plan.getBeam(1337), item2);
    OFCHECK_EQUAL(&plan.getBeam(42), item1);
    OFCHECK_EQUAL(&plan.getBeam(21), item3);
    OFCHECK_EQUAL(&plan.getBeam(100), &empty);
}
