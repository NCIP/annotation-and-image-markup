/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: FlagJanitor.c 471747 2006-11-06 14:31:56Z amassari $
 */


// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#if defined(XERCES_TMPLSINC)
#include <xercesc/util/FlagJanitor.hpp>
#endif

XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  Constructors and Destructor
// ---------------------------------------------------------------------------
template <class T> FlagJanitor<T>::FlagJanitor(T* const valPtr, const T newVal)
:   fValPtr(valPtr)
{
    // Store the pointer, save the org value, and store the new value    
    if (fValPtr)
    {
        fOldVal = *fValPtr;
        *fValPtr = newVal;
    }
}

template <class T> FlagJanitor<T>::~FlagJanitor()
{
    // Restore the old value
    if (fValPtr)
        *fValPtr = fOldVal;
}


// ---------------------------------------------------------------------------
//  Value management methods
// ---------------------------------------------------------------------------
template <class T> void FlagJanitor<T>::release()
{
    fValPtr = 0;
}

XERCES_CPP_NAMESPACE_END
