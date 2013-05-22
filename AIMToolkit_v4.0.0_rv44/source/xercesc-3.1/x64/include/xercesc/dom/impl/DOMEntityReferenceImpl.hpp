/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMEntityReferenceImpl.hpp 641193 2008-03-26 08:06:57Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMENTITYREFERENCEIMPL_HPP)
#define XERCESC_INCLUDE_GUARD_DOMENTITYREFERENCEIMPL_HPP

//
//  This file is part of the internal implementation of the C++ XML DOM.
//  It should NOT be included or used directly by application programs.
//
//  Applications should include the file <xercesc/dom/DOM.hpp> for the entire
//  DOM API, or xercesc/dom/DOM*.hpp for individual DOM classes, where the class
//  name is substituded for the *.
//

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/dom/DOMEntityReference.hpp>

#include "DOMParentNode.hpp"
#include "DOMChildNode.hpp"
#include "DOMNodeImpl.hpp"

XERCES_CPP_NAMESPACE_BEGIN


class CDOM_EXPORT DOMEntityReferenceImpl: public DOMEntityReference
{
protected:
    DOMNodeImpl      fNode;
    DOMParentNode    fParent;
    DOMChildNode     fChild;

    const XMLCh    *fName;
    const XMLCh    *fBaseURI;

    friend class XercesDOMParser;

public:
    DOMEntityReferenceImpl(DOMDocument *ownerDoc, const XMLCh *entityName);
    DOMEntityReferenceImpl(DOMDocument *ownerDoc, const XMLCh *entityName, bool cloneChild);
    DOMEntityReferenceImpl(const DOMEntityReferenceImpl &other, bool deep=false);
    virtual ~DOMEntityReferenceImpl();

public:
    // Declare all of the functions from DOMNode.
    DOMNODE_FUNCTIONS;
    
public:
    virtual void setReadOnly(bool readOnly,bool deep);

private:
    // -----------------------------------------------------------------------
    // Unimplemented constructors and operators
    // -----------------------------------------------------------------------    
    DOMEntityReferenceImpl & operator = (const DOMEntityReferenceImpl &);
};

XERCES_CPP_NAMESPACE_END

#endif

