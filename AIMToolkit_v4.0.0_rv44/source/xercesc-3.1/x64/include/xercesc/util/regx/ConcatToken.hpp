/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: ConcatToken.hpp 678879 2008-07-22 20:05:05Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_CONCATTOKEN_HPP)
#define XERCESC_INCLUDE_GUARD_CONCATTOKEN_HPP

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/regx/Token.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLUTIL_EXPORT ConcatToken : public Token {
public:
    // -----------------------------------------------------------------------
    //  Public Constructors and Destructor
    // -----------------------------------------------------------------------
    ConcatToken(Token* const tok1, Token* const tok2
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);
    ~ConcatToken();

    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    Token* getChild(const XMLSize_t index) const;
    XMLSize_t size() const;

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    ConcatToken(const ConcatToken&);
    ConcatToken& operator=(const ConcatToken&);

    // -----------------------------------------------------------------------
    //  Private data members
    // -----------------------------------------------------------------------
    Token* fChild1;
    Token* fChild2;
};


// ---------------------------------------------------------------------------
//  StringToken: getter methods
// ---------------------------------------------------------------------------
inline XMLSize_t ConcatToken::size() const {

    return 2;
}

inline Token* ConcatToken::getChild(const XMLSize_t index) const {

    return index == 0 ? fChild1 : fChild2;
}

XERCES_CPP_NAMESPACE_END

#endif

/**
  * End of file ConcatToken.hpp
  */
