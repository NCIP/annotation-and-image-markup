/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: CountedPointer.c 471747 2006-11-06 14:31:56Z amassari $
 */


// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#if defined(XERCES_TMPLSINC)
#include <xercesc/util/CountedPointer.hpp>
#endif

XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  CountedPointerTo: Constructors and Destructor
// ---------------------------------------------------------------------------
template <class T> CountedPointerTo<T>::
CountedPointerTo(const CountedPointerTo<T>& toCopy) :

    fPtr(toCopy.fPtr)
{
    if (fPtr)
        fPtr->addRef();
}

template <class T> CountedPointerTo<T>::CountedPointerTo(T* p) :

    fPtr(p)
{
    if (fPtr)
        fPtr->addRef();
}

template <class T> CountedPointerTo<T>::~CountedPointerTo()
{
    if (fPtr)
        fPtr->removeRef();
}


// ---------------------------------------------------------------------------
//  CountedPointerTo: Operators
// ---------------------------------------------------------------------------
template <class T> CountedPointerTo<T>&
CountedPointerTo<T>::operator=(const CountedPointerTo<T>& other)
{
    if (this == &other)
        return *this;

    if (other.fPtr)
        other.fPtr->addRef();

    if (fPtr)
        fPtr->removeRef();

    fPtr = other.fPtr;
    return *this;
}

template <class T> CountedPointerTo<T>::operator T*()
{
    return fPtr;
}

template <class T> const T* CountedPointerTo<T>::operator->() const
{
    return fPtr;
}

template <class T> T* CountedPointerTo<T>::operator->()
{
    return fPtr;
}

template <class T> const T& CountedPointerTo<T>::operator*() const
{
    if (!fPtr)
        ThrowXMLwithMemMgr(NullPointerException, XMLExcepts::CPtr_PointerIsZero, 0);
    return *fPtr;
}

template <class T> T& CountedPointerTo<T>::operator*()
{
    if (!fPtr)
        ThrowXMLwithMemMgr(NullPointerException, XMLExcepts::CPtr_PointerIsZero, 0);
    return *fPtr;
}

XERCES_CPP_NAMESPACE_END
