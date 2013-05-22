/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMDocumentTypeImpl.hpp 641193 2008-03-26 08:06:57Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMDOCUMENTTYPEIMPL_HPP)
#define XERCESC_INCLUDE_GUARD_DOMDOCUMENTTYPEIMPL_HPP

//
//  This file is part of the internal implementation of the C++ XML DOM.
//  It should NOT be included or used directly by application programs.
//
//  Applications should include the file <xercesc/dom/DOM.hpp> for the entire
//  DOM API, or xercesc/dom/DOM*.hpp for individual DOM classes, where the class
//  name is substituded for the *.
//



#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include "DOMNodeImpl.hpp"
#include "DOMChildNode.hpp"
#include "DOMParentNode.hpp"

XERCES_CPP_NAMESPACE_BEGIN


class DOMNamedNodeMapImpl;

class CDOM_EXPORT DOMDocumentTypeImpl: public DOMDocumentType {
protected:
    DOMNodeImpl          fNode;
    DOMParentNode        fParent;
    DOMChildNode         fChild;

    const XMLCh *        fName;
    DOMNamedNodeMapImpl* fEntities;
    DOMNamedNodeMapImpl* fNotations;
    DOMNamedNodeMapImpl* fElements;
    const XMLCh *        fPublicId;
    const XMLCh *        fSystemId;
    const XMLCh *        fInternalSubset;

    bool			     fIntSubsetReading;
    bool                 fIsCreatedFromHeap;

    virtual void         setPublicId(const XMLCh * value);
    virtual void         setSystemId(const XMLCh * value);
    virtual void         setInternalSubset(const XMLCh *value);
    bool                 isIntSubsetReading() const;

    friend class AbstractDOMParser;
    friend class DOMDocumentImpl;

public:
    DOMDocumentTypeImpl(DOMDocument *, const XMLCh *, bool);
    DOMDocumentTypeImpl(DOMDocument *,
                     const XMLCh *qualifiedName,	//DOM Level 2
                     const XMLCh *publicId, const XMLCh *systemId, bool);
    DOMDocumentTypeImpl(const DOMDocumentTypeImpl &other, bool heap, bool deep=false);
    virtual ~DOMDocumentTypeImpl();

public:
    // Declare all of the functions from DOMNode.
    DOMNODE_FUNCTIONS;

public:
    virtual void setOwnerDocument(DOMDocument *doc);
    virtual DOMNamedNodeMap * getEntities() const;
    virtual const XMLCh *       getName() const;
    virtual DOMNamedNodeMap * getNotations() const;
    virtual DOMNamedNodeMap * getElements() const;
    virtual void                setReadOnly(bool readOnly, bool deep);

    //Introduced in DOM Level 2

    virtual const XMLCh *     getPublicId() const;
    virtual const XMLCh *     getSystemId() const;
    virtual const XMLCh *     getInternalSubset() const;

private:
    // -----------------------------------------------------------------------
    // Unimplemented constructors and operators
    // -----------------------------------------------------------------------    
    DOMDocumentTypeImpl & operator = (const DOMDocumentTypeImpl &);
};

XERCES_CPP_NAMESPACE_END

#endif
