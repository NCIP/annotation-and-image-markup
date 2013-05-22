/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: UnionToken.hpp 678879 2008-07-22 20:05:05Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_UNIONTOKEN_HPP)
#define XERCESC_INCLUDE_GUARD_UNIONTOKEN_HPP

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/regx/Token.hpp>
#include <xercesc/util/RefVectorOf.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLUTIL_EXPORT UnionToken : public Token {
public:
    // -----------------------------------------------------------------------
    //  Public Constructors and Destructor
    // -----------------------------------------------------------------------
    UnionToken(const tokType tkType
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);
    ~UnionToken();

    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    XMLSize_t size() const;
    Token* getChild(const XMLSize_t index) const;

    // -----------------------------------------------------------------------
    //  Children manipulation methods
    // -----------------------------------------------------------------------
    void addChild(Token* const child, TokenFactory* const tokFactory);

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    UnionToken(const UnionToken&);
    UnionToken& operator=(const UnionToken&);

    // -----------------------------------------------------------------------
    //  Private Constants
    // -----------------------------------------------------------------------
    static const unsigned short INITIALSIZE;

    // -----------------------------------------------------------------------
    //  Private data members
    // -----------------------------------------------------------------------
    RefVectorOf<Token>* fChildren;
};


// ---------------------------------------------------------------------------
//  UnionToken: getter methods
// ---------------------------------------------------------------------------
inline XMLSize_t UnionToken::size() const {

    return fChildren == 0 ? 0 : fChildren->size();
}

inline Token* UnionToken::getChild(const XMLSize_t index) const {

    return fChildren->elementAt(index);
}

XERCES_CPP_NAMESPACE_END

#endif

/**
  * End of file UnionToken.hpp
  */
