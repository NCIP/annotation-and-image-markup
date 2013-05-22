/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: RefVectorOf.c 676911 2008-07-15 13:27:32Z amassari $
 */


// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#if defined(XERCES_TMPLSINC)
#include <xercesc/util/RefVectorOf.hpp>
#endif

XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  RefVectorOf: Constructors and Destructor
// ---------------------------------------------------------------------------
template <class TElem>
RefVectorOf<TElem>::RefVectorOf(const XMLSize_t maxElems,
                                const bool adoptElems,
                                MemoryManager* const manager)
    : BaseRefVectorOf<TElem>(maxElems, adoptElems, manager)
{
}

template <class TElem> RefVectorOf<TElem>::~RefVectorOf()
{
    if (this->fAdoptedElems)
    {
        for (XMLSize_t index = 0; index < this->fCurCount; index++)
            delete this->fElemList[index];
    }
    this->fMemoryManager->deallocate(this->fElemList);//delete [] this->fElemList;
}


XERCES_CPP_NAMESPACE_END
