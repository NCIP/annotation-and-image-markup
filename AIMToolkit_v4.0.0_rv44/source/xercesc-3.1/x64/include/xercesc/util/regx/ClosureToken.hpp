/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: ClosureToken.hpp 678879 2008-07-22 20:05:05Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_CLOSURETOKEN_HPP)
#define XERCESC_INCLUDE_GUARD_CLOSURETOKEN_HPP

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/regx/Token.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLUTIL_EXPORT ClosureToken : public Token {
public:
    // -----------------------------------------------------------------------
    //  Public Constructors and Destructor
    // -----------------------------------------------------------------------
    ClosureToken(const tokType tkType, Token* const tok
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);
    ~ClosureToken();

    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    XMLSize_t size() const;
    int getMin() const;
    int getMax() const;
    Token* getChild(const XMLSize_t index) const;

    // -----------------------------------------------------------------------
    //  Setter methods
    // -----------------------------------------------------------------------
    void setMin(const int minVal);
    void setMax(const int maxVal);

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    ClosureToken(const ClosureToken&);
    ClosureToken& operator=(const ClosureToken&);

    // -----------------------------------------------------------------------
    //  Private data members
    // -----------------------------------------------------------------------
    int    fMin;
    int    fMax;
    Token* fChild;
};


// ---------------------------------------------------------------------------
//  ClosureToken: getter methods
// ---------------------------------------------------------------------------
inline XMLSize_t ClosureToken::size() const {

    return 1;
}


inline int ClosureToken::getMax() const {

    return fMax;
}

inline int ClosureToken::getMin() const {

    return fMin;
}

inline Token* ClosureToken::getChild(const XMLSize_t) const {

    return fChild;
}

// ---------------------------------------------------------------------------
//  ClosureToken: setter methods
// ---------------------------------------------------------------------------
inline void ClosureToken::setMax(const int maxVal) {

    fMax = maxVal;
}

inline void ClosureToken::setMin(const int minVal) {

    fMin = minVal;
}

XERCES_CPP_NAMESPACE_END

#endif

/**
  * End of file ClosureToken.hpp
  */
