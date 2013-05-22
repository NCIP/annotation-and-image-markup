/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XSDElementNSImpl.hpp 672232 2008-06-27 10:16:38Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XSDELEMENTNSIMPL_HPP)
#define XERCESC_INCLUDE_GUARD_XSDELEMENTNSIMPL_HPP

//
//  This file is part of the internal implementation of the C++ XML DOM.
//  It is used by TraverseSchema to store line/column information.
//  It should NOT be included or used directly by application programs.
//
//  Applications should include the file <xercesc/dom/DOM.hpp> for the entire
//  DOM API, or xercesc/dom/DOM*.hpp for individual DOM classes, where the class
//  name is substituded for the *.
//


#include "DOMElementNSImpl.hpp"

XERCES_CPP_NAMESPACE_BEGIN



class CDOM_EXPORT XSDElementNSImpl: public DOMElementNSImpl {
protected:
    XMLFileLoc fLineNo;     //Line number
    XMLFileLoc fColumnNo;   //Column number


public:
    XSDElementNSImpl(DOMDocument *ownerDoc, const XMLCh *name);
    XSDElementNSImpl(DOMDocument *ownerDoc, //DOM Level 2
	                 const XMLCh *namespaceURI,
                     const XMLCh *qualifiedName,
                     const XMLFileLoc lineNo,
                     const XMLFileLoc columnNo);
    XSDElementNSImpl(const XSDElementNSImpl &other, bool deep=false);

    virtual DOMNode * cloneNode(bool deep) const;

    XMLFileLoc getLineNo() const   { return fLineNo;   }
    XMLFileLoc getColumnNo() const { return fColumnNo; }

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XSDElementNSImpl& operator=(const XSDElementNSImpl&);
};

XERCES_CPP_NAMESPACE_END

#endif
