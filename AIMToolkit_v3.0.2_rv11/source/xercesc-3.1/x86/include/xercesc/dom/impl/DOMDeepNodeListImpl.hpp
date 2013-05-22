/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMDeepNodeListImpl.hpp 671894 2008-06-26 13:29:21Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMDEEPNODELISTIMPL_HPP)
#define XERCESC_INCLUDE_GUARD_DOMDEEPNODELISTIMPL_HPP

//
//  This file is part of the internal implementation of the C++ XML DOM.
//  It should NOT be included or used directly by application programs.
//
//  Applications should include the file <xercesc/dom/DOM.hpp> for the entire
//  DOM API, or xercesc/dom/DOM*.hpp for individual DOM classes, where the class
//  name is substituded for the *.
//

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/dom/DOMNodeList.hpp>

XERCES_CPP_NAMESPACE_BEGIN


class DOMNode;


class CDOM_EXPORT DOMDeepNodeListImpl: public DOMNodeList {
protected:
    const DOMNode*   fRootNode;
    const XMLCh*     fTagName;
    bool             fMatchAll;
    int              fChanges;
    DOMNode*         fCurrentNode;
    XMLSize_t        fCurrentIndexPlus1;

    //DOM Level 2
    const XMLCh*     fNamespaceURI;
    bool	     fMatchAllURI;
    bool             fMatchURIandTagname; //match both namespaceURI and tagName

public:
    DOMDeepNodeListImpl(const DOMNode *rootNode, const XMLCh *tagName);
    DOMDeepNodeListImpl(const DOMNode *rootNode,	//DOM Level 2
	                    const XMLCh *namespaceURI,
                       const XMLCh *localName);
    virtual          ~DOMDeepNodeListImpl();
    virtual XMLSize_t    getLength() const;
    virtual DOMNode*     item(XMLSize_t index) const;
    DOMNode*             cacheItem(XMLSize_t index);

protected:
    DOMNode*          nextMatchingElementAfter(DOMNode *current);

private:
    // -----------------------------------------------------------------------
    // Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    DOMDeepNodeListImpl(const DOMDeepNodeListImpl &);
    DOMDeepNodeListImpl & operator = (const DOMDeepNodeListImpl &);
};

XERCES_CPP_NAMESPACE_END

#endif
