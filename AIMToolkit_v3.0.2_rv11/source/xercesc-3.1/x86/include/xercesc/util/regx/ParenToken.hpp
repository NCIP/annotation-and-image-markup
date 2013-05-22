/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: ParenToken.hpp 678879 2008-07-22 20:05:05Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_PARENTOKEN_HPP)
#define XERCESC_INCLUDE_GUARD_PARENTOKEN_HPP

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/regx/Token.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLUTIL_EXPORT ParenToken : public Token {
public:
    // -----------------------------------------------------------------------
    //  Public Constructors and Destructor
    // -----------------------------------------------------------------------
    ParenToken(const tokType tkType, Token* const tok,
               const int noParen, MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);
    ~ParenToken();

    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    XMLSize_t size() const;
    int getNoParen() const;
    Token* getChild(const XMLSize_t index) const;

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    ParenToken(const ParenToken&);
    ParenToken& operator=(const ParenToken&);

    // -----------------------------------------------------------------------
    //  Private data members
    // -----------------------------------------------------------------------
    int    fNoParen;
    Token* fChild;
};


// ---------------------------------------------------------------------------
//  ParenToken: getter methods
// ---------------------------------------------------------------------------
inline XMLSize_t ParenToken::size() const {

    return 1;
}

inline int ParenToken::getNoParen() const {

    return fNoParen;
}

inline Token* ParenToken::getChild(const XMLSize_t) const {

    return fChild;
}

XERCES_CPP_NAMESPACE_END

#endif

/**
  * End of file ParenToken.hpp
  */
