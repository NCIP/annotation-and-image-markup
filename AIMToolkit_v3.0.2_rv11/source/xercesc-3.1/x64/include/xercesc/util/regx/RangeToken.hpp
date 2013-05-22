/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: RangeToken.hpp 678879 2008-07-22 20:05:05Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_RANGETOKEN_HPP)
#define XERCESC_INCLUDE_GUARD_RANGETOKEN_HPP

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/regx/Token.hpp>

XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  Forward Declaration
// ---------------------------------------------------------------------------
class TokenFactory;


class XMLUTIL_EXPORT RangeToken : public Token {
public:
    // -----------------------------------------------------------------------
    //  Public Constructors and Destructor
    // -----------------------------------------------------------------------
    RangeToken(const tokType tkType,
               MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);
    ~RangeToken();

    // -----------------------------------------------------------------------
    //  Public Constants
    // -----------------------------------------------------------------------
    static const int MAPSIZE;
    static const unsigned int INITIALSIZE;

    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    RangeToken* getCaseInsensitiveToken(TokenFactory* const tokFactory);

    void setCaseInsensitiveToken(RangeToken* tok);

    // -----------------------------------------------------------------------
    //  Setter methods
    // -----------------------------------------------------------------------
    void setRangeValues(XMLInt32* const rangeValues, const unsigned int count);

    // -----------------------------------------------------------------------
    //  Range manipulation methods
    // -----------------------------------------------------------------------
    void addRange(const XMLInt32 start, const XMLInt32 end);
    void mergeRanges(const Token *const tok);
    void sortRanges();
    void compactRanges();
    void subtractRanges(RangeToken* const tok);
    void intersectRanges(RangeToken* const tok);
    static RangeToken* complementRanges(RangeToken* const tok,
                                   TokenFactory* const tokFactory,
                                   MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);

    bool empty() const;

    // -----------------------------------------------------------------------
    //  Match methods
    // -----------------------------------------------------------------------
    bool match(const XMLInt32 ch);

    // -----------------------------------------------------------------------
    //  Creates the map.  This will happen automatically,
    //  necessary.
    // -----------------------------------------------------------------------
    void createMap();

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    RangeToken(const RangeToken&);
    RangeToken& operator=(const RangeToken&);

    // -----------------------------------------------------------------------
    // Private Helper methods
    // -----------------------------------------------------------------------
    void expand(const unsigned int length);

    void doCreateMap();

    // -----------------------------------------------------------------------
    //  Private data members
    // -----------------------------------------------------------------------
    bool         fSorted;
    bool         fCompacted;
    int          fNonMapIndex;
    unsigned int fElemCount;
    unsigned int fMaxCount;
    int*         fMap;
    XMLInt32*    fRanges;
    RangeToken*  fCaseIToken;
    MemoryManager* fMemoryManager;
};


inline void RangeToken::setCaseInsensitiveToken(RangeToken* tok)
{
    fCaseIToken = tok;
}

inline void RangeToken::createMap()
{
    if (!fMap)
    {
        doCreateMap();
    }
}

inline bool RangeToken::empty() const
{
    return fElemCount==0; 
}

XERCES_CPP_NAMESPACE_END

#endif

/**
  * End of file RangeToken.hpp
  */

