/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#if defined(XERCES_TMPLSINC)
#include "RefArrayVectorOf.hpp"
#endif

XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  RefArrayVectorOf: Constructor and Destructor
// ---------------------------------------------------------------------------
template <class TElem>
RefArrayVectorOf<TElem>::RefArrayVectorOf( const XMLSize_t maxElems
                                         , const bool adoptElems
                                         , MemoryManager* const manager)
    : BaseRefVectorOf<TElem>(maxElems, adoptElems, manager)
{
}


template <class TElem> RefArrayVectorOf<TElem>::~RefArrayVectorOf()
{
    if (this->fAdoptedElems)
    {
        for (XMLSize_t index = 0; index < this->fCurCount; index++)
            this->fMemoryManager->deallocate(this->fElemList[index]);//delete[] fElemList[index];
    }
    this->fMemoryManager->deallocate(this->fElemList);//delete [] fElemList;
}

template <class TElem> void
RefArrayVectorOf<TElem>::setElementAt(TElem* const toSet, const XMLSize_t setAt)
{
    if (setAt >= this->fCurCount)
        ThrowXMLwithMemMgr(ArrayIndexOutOfBoundsException, XMLExcepts::Vector_BadIndex, this->fMemoryManager);

    if (this->fAdoptedElems)
        this->fMemoryManager->deallocate(this->fElemList[setAt]);

    this->fElemList[setAt] = toSet;
}

template <class TElem> void RefArrayVectorOf<TElem>::removeAllElements()
{
    for (XMLSize_t index = 0; index < this->fCurCount; index++)
    {
        if (this->fAdoptedElems)
            this->fMemoryManager->deallocate(this->fElemList[index]);

        // Keep unused elements zero for sanity's sake
        this->fElemList[index] = 0;
    }
    this->fCurCount = 0;
}

template <class TElem> void RefArrayVectorOf<TElem>::
removeElementAt(const XMLSize_t removeAt)
{
    if (removeAt >= this->fCurCount)
        ThrowXMLwithMemMgr(ArrayIndexOutOfBoundsException, XMLExcepts::Vector_BadIndex, this->fMemoryManager);

    if (this->fAdoptedElems)
        this->fMemoryManager->deallocate(this->fElemList[removeAt]);

    // Optimize if its the last element
    if (removeAt == this->fCurCount-1)
    {
        this->fElemList[removeAt] = 0;
        this->fCurCount--;
        return;
    }

    // Copy down every element above remove point
    for (XMLSize_t index = removeAt; index < this->fCurCount-1; index++)
        this->fElemList[index] = this->fElemList[index+1];

    // Keep unused elements zero for sanity's sake
    this->fElemList[this->fCurCount-1] = 0;

    // And bump down count
    this->fCurCount--;
}

template <class TElem> void RefArrayVectorOf<TElem>::removeLastElement()
{
    if (!this->fCurCount)
        return;
    this->fCurCount--;

    if (this->fAdoptedElems)
        this->fMemoryManager->deallocate(this->fElemList[this->fCurCount]);
}

template <class TElem> void RefArrayVectorOf<TElem>::cleanup()
{
    if (this->fAdoptedElems)
    {
        for (XMLSize_t index = 0; index < this->fCurCount; index++)
            this->fMemoryManager->deallocate(this->fElemList[index]);
    }
    this->fMemoryManager->deallocate(this->fElemList);//delete [] fElemList;
}

XERCES_CPP_NAMESPACE_END
