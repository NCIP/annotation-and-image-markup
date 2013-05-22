/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: TokenFactory.hpp 678879 2008-07-22 20:05:05Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_TOKENFACTORY_HPP)
#define XERCESC_INCLUDE_GUARD_TOKENFACTORY_HPP

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/RefVectorOf.hpp>
#include <xercesc/util/regx/Token.hpp>
#include <xercesc/util/Mutexes.hpp>

XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  Forward Declaration
// ---------------------------------------------------------------------------
class RangeToken;
class CharToken;
class ClosureToken;
class ConcatToken;
class ParenToken;
class StringToken;
class UnionToken;

class XMLUTIL_EXPORT TokenFactory : public XMemory
{

public:
    // -----------------------------------------------------------------------
    //  Constructors and destructors
    // -----------------------------------------------------------------------
    TokenFactory(MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);
    ~TokenFactory();

    // -----------------------------------------------------------------------
    //  Factory methods
    // -----------------------------------------------------------------------
    Token* createToken(const Token::tokType tkType);

    ParenToken* createParenthesis(Token* const token, const int noGroups);
    ClosureToken* createClosure(Token* const token, bool isNonGreedy = false);
    ConcatToken* createConcat(Token* const token1, Token* const token2);
    UnionToken* createUnion(const bool isConcat = false);
    RangeToken* createRange(const bool isNegRange = false);
    CharToken* createChar(const XMLUInt32 ch, const bool isAnchor = false);
    StringToken* createBackReference(const int refNo);
    StringToken* createString(const XMLCh* const literal);


    //static void printUnicode();

    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    /*
     *  Gets a commonly used RangeToken from the token registry based on the
     *  range name.
     */
    RangeToken* getRange(const XMLCh* const name,const bool complement=false);
    Token* getLineBegin();
    Token* getLineEnd();
    Token* getDot();
    MemoryManager* getMemoryManager() const;

    static RangeToken* staticGetRange(const XMLCh* const name,const bool complement=false);

    // -----------------------------------------------------------------------
    //  Notification that lazy data has been deleted
    // -----------------------------------------------------------------------
    static void reinitTokenFactoryMutex();

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    TokenFactory(const TokenFactory&);
    TokenFactory& operator=(const TokenFactory&);

    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fRangeInitialized
    //      Indicates whether we have initialized the RangeFactory instance or
    //      not
    //        
    //  fToken
    //      Contains user created Token objects. Used for memory cleanup.
    // -----------------------------------------------------------------------
    RefVectorOf<Token>* fTokens;
    Token*              fEmpty;
    Token*              fLineBegin;
    Token*              fLineEnd;
    Token*              fDot;
    MemoryManager*      fMemoryManager;
};

inline RangeToken* TokenFactory::getRange(const XMLCh* const name,const bool complement)
{
    return staticGetRange(name, complement);
}

inline MemoryManager* TokenFactory::getMemoryManager() const
{
    return fMemoryManager;
}

XERCES_CPP_NAMESPACE_END

#endif

/**
  *    End file TokenFactory
  */

