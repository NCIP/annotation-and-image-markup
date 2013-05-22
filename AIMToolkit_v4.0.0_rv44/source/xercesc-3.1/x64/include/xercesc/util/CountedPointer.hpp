/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: CountedPointer.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_COUNTEDPOINTERTO_HPP)
#define XERCESC_INCLUDE_GUARD_COUNTEDPOINTERTO_HPP

#include <xercesc/util/NullPointerException.hpp>

XERCES_CPP_NAMESPACE_BEGIN

template <class T> class CountedPointerTo : public XMemory
{
public:
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    CountedPointerTo(const CountedPointerTo<T>& toCopy);
    CountedPointerTo(T* p = 0);
    ~CountedPointerTo();


    // -----------------------------------------------------------------------
    //  Operators
    // -----------------------------------------------------------------------
    CountedPointerTo<T>& operator=(const CountedPointerTo<T>& other);
    operator T*();
    const T* operator->() const;
    T* operator->();
    const T& operator*() const;
    T& operator*();


private:
    // -----------------------------------------------------------------------
    //  Data members
    //
    //  fPtr
    //      The pointer that we are counting. The T type must implement the
    //      addRef() and removeRef() APIs but it doesn't have to derive from
    //      any particular type.
    // -----------------------------------------------------------------------
    T*  fPtr;
};

XERCES_CPP_NAMESPACE_END

#if !defined(XERCES_TMPLSINC)
#include <xercesc/util/CountedPointer.c>
#endif

#endif
