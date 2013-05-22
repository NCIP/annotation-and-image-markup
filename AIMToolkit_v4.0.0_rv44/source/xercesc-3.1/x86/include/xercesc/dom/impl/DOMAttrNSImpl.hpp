/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMAttrNSImpl.hpp 678709 2008-07-22 10:56:56Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMATTRNSIMPL_HPP)
#define XERCESC_INCLUDE_GUARD_DOMATTRNSIMPL_HPP

//
//  This file is part of the internal implementation of the C++ XML DOM.
//  It should NOT be included or used directly by application programs.
//
//  Applications should include the file <xercesc/dom/DOM.hpp> for the entire
//  DOM API, or xercesc/dom/DOM*.hpp for individual DOM classes, where the class
//  name is substituded for the *.
//

#include "DOMAttrImpl.hpp"

XERCES_CPP_NAMESPACE_BEGIN


class CDOM_EXPORT DOMAttrNSImpl: public DOMAttrImpl {
protected:
    //Introduced in DOM Level 2
    const XMLCh * fNamespaceURI;     //namespace URI of this node
    const XMLCh * fLocalName;        //local part of qualified name
    const XMLCh * fPrefix;           // prefix part of qualified name
                           // revisit - can return local part
                           //    by pointing into the qualified (L1) name.

public:
    DOMAttrNSImpl(DOMDocument *ownerDoc, const XMLCh *name);
    DOMAttrNSImpl(DOMDocument *ownerDoc, //DOM Level 2
                  const XMLCh *namespaceURI, const XMLCh *qualifiedName);
    DOMAttrNSImpl(const DOMAttrNSImpl &other, bool deep=false);

    // Fast construction without any checks for name validity. Used in
    // parsing. Note that if prefix is not specified and localName is
    // 'xmlns', this constructor expects proper namespaceURI.
    //
    DOMAttrNSImpl(DOMDocument *ownerDoc,
                  const XMLCh *namespaceURI,
                  const XMLCh *prefix,        // Null or empty - no prefix.
                  const XMLCh *localName,
                  const XMLCh *qualifiedName);

    virtual DOMNode * cloneNode(bool deep) const;
    //Introduced in DOM Level 2
    virtual const XMLCh *   getNamespaceURI() const;
    virtual const XMLCh *   getPrefix() const;
    virtual const XMLCh *   getLocalName() const;
    virtual void            setPrefix(const XMLCh *prefix);
    virtual void            release();

   // helper function for DOM Level 3 renameNode
   virtual DOMNode* rename(const XMLCh* namespaceURI, const XMLCh* name);
   void setName(const XMLCh* namespaceURI, const XMLCh* name);

private:
    // -----------------------------------------------------------------------
    // Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    DOMAttrNSImpl & operator = (const DOMAttrNSImpl &);
};

XERCES_CPP_NAMESPACE_END

#endif
