/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMTextImpl.hpp 678709 2008-07-22 10:56:56Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMTEXTIMPL_HPP)
#define XERCESC_INCLUDE_GUARD_DOMTEXTIMPL_HPP

//
//  This file is part of the internal implementation of the C++ XML DOM.
//  It should NOT be included or used directly by application programs.
//
//  Applications should include the file <xercesc/dom/DOM.hpp> for the entire
//  DOM API, or xercesc/dom/DOM*.hpp for individual DOM classes, where the class
//  name is substituded for the *.
//



#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/dom/DOMText.hpp>

#include "DOMChildNode.hpp"
#include "DOMNodeImpl.hpp"
#include "DOMCharacterDataImpl.hpp"

XERCES_CPP_NAMESPACE_BEGIN


class CDOM_EXPORT DOMTextImpl: public DOMText {
public:
    DOMNodeImpl             fNode;
    DOMChildNode            fChild;
    DOMCharacterDataImpl    fCharacterData;

public:
    DOMTextImpl(DOMDocument* ownerDoc, const XMLCh* data);
    DOMTextImpl(DOMDocument *ownerDoc, const XMLCh* data, XMLSize_t n);
    DOMTextImpl(const DOMTextImpl& other, bool deep=false);

    virtual                ~DOMTextImpl();
    virtual DOMText*        splitText(XMLSize_t offset);
    // DOM Level 3
    virtual bool            getIsElementContentWhitespace() const;
    virtual const XMLCh*    getWholeText() const;
    virtual DOMText*        replaceWholeText(const XMLCh* content);

    // non-standard extension
    virtual bool            isIgnorableWhitespace() const;

public:
    // Declare the functions coming from DOMNode.
    DOMNODE_FUNCTIONS;

public:
    // All of the functions coming from DOMCharacterData
    virtual const XMLCh*    getData() const;
    virtual XMLSize_t       getLength() const;
    virtual const XMLCh*    substringData(XMLSize_t offset,
                                          XMLSize_t count) const;
    virtual void            appendData(const XMLCh *arg);
    virtual void            insertData(XMLSize_t offset, const  XMLCh *arg);
    virtual void            deleteData(XMLSize_t offset,
                                       XMLSize_t count);
    virtual void            replaceData(XMLSize_t offset,
                                        XMLSize_t count,
                                        const XMLCh *arg);
    virtual void            setData(const XMLCh *data);

    // Non-standard extension.
    //
    virtual void            appendData(const XMLCh *arg, XMLSize_t n);

protected:
    virtual void            setIgnorableWhitespace(bool ignorable);
    friend class            AbstractDOMParser;

private:
    // -----------------------------------------------------------------------
    // Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    DOMTextImpl & operator = (const DOMTextImpl &);
};

XERCES_CPP_NAMESPACE_END

#endif
