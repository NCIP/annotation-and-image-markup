/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMNotationImpl.hpp 641193 2008-03-26 08:06:57Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMNOTATIONIMPL_HPP)
#define XERCESC_INCLUDE_GUARD_DOMNOTATIONIMPL_HPP

//
//  This file is part of the internal implementation of the C++ XML DOM.
//  It should NOT be included or used directly by application programs.
//
//  Applications should include the file <xercesc/dom/DOM.hpp> for the entire
//  DOM API, or xercesc/dom/DOM*.hpp for individual DOM classes, where the class
//  name is substituded for the *.
//

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/dom/DOMNotation.hpp>

XERCES_CPP_NAMESPACE_BEGIN


#include "DOMNodeImpl.hpp"

class DOMDocument;


class CDOM_EXPORT DOMNotationImpl: public DOMNotation {
public:
    DOMNodeImpl      fNode;

    const XMLCh * fName;
    const XMLCh * fPublicId;
    const XMLCh * fSystemId;
    const XMLCh * fBaseURI;

public:
    DOMNotationImpl(DOMDocument *ownerDoc, const XMLCh *);
    DOMNotationImpl(const DOMNotationImpl &other, bool deep=false);

    virtual ~DOMNotationImpl();

public:
    // Declare all of the functions from DOMNode.
    DOMNODE_FUNCTIONS;

public:
    //
    // The Public Identifier for this Notation. If no public identifier
    // was specified, this will be null.
    virtual const XMLCh * getPublicId() const;

    // The System Identifier for this Notation. If no system identifier
    // was specified, this will be null.
    virtual const XMLCh * getSystemId() const;

    // NON-DOM: The Public Identifier for this Notation. If no public
    // identifier was specified, this will be null.
    virtual void setPublicId(const XMLCh *arg);


    // NON-DOM: The System Identifier for this Notation. If no system
    // identifier was specified, this will be null.
    virtual void setSystemId(const XMLCh *arg);

    // NON-DOM: set base uri
    virtual void setBaseURI(const XMLCh *arg);

private:
    // unimplemented    
    DOMNotationImpl& operator= (const DOMNotationImpl& other);
};

XERCES_CPP_NAMESPACE_END

#endif
