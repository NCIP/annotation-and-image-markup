/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: Janitor.c 669844 2008-06-20 10:11:44Z borisk $
 */


// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#if defined(XERCES_TMPLSINC)
#include <xercesc/util/Janitor.hpp>
#endif

XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  Janitor: Constructors and Destructor
// ---------------------------------------------------------------------------
template <class T> Janitor<T>::Janitor(T* const toDelete) :
    fData(toDelete)
{
}


template <class T> Janitor<T>::~Janitor()
{
    reset();
}


// ---------------------------------------------------------------------------
//  Janitor: Public, non-virtual methods
// ---------------------------------------------------------------------------
template <class T> void
Janitor<T>::orphan()
{
   release();
}


template <class T> T&
Janitor<T>::operator*() const
{
	return *fData;
}


template <class T> T*
Janitor<T>::operator->() const
{
	return fData;
}


template <class T> T*
Janitor<T>::get() const
{
	return fData;
}


template <class T> T*
Janitor<T>::release()
{
	T* p = fData;
	fData = 0;
	return p;
}


template <class T> void Janitor<T>::reset(T* p)
{
    if (fData)
        delete fData;

    fData = p;
}

template <class T> bool Janitor<T>::isDataNull()
{
    return (fData == 0);
}


// -----------------------------------------------------------------------
//  ArrayJanitor: Constructors and Destructor
// -----------------------------------------------------------------------
template <class T> ArrayJanitor<T>::ArrayJanitor(T* const toDelete) :
    fData(toDelete)
    , fMemoryManager(0)
{
}

template <class T>
ArrayJanitor<T>::ArrayJanitor(T* const toDelete,
                              MemoryManager* const manager) :
    fData(toDelete)
    , fMemoryManager(manager)
{
}


template <class T> ArrayJanitor<T>::~ArrayJanitor()
{
	reset();
}


// -----------------------------------------------------------------------
//  ArrayJanitor: Public, non-virtual methods
// -----------------------------------------------------------------------
template <class T> void
ArrayJanitor<T>::orphan()
{
   release();
}


//	Look, Ma! No hands! Don't call this with null data!
template <class T> T&
ArrayJanitor<T>::operator[](int index) const
{
	//	TODO: Add appropriate exception
	return fData[index];
}


template <class T> T*
ArrayJanitor<T>::get() const
{
	return fData;
}


template <class T> T*
ArrayJanitor<T>::release()
{
	T* p = fData;
	fData = 0;
	return p;
}


template <class T> void
ArrayJanitor<T>::reset(T* p)
{
	if (fData) {

		if (fMemoryManager)
            fMemoryManager->deallocate((void*)fData);
        else
            delete [] fData;
    }

	fData = p;
    fMemoryManager = 0;
}

template <class T> void
ArrayJanitor<T>::reset(T* p, MemoryManager* const manager)
{
	if (fData) {

		if (fMemoryManager)
            fMemoryManager->deallocate((void*)fData);
        else
            delete [] fData;
    }

	fData = p;
    fMemoryManager = manager;
}

//
// JanitorMemFunCall
//

template <class T>
JanitorMemFunCall<T>::JanitorMemFunCall(
            T*      object,
            MFPT    toCall) :
    fObject(object),
    fToCall(toCall)
{
}

template <class T>
JanitorMemFunCall<T>::~JanitorMemFunCall()
{
  reset ();
}

template <class T>
T& JanitorMemFunCall<T>::operator*() const
{
  return *fObject;
}


template <class T>
T* JanitorMemFunCall<T>::operator->() const
{
  return fObject;
}


template <class T>
T* JanitorMemFunCall<T>::get() const
{
  return fObject;
}


template <class T>
T* JanitorMemFunCall<T>::release()
{
  T* p = fObject;
  fObject = 0;
  return p;
}

template <class T>
void JanitorMemFunCall<T>::reset(T* p)
{
  if (fObject != 0 && fToCall != 0)
    (fObject->*fToCall)();

  fObject = p;
}


XERCES_CPP_NAMESPACE_END
