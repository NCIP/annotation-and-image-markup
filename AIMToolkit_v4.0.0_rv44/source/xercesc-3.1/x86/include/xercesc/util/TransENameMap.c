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
#include <xercesc/util/TransENameMap.hpp>
#endif

XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  ENameMapFor: Constructors and Destructor
// ---------------------------------------------------------------------------
template <class TType>
ENameMapFor<TType>::ENameMapFor(const XMLCh* const encodingName) :

    ENameMap(encodingName)
{
}

template <class TType> ENameMapFor<TType>::~ENameMapFor()
{
}


// ---------------------------------------------------------------------------
//  ENameMapFor: Implementation of virtual factory method
// ---------------------------------------------------------------------------
template <class TType> XMLTranscoder*
ENameMapFor<TType>::makeNew(const XMLSize_t      blockSize,
                            MemoryManager* const manager) const
{
    return new (manager) TType(getKey(), blockSize, manager);
}




// ---------------------------------------------------------------------------
//  ENameMapFor: Constructors and Destructor
// ---------------------------------------------------------------------------
template <class TType> EEndianNameMapFor<TType>::EEndianNameMapFor(const XMLCh* const encodingName, const bool swapped) :

    ENameMap(encodingName)
    , fSwapped(swapped)
{
}

template <class TType> EEndianNameMapFor<TType>::~EEndianNameMapFor()
{
}


// ---------------------------------------------------------------------------
//  ENameMapFor: Implementation of virtual factory method
// ---------------------------------------------------------------------------
template <class TType> XMLTranscoder*
EEndianNameMapFor<TType>::makeNew(const XMLSize_t      blockSize,
                                  MemoryManager* const manager) const
{
    return new (manager) TType(getKey(), blockSize, fSwapped, manager);
}

XERCES_CPP_NAMESPACE_END
