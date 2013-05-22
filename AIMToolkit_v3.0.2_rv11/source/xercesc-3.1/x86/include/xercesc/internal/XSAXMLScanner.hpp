/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XSAXMLScanner.hpp 676911 2008-07-15 13:27:32Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XSAXMLSCANNER_HPP)
#define XERCESC_INCLUDE_GUARD_XSAXMLSCANNER_HPP

#include <xercesc/internal/SGXMLScanner.hpp>


XERCES_CPP_NAMESPACE_BEGIN

//
//  This is a scanner class, which processes/validates contents of XML Schema
//  Annotations. It's intended for internal use only.
//
class XMLPARSER_EXPORT XSAXMLScanner : public SGXMLScanner
{
public :
    // -----------------------------------------------------------------------
    //  Destructor
    // -----------------------------------------------------------------------
    virtual ~XSAXMLScanner();

    // -----------------------------------------------------------------------
    //  XMLScanner public virtual methods
    // -----------------------------------------------------------------------
    virtual const XMLCh* getName() const;

protected:
    // -----------------------------------------------------------------------
    //  Constructors
    // -----------------------------------------------------------------------
    /**
     * The grammar representing the XML Schema annotation (xsaGrammar) is
     * passed in by the caller. The scanner will own it and is responsible
     * for deleting it.
     */
    XSAXMLScanner
    (
        GrammarResolver* const grammarResolver
        , XMLStringPool* const   uriStringPool
        , SchemaGrammar* const   xsaGrammar
        , MemoryManager* const   manager = XMLPlatformUtils::fgMemoryManager
    );
    friend class TraverseSchema;

    // -----------------------------------------------------------------------
    //  XMLScanner virtual methods
    // -----------------------------------------------------------------------
    virtual void scanReset(const InputSource& src);

    // -----------------------------------------------------------------------
    //  SGXMLScanner virtual methods
    // -----------------------------------------------------------------------
    virtual bool scanStartTag(bool& gotData);
    virtual void scanEndTag(bool& gotData);

private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XSAXMLScanner();
    XSAXMLScanner(const XSAXMLScanner&);
    XSAXMLScanner& operator=(const XSAXMLScanner&);

    // -----------------------------------------------------------------------
    //  Private helper methods
    // -----------------------------------------------------------------------
    void scanRawAttrListforNameSpaces(XMLSize_t attCount);
    void switchGrammar(const XMLCh* const newGrammarNameSpace, bool laxValidate);
};

inline const XMLCh* XSAXMLScanner::getName() const
{
    return XMLUni::fgXSAXMLScanner;
}

XERCES_CPP_NAMESPACE_END

#endif
