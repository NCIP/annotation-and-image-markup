/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"

#define OFTEST_OFSTD_ONLY
#include "dcmtk/ofstd/oftest.h"
#include "dcmtk/ofstd/ofmap.h"


OFTEST(ofstd_OFMap)
{
    OFMap<int, int> m;
    OFMap<int, int>::iterator it;
    int i;

    // Fill a map with some entries
    for (i = 1; i <= 6; ++i)
        m[i] = i;

    // and verify they were really added
    OFCHECK_EQUAL(m.size(), 6);

    it = m.begin();
    OFCHECK(it != m.end());

    for (i = 1; i <= 6; ++i)
    {
        OFCHECK_EQUAL(m[i], i);
        OFCHECK_EQUAL(it->first, i);
        OFCHECK_EQUAL(it->second, i);
        it++;
    }

    OFCHECK(it == m.end());

    // Now check if removing "4" really removes it
    it = m.find(4);
    OFCHECK(it != m.end());
    m.erase(it);
    OFCHECK(m.find(4) == m.end());

    // Do the same again but using a different function for removing "5"
    OFCHECK(m.find(5) != m.end());
    m.erase(5);
    OFCHECK(m.find(5) == m.end());

    // Now remove a range of objects by removing 1 and 2
    OFCHECK_EQUAL(m.size(), 4);
    m.erase(m.find(1), m.find(3));
    OFCHECK_EQUAL(m.size(), 2);
    OFCHECK(m.find(2) == m.end());

    OFCHECK_EQUAL(m.size(), 2);
    OFCHECK_EQUAL(m[3], 3);
}
