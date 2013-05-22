/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XMLUniCharacter.hpp 671870 2008-06-26 12:19:31Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XMLUNICHARACTER_HPP)
#define XERCESC_INCLUDE_GUARD_XMLUNICHARACTER_HPP

#include <xercesc/util/XercesDefs.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/**
  * Class for representing unicode characters
  */
class XMLUTIL_EXPORT XMLUniCharacter
{
public:
    // -----------------------------------------------------------------------
    //  Public Constants
    // -----------------------------------------------------------------------
    // Unicode char types
    enum {
        UNASSIGNED              = 0,
        UPPERCASE_LETTER        = 1,
        LOWERCASE_LETTER        = 2,
        TITLECASE_LETTER        = 3,
        MODIFIER_LETTER         = 4,
        OTHER_LETTER            = 5,
        NON_SPACING_MARK        = 6,
        ENCLOSING_MARK          = 7,
        COMBINING_SPACING_MARK  = 8,
        DECIMAL_DIGIT_NUMBER    = 9,
        LETTER_NUMBER           = 10,
        OTHER_NUMBER            = 11,
        SPACE_SEPARATOR         = 12,
        LINE_SEPARATOR          = 13,
        PARAGRAPH_SEPARATOR     = 14,
        CONTROL                 = 15,
        FORMAT                  = 16,
        PRIVATE_USE             = 17,
        SURROGATE               = 18,
        DASH_PUNCTUATION        = 19,
        START_PUNCTUATION       = 20,
        END_PUNCTUATION         = 21,
        CONNECTOR_PUNCTUATION   = 22,
        OTHER_PUNCTUATION       = 23,
        MATH_SYMBOL             = 24,
        CURRENCY_SYMBOL         = 25,
        MODIFIER_SYMBOL         = 26,
        OTHER_SYMBOL            = 27,
        INITIAL_PUNCTUATION     = 28,
        FINAL_PUNCTUATION       = 29
    };

    /** destructor */
    ~XMLUniCharacter() {}

    /* Static methods for getting unicode character type */
    /** @name Getter functions */
    //@{

    /** Gets the unicode type of a given character
      *
      * @param ch The character we want to get its unicode type
      */
    static unsigned short getType(const XMLCh ch);
    //@}

private :

    /** @name Constructors and Destructor */
    //@{
    /** Unimplemented default constructor */
    XMLUniCharacter();
    //@}
};

XERCES_CPP_NAMESPACE_END

#endif

/**
  * End of file XMLUniCharacter.hpp
  */
