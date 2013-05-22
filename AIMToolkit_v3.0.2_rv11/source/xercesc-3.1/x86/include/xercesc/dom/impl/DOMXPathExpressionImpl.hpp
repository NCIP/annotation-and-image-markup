/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMXPathExpressionImpl.hpp 671894 2008-06-26 13:29:21Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMXPATHEXPRESSIONIMPL_HPP)
#define XERCESC_INCLUDE_GUARD_DOMXPATHEXPRESSIONIMPL_HPP

#include <xercesc/util/XMemory.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOMXPathExpression.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class DOMElement;
class XercesXPath;
class XPathMatcher;
class DOMXPathResultImpl;
class DOMXPathNSResolver;
class XMLStringPool;

class CDOM_EXPORT DOMXPathExpressionImpl :  public XMemory,
                                            public DOMXPathExpression
{
public:
    DOMXPathExpressionImpl(const XMLCh *expression,
                           const DOMXPathNSResolver *resolver,
                           MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);
    virtual ~DOMXPathExpressionImpl();

    virtual DOMXPathResult* evaluate(const DOMNode *contextNode,
                                     DOMXPathResult::ResultType type,
                                     DOMXPathResult* result) const;

    virtual void release();

protected:
    bool testNode(XPathMatcher* matcher,
                  DOMXPathResultImpl* result,
                  DOMElement *node) const;
    void cleanUp();

    XMLStringPool*              fStringPool;
    XercesXPath*                fParsedExpression;
    XMLCh*                      fExpression;
    bool                        fMoveToRoot;

    MemoryManager* const        fMemoryManager;
};

XERCES_CPP_NAMESPACE_END

#endif
