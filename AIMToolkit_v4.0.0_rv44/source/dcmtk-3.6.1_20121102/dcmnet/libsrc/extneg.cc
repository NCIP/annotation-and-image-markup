/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h" /* make sure OS specific configuration is included first */
#include "dcmtk/dcmnet/extneg.h"


void appendList(const SOPClassExtendedNegotiationSubItemList& from, SOPClassExtendedNegotiationSubItemList& to)
{
    OFListConstIterator(SOPClassExtendedNegotiationSubItem*) i = from.begin();
    while (i != from.end()) {
        to.push_back(*i);
        ++i;
    }
}

void deleteListMembers(SOPClassExtendedNegotiationSubItemList& lst)
{
    OFListIterator(SOPClassExtendedNegotiationSubItem*) i = lst.begin();
    while (i != lst.end()) {
        delete[] (*i)->serviceClassAppInfo;
        (*i)->serviceClassAppInfo = NULL;
        delete *i;
        ++i;
    }
    lst.clear();
}
