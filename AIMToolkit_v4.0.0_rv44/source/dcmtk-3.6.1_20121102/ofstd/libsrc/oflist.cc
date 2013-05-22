/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#if defined(HAVE_STL) || defined (HAVE_STL_LIST)
// We do not need to make this library
void OF__DUMMY()    // to make the linker happy!
{
}
#else

#include "dcmtk/ofstd/oflist.h"

OFListBase::OFListBase()
: afterLast(NULL)
, listSize(0)
{
    afterLast = new OFListLinkBase();
    afterLast->prev = afterLast->next = afterLast;
    afterLast->dummy = OFTrue;
}


OFListBase::~OFListBase()
{
    base_clear();
    if (afterLast)
        delete afterLast;
}

OFListLinkBase * OFListBase::base_insert(OFListLinkBase * pos,
                                         OFListLinkBase * newElem)
{
    assert(pos && newElem);
    if (pos && newElem)
    {
        newElem->next = pos;
        newElem->prev = pos->prev;
        pos->prev->next = newElem;
        pos->prev = newElem;
        listSize++;
        return newElem;
    }
    return NULL;
}


OFListLinkBase * OFListBase::base_erase(OFListLinkBase * pos)
{
    assert(pos && pos != afterLast);
    OFListLinkBase * tmp = pos->next;;
    pos->next->prev=pos->prev;
    pos->prev->next=pos->next;
    delete pos;
    listSize--;
    return tmp;
}

void OFListBase::base_splice(OFListLinkBase * pos,
                             OFListLinkBase * begin,
                             OFListLinkBase * end)
{
    assert(pos && begin && end);
    if (begin != end)
    {
        OFListLinkBase * beginPrev = begin->prev;
        OFListLinkBase * posPrev = pos->prev;
        pos->prev->next = begin;
        pos->prev = end->prev;
        begin->prev->next = end;
        begin->prev = posPrev;
        end->prev->next = pos;
        end->prev = beginPrev;
        base_recalcListSize();
    }
}

void OFListBase::base_clear()
{
    while(listSize)
        base_erase(afterLast->next);
}

void OFListBase::base_recalcListSize()
{
    OFListLinkBase * elem;
    for (listSize = 0, elem = afterLast->next;
         elem != afterLast;
         elem = elem->next, ++listSize)
        ;
}


#endif
