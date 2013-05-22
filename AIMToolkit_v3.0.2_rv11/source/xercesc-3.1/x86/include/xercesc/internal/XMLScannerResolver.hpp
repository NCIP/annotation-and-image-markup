/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XMLScannerResolver.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XMLSCANNERRESOLVER_HPP)
#define XERCESC_INCLUDE_GUARD_XMLSCANNERRESOLVER_HPP

#include <xercesc/internal/XMLScanner.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLValidator;
class XMLDocumentHandler;
class XMLErrorReporter;
class DocTypeHandler;
class XMLEntityHandler;

class XMLPARSER_EXPORT XMLScannerResolver
{
public:
    // -----------------------------------------------------------------------
    //  Public class methods
    // -----------------------------------------------------------------------
    static XMLScanner* resolveScanner
    (
          const XMLCh* const   scannerName
        , XMLValidator* const  valToAdopt
        , GrammarResolver* const grammarResolver
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );

    static XMLScanner* resolveScanner
    (
          const XMLCh* const        scannerName
        , XMLDocumentHandler* const docHandler
        , DocTypeHandler* const     docTypeHandler
        , XMLEntityHandler* const   entityHandler
        , XMLErrorReporter* const   errReporter
        , XMLValidator* const       valToAdopt
        , GrammarResolver* const    grammarResolver
        , MemoryManager* const      manager = XMLPlatformUtils::fgMemoryManager
    );

    static XMLScanner* getDefaultScanner
    (
          XMLValidator* const  valToAdopt
        , GrammarResolver* const grammarResolver
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );

private :

    // -----------------------------------------------------------------------
    //  Unimplemented constructor and destructor
    // -----------------------------------------------------------------------
    XMLScannerResolver();
    ~XMLScannerResolver();
};

XERCES_CPP_NAMESPACE_END

#endif
