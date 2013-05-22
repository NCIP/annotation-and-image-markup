/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: ValueArrayOf.hpp 932887 2010-04-11 13:04:59Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_VALUEARRAY_HPP)
#define XERCESC_INCLUDE_GUARD_VALUEARRAY_HPP

#include <xercesc/util/XMLEnumerator.hpp>
#include <xercesc/util/ArrayIndexOutOfBoundsException.hpp>
#include <xercesc/util/IllegalArgumentException.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/framework/MemoryManager.hpp>

XERCES_CPP_NAMESPACE_BEGIN

template <class TElem> class ValueArrayOf : public XMemory
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    ValueArrayOf
    (
           const XMLSize_t      size
         , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );
	ValueArrayOf
    (
          const TElem*         values
        , const XMLSize_t      size
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );
	ValueArrayOf(const ValueArrayOf<TElem>& source);
	~ValueArrayOf();


    // -----------------------------------------------------------------------
    //  Public operators
    // -----------------------------------------------------------------------
	TElem& operator[](const XMLSize_t index);
	const TElem& operator[](const XMLSize_t index) const;
	ValueArrayOf<TElem>& operator=(const ValueArrayOf<TElem>& toAssign);
	bool operator==(const ValueArrayOf<TElem>& toCompare) const;
	bool operator!=(const ValueArrayOf<TElem>& toCompare) const;


    // -----------------------------------------------------------------------
    //  Copy operations
    // -----------------------------------------------------------------------
    XMLSize_t copyFrom(const ValueArrayOf<TElem>& srcArray);


    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
	XMLSize_t length() const;
	TElem* rawData() const;


    // -----------------------------------------------------------------------
    //  Miscellaneous methods
    // -----------------------------------------------------------------------
    void resize(const XMLSize_t newSize);


private :
    // -----------------------------------------------------------------------
    //  Data members
    // -----------------------------------------------------------------------
	XMLSize_t       fSize;
	TElem*          fArray;
    MemoryManager*  fMemoryManager;
};


//
//  An enumerator for a value array. It derives from the basic enumerator
//  class, so that value vectors can be generically enumerated.
//
template <class TElem> class ValueArrayEnumerator : public XMLEnumerator<TElem>, public XMemory
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    ValueArrayEnumerator
    (
                ValueArrayOf<TElem>* const toEnum
        , const bool                       adopt = false
    );
    virtual ~ValueArrayEnumerator();


    // -----------------------------------------------------------------------
    //  Enum interface
    // -----------------------------------------------------------------------
    bool hasMoreElements() const;
    TElem& nextElement();
    void Reset();


private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------    
    ValueArrayEnumerator(const ValueArrayEnumerator<TElem>&);
    ValueArrayEnumerator<TElem>& operator=(const ValueArrayEnumerator<TElem>&);

    // -----------------------------------------------------------------------
    //  Data Members
    //
    //  fAdopted
    //      Indicates whether we have adopted the passed vector. If so then
    //      we delete the vector when we are destroyed.
    //
    //  fCurIndex
    //      This is the current index into the vector.
    //
    //  fToEnum
    //      The value array being enumerated.
    // -----------------------------------------------------------------------
    bool                    fAdopted;
    XMLSize_t               fCurIndex;
    ValueArrayOf<TElem>*    fToEnum;
};

XERCES_CPP_NAMESPACE_END

#if !defined(XERCES_TMPLSINC)
#include <xercesc/util/ValueArrayOf.c>
#endif

#endif
