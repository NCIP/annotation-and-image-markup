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


/*
** CVS/RCS Log:
** $Log: extneg.cc,v $
** Revision 1.7  2010-10-14 13:14:29  joergr
** Updated copyright header. Added reference to COPYRIGHT file.
**
** Revision 1.6  2010-07-06 14:50:17  onken
** Fixed memory leaked in extended negotiaton code.
**
** Revision 1.5  2005-12-08 15:44:54  meichel
** Changed include path schema for all DCMTK header files
**
** Revision 1.4  2004/02/04 15:33:48  joergr
** Removed acknowledgements with e-mail addresses from CVS log.
**
** Revision 1.3  2003/06/12 18:25:20  joergr
** Modified code to use const_iterators where appropriate (required for STL).
**
** Revision 1.2  2003/06/02 16:44:11  meichel
** Renamed local variables to avoid name clashes with STL
**
** Revision 1.1  1999/04/19 08:40:03  meichel
** Added experimental support for extended SOP class negotiation.
**
**
*/
