/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: ValueStackOf.c 676911 2008-07-15 13:27:32Z amassari $
 */


// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#if defined(XERCES_TMPLSINC)
#include <xercesc/util/ValueStackOf.hpp>
#endif

XERCES_CPP_NAMESPACE_BEGIN


// ---------------------------------------------------------------------------
//  ValueStackOf: Constructors and Destructor
// ---------------------------------------------------------------------------
template <class TElem>
ValueStackOf<TElem>::ValueStackOf(const XMLSize_t fInitCapacity,
                                  MemoryManager* const manager,
                                  const bool toCallDestructor) :

    fVector(fInitCapacity, manager, toCallDestructor)
{
}

template <class TElem> ValueStackOf<TElem>::~ValueStackOf()
{
}


// ---------------------------------------------------------------------------
//  ValueStackOf: Element management methods
// ---------------------------------------------------------------------------
template <class TElem> void ValueStackOf<TElem>::push(const TElem& toPush)
{
    fVector.addElement(toPush);
}

template <class TElem> const TElem& ValueStackOf<TElem>::peek() const
{
    const XMLSize_t curSize = fVector.size();
    if (curSize == 0)
        ThrowXMLwithMemMgr(EmptyStackException, XMLExcepts::Stack_EmptyStack, fVector.getMemoryManager());

    return fVector.elementAt(curSize-1);
}

template <class TElem> TElem ValueStackOf<TElem>::pop()
{
    const XMLSize_t curSize = fVector.size();
    if (curSize == 0)
        ThrowXMLwithMemMgr(EmptyStackException, XMLExcepts::Stack_EmptyStack, fVector.getMemoryManager());

    TElem retVal = fVector.elementAt(curSize-1);
    fVector.removeElementAt(curSize-1);
    return retVal;
}

template <class TElem> void ValueStackOf<TElem>::removeAllElements()
{
    fVector.removeAllElements();
}


// ---------------------------------------------------------------------------
//  ValueStackOf: Getter methods
// ---------------------------------------------------------------------------
template <class TElem> bool ValueStackOf<TElem>::empty()
{
    return (fVector.size() == 0);
}

template <class TElem> XMLSize_t ValueStackOf<TElem>::curCapacity()
{
    return fVector.curCapacity();
}

template <class TElem> XMLSize_t ValueStackOf<TElem>::size()
{
    return fVector.size();
}




// ---------------------------------------------------------------------------
//  ValueStackEnumerator: Constructors and Destructor
// ---------------------------------------------------------------------------
template <class TElem> ValueStackEnumerator<TElem>::
ValueStackEnumerator(       ValueStackOf<TElem>* const  toEnum
                    , const bool                        adopt) :

    fAdopted(adopt)
    , fCurIndex(0)
    , fToEnum(toEnum)
    , fVector(&toEnum->fVector)
{
}

template <class TElem> ValueStackEnumerator<TElem>::~ValueStackEnumerator()
{
    if (fAdopted)
        delete fToEnum;
}


// ---------------------------------------------------------------------------
//  ValueStackEnumerator: Enum interface
// ---------------------------------------------------------------------------
template <class TElem> bool ValueStackEnumerator<TElem>::hasMoreElements() const
{
    if (fCurIndex >= fVector->size())
        return false;
    return true;
}

template <class TElem> TElem& ValueStackEnumerator<TElem>::nextElement()
{
    return fVector->elementAt(fCurIndex++);
}

template <class TElem> void ValueStackEnumerator<TElem>::Reset()
{
    fCurIndex = 0;
}

XERCES_CPP_NAMESPACE_END
