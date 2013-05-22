/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: UnicodeRangeFactory.hpp 671870 2008-06-26 12:19:31Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_UNICODERANGEFACTORY_HPP)
#define XERCESC_INCLUDE_GUARD_UNICODERANGEFACTORY_HPP

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/regx/RangeFactory.hpp>
#include <xercesc/util/regx/XMLUniCharacter.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLUTIL_EXPORT UnicodeRangeFactory: public RangeFactory {

public:
    // -----------------------------------------------------------------------
    //  Public Constants
    // -----------------------------------------------------------------------
    // Unicode categories 
    enum {
        CHAR_LETTER      = XMLUniCharacter::FINAL_PUNCTUATION+1,
        CHAR_MARK,
        CHAR_NUMBER,
        CHAR_SEPARATOR,
        CHAR_OTHER,
        CHAR_PUNCTUATION,
        CHAR_SYMBOL,
        UNICATEGSIZE
    };

    // -----------------------------------------------------------------------
    //  Constructors and operators
    // -----------------------------------------------------------------------
    UnicodeRangeFactory();
    ~UnicodeRangeFactory();

    // -----------------------------------------------------------------------
    //  Initialization methods
    // -----------------------------------------------------------------------
    void initializeKeywordMap(RangeTokenMap *rangeTokMap = 0);

    // -----------------------------------------------------------------------
    //  Helper methods
    // -----------------------------------------------------------------------
    static unsigned short getUniCategory(const unsigned short type);

protected:
    // -----------------------------------------------------------------------
    //  Private Helper methods
    // -----------------------------------------------------------------------
    void buildRanges(RangeTokenMap *rangeTokMap = 0);

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    UnicodeRangeFactory(const UnicodeRangeFactory&);
    UnicodeRangeFactory& operator=(const UnicodeRangeFactory&);

};

XERCES_CPP_NAMESPACE_END

#endif

/**
  *    End file UnicodeRangeFactory.hpp
  */
