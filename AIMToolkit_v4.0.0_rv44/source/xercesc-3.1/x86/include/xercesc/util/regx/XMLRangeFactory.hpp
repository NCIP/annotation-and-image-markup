/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XMLRangeFactory.hpp 678879 2008-07-22 20:05:05Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XMLRANGEFACTORY_HPP)
#define XERCESC_INCLUDE_GUARD_XMLRANGEFACTORY_HPP

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/regx/RangeFactory.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLUTIL_EXPORT XMLRangeFactory: public RangeFactory {

public:
    // -----------------------------------------------------------------------
    //  Constructors and operators
    // -----------------------------------------------------------------------
    XMLRangeFactory();
    ~XMLRangeFactory();

    // -----------------------------------------------------------------------
    //  Initialization methods
    // -----------------------------------------------------------------------
    void initializeKeywordMap(RangeTokenMap *rangeTokMap = 0);

protected:
    // -----------------------------------------------------------------------
    //  Protected Helper methods
    // -----------------------------------------------------------------------
    void buildRanges(RangeTokenMap *rangeTokMap = 0);

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XMLRangeFactory(const XMLRangeFactory&);
    XMLRangeFactory& operator=(const XMLRangeFactory&);
};

XERCES_CPP_NAMESPACE_END

#endif

/**
  *    End file XMLRangeFactory.hpp
  */
