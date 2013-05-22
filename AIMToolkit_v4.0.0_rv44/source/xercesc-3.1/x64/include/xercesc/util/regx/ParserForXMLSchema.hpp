/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: ParserForXMLSchema.hpp 678879 2008-07-22 20:05:05Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_PARSERFORXMLSCHEMA_HPP)
#define XERCESC_INCLUDE_GUARD_PARSERFORXMLSCHEMA_HPP

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/regx/RegxParser.hpp>

XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  Forward Declaration
// ---------------------------------------------------------------------------
class Token;
class RangeToken;

class XMLUTIL_EXPORT ParserForXMLSchema : public RegxParser {
public:
    // -----------------------------------------------------------------------
    //  Public Constructors and Destructor
    // -----------------------------------------------------------------------
    ParserForXMLSchema(MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);
    ~ParserForXMLSchema();

    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------

protected:
    // -----------------------------------------------------------------------
    //  Parsing/Processing methods
    // -----------------------------------------------------------------------
    Token*      processCaret();
    Token*      processDollar();
    Token*      processStar(Token* const tok);
    Token*      processPlus(Token* const tok);
    Token*      processQuestion(Token* const tok);
    Token*      processParen();
    Token*      processBackReference();

    // -----------------------------------------------------------------------
    //  Helper methods
    // -----------------------------------------------------------------------
    bool checkQuestion(const XMLSize_t off);
    XMLInt32 decodeEscaped();

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    ParserForXMLSchema(const ParserForXMLSchema&);
    ParserForXMLSchema& operator=(const ParserForXMLSchema&);

    // -----------------------------------------------------------------------
    //  Private data members
    // -----------------------------------------------------------------------
};

XERCES_CPP_NAMESPACE_END

#endif

/**
  * End of file ParserForXMLSchema.hpp
  */
