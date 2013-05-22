/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: RefArrayVectorOf.hpp 676911 2008-07-15 13:27:32Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_REFARRAYVECTOROF_HPP)
#define XERCESC_INCLUDE_GUARD_REFARRAYVECTOROF_HPP

#include <xercesc/util/BaseRefVectorOf.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/** 
 * Class with implementation for vectors of pointers to arrays  - implements from 
 * the Abstract class Vector
 */ 
template <class TElem> class RefArrayVectorOf : public BaseRefVectorOf<TElem> 
{
public :
    // -----------------------------------------------------------------------
    //  Constructor
    // -----------------------------------------------------------------------
    RefArrayVectorOf( const XMLSize_t      maxElems
                    , const bool           adoptElems = true
                    , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);

    // -----------------------------------------------------------------------
    //  Destructor
    // -----------------------------------------------------------------------
    ~RefArrayVectorOf();

    // -----------------------------------------------------------------------
    //  Element management
    // -----------------------------------------------------------------------
    void setElementAt(TElem* const toSet, const XMLSize_t setAt);
    void removeAllElements();
    void removeElementAt(const XMLSize_t removeAt);
    void removeLastElement();
    void cleanup();
private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    RefArrayVectorOf(const RefArrayVectorOf<TElem>&);
    RefArrayVectorOf<TElem>& operator=(const RefArrayVectorOf<TElem>&);
};

XERCES_CPP_NAMESPACE_END

#if !defined(XERCES_TMPLSINC)
#include <xercesc/util/RefArrayVectorOf.c>
#endif

#endif
