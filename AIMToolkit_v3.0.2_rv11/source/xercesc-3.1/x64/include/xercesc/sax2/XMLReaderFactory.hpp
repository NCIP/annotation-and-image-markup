/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XMLReaderFactory.hpp 932887 2010-04-11 13:04:59Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XMLREADERFACTORY_HPP)
#define XERCESC_INCLUDE_GUARD_XMLREADERFACTORY_HPP

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax/SAXException.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class MemoryManager;
class XMLGrammarPool;

/**
  * Creates a SAX2 parser (SAX2XMLReader).
  *
  * <p>Note: The parser object returned by XMLReaderFactory is owned by the
  * calling users, and it's the responsibility of the users to delete that
  * parser object, once they no longer need it.</p>
  *
  * @see SAX2XMLReader#SAX2XMLReader
  */
class SAX2_EXPORT XMLReaderFactory
{
protected:                // really should be private, but that causes compiler warnings.
	XMLReaderFactory() ;
	~XMLReaderFactory() ;

public:
	static SAX2XMLReader * createXMLReader(  MemoryManager* const  manager = XMLPlatformUtils::fgMemoryManager
                                           , XMLGrammarPool* const gramPool = 0
                                          ) ;
	static SAX2XMLReader * createXMLReader(const XMLCh* className)  ;

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XMLReaderFactory(const XMLReaderFactory&);
    XMLReaderFactory& operator=(const XMLReaderFactory&);
};

inline SAX2XMLReader * XMLReaderFactory::createXMLReader(const XMLCh *)
{	
	throw SAXNotSupportedException();
	// unimplemented
	return 0;
}

XERCES_CPP_NAMESPACE_END

#endif
