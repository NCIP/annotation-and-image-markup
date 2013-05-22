/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMCDATASectionImpl.hpp 678709 2008-07-22 10:56:56Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMCDATASECTIONIMPL_HPP)
#define XERCESC_INCLUDE_GUARD_DOMCDATASECTIONIMPL_HPP

//
//  This file is part of the internal implementation of the C++ XML DOM.
//  It should NOT be included or used directly by application programs.
//
//  Applications should include the file <xercesc/dom/DOM.hpp> for the entire
//  DOM API, or xercesc/dom/DOM*.hpp for individual DOM classes, where the class
//  name is substituded for the *.
//


#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/dom/DOMCDATASection.hpp>
#include "DOMNodeImpl.hpp"
#include "DOMChildNode.hpp"
#include "DOMParentNode.hpp"
#include "DOMCharacterDataImpl.hpp"

XERCES_CPP_NAMESPACE_BEGIN


class CDOM_EXPORT DOMCDATASectionImpl: public DOMCDATASection {
protected:
    DOMNodeImpl           fNode;
    DOMChildNode          fChild;
    DOMCharacterDataImpl  fCharacterData;


public:
    DOMCDATASectionImpl(DOMDocument *ownerDoc, const XMLCh* data);
    DOMCDATASectionImpl(DOMDocument *ownerDoc, const XMLCh* data, XMLSize_t n);
    DOMCDATASectionImpl(const DOMCDATASectionImpl &other, bool deep = false);

    virtual             ~DOMCDATASectionImpl();

    // Functions inherited from TEXT
    virtual DOMText*     splitText(XMLSize_t offset);
    // DOM Level 3
    virtual bool            getIsElementContentWhitespace() const;
    virtual const XMLCh*    getWholeText() const;
    virtual DOMText*        replaceWholeText(const XMLCh* content);

    // non-standard extension
    virtual bool         isIgnorableWhitespace() const;


public:
    // Declare all of the functions from DOMNode.
    DOMNODE_FUNCTIONS;

public:
    // Functions introduced by DOMCharacterData
    virtual const XMLCh* getData() const;
    virtual XMLSize_t    getLength() const;
    virtual const XMLCh* substringData(XMLSize_t offset,
                                       XMLSize_t count) const;
    virtual void         appendData(const XMLCh *arg);
    virtual void         insertData(XMLSize_t offset, const  XMLCh *arg);
    virtual void         deleteData(XMLSize_t offset,
                                    XMLSize_t count);
    virtual void         replaceData(XMLSize_t offset,
                                     XMLSize_t count,
                                     const XMLCh *arg);
    virtual void         setData(const XMLCh *data);

private:
    // -----------------------------------------------------------------------
    // Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    DOMCDATASectionImpl & operator = (const DOMCDATASectionImpl &);
};

XERCES_CPP_NAMESPACE_END

#endif
