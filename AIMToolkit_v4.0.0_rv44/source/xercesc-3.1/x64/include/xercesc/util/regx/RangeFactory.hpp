/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: RangeFactory.hpp 678879 2008-07-22 20:05:05Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_RANGEFACTORY_HPP)
#define XERCESC_INCLUDE_GUARD_RANGEFACTORY_HPP

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/XMemory.hpp>

XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  Forward Declaration
// ---------------------------------------------------------------------------
class RangeTokenMap;

class XMLUTIL_EXPORT RangeFactory : public XMemory
{
public:
    // -----------------------------------------------------------------------
    //  Constructors and destructors
    // -----------------------------------------------------------------------
    virtual ~RangeFactory();

    //-----------------------------------------------------------------------
    //  Initialization methods
    // -----------------------------------------------------------------------
    /**
     * To maintain src code compatibility, we added a default parameter.
     * The caller is expected to pass in a valid RangeTokenMap instance.
     */
    virtual void initializeKeywordMap(RangeTokenMap *rangeTokMap = 0) = 0;

    /*
     * Used by children to build commonly used ranges
     * To maintain src code compatibility, we added a default parameter.
     * The caller is expected to pass in a valid RangeTokenMap instance.
     */
    virtual void buildRanges(RangeTokenMap *rangeTokMap = 0) = 0;

protected:
    // -----------------------------------------------------------------------
    //  Constructor and destructors
    // -----------------------------------------------------------------------
    RangeFactory();

    //friend class RangeTokenMap;

    // -----------------------------------------------------------------------
    //  Data
    // -----------------------------------------------------------------------
    bool fRangesCreated;
    bool fKeywordsInitialized;

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    RangeFactory(const RangeFactory&);
    RangeFactory& operator=(const RangeFactory&);
};

XERCES_CPP_NAMESPACE_END

#endif

/**
  *    End file RangeFactory.hpp
  */
