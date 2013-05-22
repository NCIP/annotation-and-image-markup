/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: FlagJanitor.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_FLAGJANITOR_HPP)
#define XERCESC_INCLUDE_GUARD_FLAGJANITOR_HPP

#include <xercesc/util/XercesDefs.hpp>

XERCES_CPP_NAMESPACE_BEGIN

template <class T> class FlagJanitor
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    FlagJanitor(T* const valPtr, const T newVal);
    ~FlagJanitor();


    // -----------------------------------------------------------------------
    //  Value management methods
    // -----------------------------------------------------------------------
    void release();


private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    FlagJanitor();
    FlagJanitor(const FlagJanitor<T>&);
    FlagJanitor<T>& operator=(const FlagJanitor<T>&);


    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fOldVal
    //      The old value that was in the flag when we were constructed.
    //
    //  fValPtr
    //      A pointer to the flag that we are to restore the value of
    // -----------------------------------------------------------------------
    T   fOldVal;
    T*  fValPtr;
};

XERCES_CPP_NAMESPACE_END

#if !defined(XERCES_TMPLSINC)
#include <xercesc/util/FlagJanitor.c>
#endif

#endif
