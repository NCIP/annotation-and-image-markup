/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: RefVectorOf.hpp 676911 2008-07-15 13:27:32Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_REFVECTOROF_HPP)
#define XERCESC_INCLUDE_GUARD_REFVECTOROF_HPP

#include <xercesc/util/BaseRefVectorOf.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/** 
 * Class with implementation for vectors of References - implements from the 
 * Abstract class Vector
 */ 
template <class TElem> class RefVectorOf : public BaseRefVectorOf<TElem>
{
public :
    // -----------------------------------------------------------------------
    //  Constructor
    // -----------------------------------------------------------------------
    RefVectorOf(const XMLSize_t maxElems,
                const bool adoptElems = true,
                MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);

    // -----------------------------------------------------------------------
    //  Destructor
    // -----------------------------------------------------------------------
    ~RefVectorOf();

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    RefVectorOf(const RefVectorOf<TElem>&);
    RefVectorOf<TElem>& operator=(const RefVectorOf<TElem>&);
};

XERCES_CPP_NAMESPACE_END

#if !defined(XERCES_TMPLSINC)
#include <xercesc/util/RefVectorOf.c>
#endif

#endif
