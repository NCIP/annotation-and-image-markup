/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMNamedNodeMapImpl.hpp 671894 2008-06-26 13:29:21Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMNAMEDNODEMAPIMPL_HPP)
#define XERCESC_INCLUDE_GUARD_DOMNAMEDNODEMAPIMPL_HPP

//
//  This file is part of the internal implementation of the C++ XML DOM.
//  It should NOT be included or used directly by application programs.
//
//  Applications should include the file <xercesc/dom/DOM.hpp> for the entire
//  DOM API, or xercesc/dom/DOM*.hpp for individual DOM classes, where the class
//  name is substituded for the *.
//

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>

XERCES_CPP_NAMESPACE_BEGIN


class       DOMNodeVector;
class       DOMNode;

#define MAP_SIZE    193

class CDOM_EXPORT DOMNamedNodeMapImpl: public DOMNamedNodeMap {
protected:
    DOMNodeVector*    fBuckets[MAP_SIZE];
    DOMNode*          fOwnerNode;       // the node this map belongs to
    //bool             fReadOnly;     // revisit - flag on owner node instead?

    bool            readOnly();  // revisit.  Look at owner node read-only.

public:
    DOMNamedNodeMapImpl(DOMNode *ownerNode);

    virtual                 ~DOMNamedNodeMapImpl();
    virtual DOMNamedNodeMapImpl *cloneMap(DOMNode *ownerNode);
    virtual void            setReadOnly(bool readOnly, bool deep);

    virtual XMLSize_t       getLength() const;
    virtual DOMNode*        item(XMLSize_t index) const;
    virtual DOMNode*        getNamedItem(const XMLCh *name) const;
    virtual DOMNode*        setNamedItem(DOMNode *arg);
    virtual DOMNode*        removeNamedItem(const XMLCh *name);

    //Introduced in DOM Level 2
    virtual DOMNode*        getNamedItemNS(const XMLCh *namespaceURI,
	                                        const XMLCh *localName) const;
    virtual DOMNode*        setNamedItemNS(DOMNode *arg);
    virtual DOMNode*        removeNamedItemNS(const XMLCh *namespaceURI,
	                                           const XMLCh *localName);
private:
    // unimplemented
    DOMNamedNodeMapImpl(const DOMNamedNodeMapImpl &);
    DOMNamedNodeMapImpl & operator = (const DOMNamedNodeMapImpl &);
};

XERCES_CPP_NAMESPACE_END

#endif
