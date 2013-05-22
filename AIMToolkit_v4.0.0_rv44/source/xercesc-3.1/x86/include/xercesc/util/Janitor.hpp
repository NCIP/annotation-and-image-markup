/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: Janitor.hpp 669844 2008-06-20 10:11:44Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_JANITOR_HPP)
#define XERCESC_INCLUDE_GUARD_JANITOR_HPP

#include <xercesc/util/XMemory.hpp>
#include <xercesc/framework/MemoryManager.hpp>

XERCES_CPP_NAMESPACE_BEGIN

template <class T> class Janitor : public XMemory
{
public  :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    Janitor(T* const toDelete);
    ~Janitor();

    // -----------------------------------------------------------------------
    //  Public, non-virtual methods
    // -----------------------------------------------------------------------
    void orphan();

    //  small amount of auto_ptr compatibility
    T& operator*() const;
    T* operator->() const;
    T* get() const;
    T* release();
    void reset(T* p = 0);
    bool isDataNull();

private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    Janitor();
    Janitor(const Janitor<T>&);
    Janitor<T>& operator=(const Janitor<T>&);

    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fData
    //      This is the pointer to the object or structure that must be
    //      destroyed when this object is destroyed.
    // -----------------------------------------------------------------------
    T*  fData;
};



template <class T> class ArrayJanitor : public XMemory
{
public  :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    ArrayJanitor(T* const toDelete);
    ArrayJanitor(T* const toDelete, MemoryManager* const manager);
    ~ArrayJanitor();


    // -----------------------------------------------------------------------
    //  Public, non-virtual methods
    // -----------------------------------------------------------------------
    void orphan();

	//	small amount of auto_ptr compatibility
	T&	operator[](int index) const;
	T*	get() const;
	T*	release();
	void reset(T* p = 0);
	void reset(T* p, MemoryManager* const manager);

private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
	ArrayJanitor();
    ArrayJanitor(const ArrayJanitor<T>& copy);
    ArrayJanitor<T>& operator=(const ArrayJanitor<T>& copy);

    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fData
    //      This is the pointer to the object or structure that must be
    //      destroyed when this object is destroyed.
    // -----------------------------------------------------------------------
    T*  fData;
    MemoryManager* fMemoryManager;
};



template <class T> class JanitorMemFunCall
{
public  :

    typedef void (T::*MFPT) ();

    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    JanitorMemFunCall(
        T*      object,
        MFPT    toCall);

    ~JanitorMemFunCall();

    //  small amount of auto_ptr compatibility
    T& operator*() const;
    T* operator->() const;
    T* get() const;
    T* release();
    void reset(T* p = 0);

private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    JanitorMemFunCall();
    JanitorMemFunCall(const JanitorMemFunCall<T>&);
    JanitorMemFunCall<T>& operator=(const JanitorMemFunCall<T>&);

    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fObject
    //      This is the pointer to the object for which we will call the
    //      member function when this object is destroyed.
    // -----------------------------------------------------------------------
    T*      fObject;
    MFPT    fToCall;
};




XERCES_CPP_NAMESPACE_END

#if !defined(XERCES_TMPLSINC)
#include <xercesc/util/Janitor.c>
#endif

#endif
