/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: CharToken.hpp 678879 2008-07-22 20:05:05Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_CHARTOKEN_HPP)
#define XERCESC_INCLUDE_GUARD_CHARTOKEN_HPP

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/regx/Token.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLUTIL_EXPORT CharToken : public Token {
public:
    // -----------------------------------------------------------------------
    //  Public Constructors and Destructor
    // -----------------------------------------------------------------------
    CharToken(const tokType tkType, const XMLInt32 ch
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);
    ~CharToken();

    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    XMLInt32 getChar() const;

    // -----------------------------------------------------------------------
    //  Match methods
    // -----------------------------------------------------------------------
    bool match(const XMLInt32 ch);

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    CharToken(const CharToken&);
    CharToken& operator=(const CharToken&);

    // -----------------------------------------------------------------------
    //  Private data members
    // -----------------------------------------------------------------------
    XMLInt32 fCharData;
};


// ---------------------------------------------------------------------------
//  CharToken: getter methods
// ---------------------------------------------------------------------------
inline XMLInt32 CharToken::getChar() const {

    return fCharData;
}


// ---------------------------------------------------------------------------
//  CharToken: getter methods
// ---------------------------------------------------------------------------
inline bool CharToken::match(const XMLInt32 ch){

    return ch == fCharData;
}

XERCES_CPP_NAMESPACE_END

#endif

/**
  * End of file CharToken.hpp
  */
