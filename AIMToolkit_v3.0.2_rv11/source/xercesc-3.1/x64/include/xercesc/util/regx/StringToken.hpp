/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: StringToken.hpp 678879 2008-07-22 20:05:05Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_STRINGTOKEN_HPP)
#define XERCESC_INCLUDE_GUARD_STRINGTOKEN_HPP

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/regx/Token.hpp>
#include <xercesc/util/XMLString.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLUTIL_EXPORT StringToken : public Token {
public:
    // -----------------------------------------------------------------------
    //  Public Constructors and Destructor
    // -----------------------------------------------------------------------
    StringToken(const tokType tkType,
                const XMLCh* const literal,
                const int refNo,
                MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);
    ~StringToken();

    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    int getReferenceNo() const;
    const XMLCh* getString() const;

    // -----------------------------------------------------------------------
    //  Setter methods
    // -----------------------------------------------------------------------
    void setString(const XMLCh* const literal);

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    StringToken(const StringToken&);
    StringToken& operator=(const StringToken&);

    // -----------------------------------------------------------------------
    //  Private data members
    // -----------------------------------------------------------------------
    int    fRefNo;
    XMLCh* fString;
    MemoryManager* fMemoryManager;
};


// ---------------------------------------------------------------------------
//  StringToken: getter methods
// ---------------------------------------------------------------------------
inline int StringToken::getReferenceNo() const {

    return fRefNo;
}

inline const XMLCh* StringToken::getString() const {

    return fString;
}

// ---------------------------------------------------------------------------
//  StringToken: Setter methods
// ---------------------------------------------------------------------------
inline void StringToken::setString(const XMLCh* const literal) {

    fMemoryManager->deallocate(fString);//delete [] fString;
    fString = 0;
    fString = XMLString::replicate(literal, fMemoryManager);
}

XERCES_CPP_NAMESPACE_END

#endif

/**
  * End of file StringToken.hpp
  */
