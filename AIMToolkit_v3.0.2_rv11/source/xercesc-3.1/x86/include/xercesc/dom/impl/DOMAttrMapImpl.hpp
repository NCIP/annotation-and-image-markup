/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMAttrMapImpl.hpp 678709 2008-07-22 10:56:56Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMATTRMAPIMPL_HPP)
#define XERCESC_INCLUDE_GUARD_DOMATTRMAPIMPL_HPP

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

class DOMNode;
class DOMNodeVector;

class CDOM_EXPORT DOMAttrMapImpl : public DOMNamedNodeMap
{
protected:
    DOMNodeVector*    fNodes;
    DOMNode*          fOwnerNode;       // the node this map belongs to
    bool              attrDefaults;

    virtual void      cloneContent(const DOMAttrMapImpl *srcmap);

    bool              readOnly();  // revisit.  Look at owner node read-only.

public:
    DOMAttrMapImpl(DOMNode *ownerNod);

    // revisit.  This "copy" constructor is used for cloning an Element with Attributes,
    //                and for setting up default attributes.  It's probably not right
    //                for one or the other or both.
    DOMAttrMapImpl(DOMNode *ownerNod, const DOMAttrMapImpl *defaults);
    DOMAttrMapImpl();

    virtual ~DOMAttrMapImpl();
    virtual DOMAttrMapImpl *cloneAttrMap(DOMNode *ownerNode);
    virtual bool hasDefaults();
    virtual void hasDefaults(bool value);
    virtual int             findNamePoint(const XMLCh *name) const;
    virtual int             findNamePoint(const XMLCh *namespaceURI,
	                                       const XMLCh *localName) const;
    virtual DOMNode*        removeNamedItemAt(XMLSize_t index);
    virtual void            setReadOnly(bool readOnly, bool deep);


    virtual XMLSize_t       getLength() const;
    virtual DOMNode*        item(XMLSize_t index) const;

    virtual DOMNode*        getNamedItem(const XMLCh *name) const;
    virtual DOMNode*        setNamedItem(DOMNode *arg);
    virtual DOMNode*        removeNamedItem(const XMLCh *name);

    virtual DOMNode*        getNamedItemNS(const XMLCh *namespaceURI,
	                                        const XMLCh *localName) const;
    virtual DOMNode*        setNamedItemNS(DOMNode *arg);
    virtual DOMNode*        removeNamedItemNS(const XMLCh *namespaceURI, const XMLCh *localName);

    // Fast versions of the above functions which bypass validity checks.
    // It also assumes that fNode is not 0 (call reserve) and that there
    // is no previous node with this name. These are used in parsing.
    //
    void setNamedItemFast(DOMNode *arg);
    void setNamedItemNSFast(DOMNode *arg);

    // Tries to reserve space for the specified number of elements.
    // Currently only works on newly-created instances (fNodes == 0).
    //
    void reserve (XMLSize_t);

    void reconcileDefaultAttributes(const DOMAttrMapImpl* defaults);
    void moveSpecifiedAttributes(DOMAttrMapImpl* srcmap);

private:
    // -----------------------------------------------------------------------
    // Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    DOMAttrMapImpl(const DOMAttrMapImpl &);
    DOMAttrMapImpl & operator = (const DOMAttrMapImpl &);
};

// ---------------------------------------------------------------------------
//  DOMAttrMapImpl: Getters & Setters
// ---------------------------------------------------------------------------

inline bool DOMAttrMapImpl::hasDefaults()
{
    return attrDefaults;
}

inline void DOMAttrMapImpl::hasDefaults(bool value)
{
    attrDefaults = value;
}

XERCES_CPP_NAMESPACE_END


#endif
