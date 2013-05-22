/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"

#include "dcmtk/ofstd/ofstack.h"

#define OFTEST_OFSTD_ONLY
#include "dcmtk/ofstd/oftest.h"


OFTEST(ofstd_OFStack)
{
    OFStack<int> st;
    int i;
    st.push(1);
    st.push(2);
    st.push(3);

    OFStack<int> nst(st);

    OFCHECK_EQUAL(st.size(), 3);
    for (i = 3; i >= 1; i--)
    {
        OFCHECK(!st.empty());
        OFCHECK_EQUAL(i, st.top());
        st.pop();
    }

    OFCHECK_EQUAL(nst.size(), 3);
    for (i = 3; i >= 1; i--)
    {
        OFCHECK(!nst.empty());
        OFCHECK_EQUAL(i, nst.top());
        nst.pop();
    }
}
