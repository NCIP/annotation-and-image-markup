/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMProcessingInstructionImpl.hpp 641193 2008-03-26 08:06:57Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMPROCESSINGINSTRUCTIONIMPL_HPP)
#define XERCESC_INCLUDE_GUARD_DOMPROCESSINGINSTRUCTIONIMPL_HPP

//
//  This file is part of the internal implementation of the C++ XML DOM.
//  It should NOT be included or used directly by application programs.
//
//  Applications should include the file <xercesc/dom/DOM.hpp> for the entire
//  DOM API, or xercesc/dom/DOM*.hpp for individual DOM classes, where the class
//  name is substituded for the *.
//


#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/dom/DOMProcessingInstruction.hpp>
#include "DOMCharacterDataImpl.hpp"
#include "DOMNodeImpl.hpp"
#include "DOMChildNode.hpp"

XERCES_CPP_NAMESPACE_BEGIN


class    DocumentImpl;


class CDOM_EXPORT DOMProcessingInstructionImpl: public DOMProcessingInstruction {
protected:
    DOMNodeImpl   fNode;
    DOMChildNode  fChild;
    // use fCharacterData to store its data so that those character utitlites can be used
    DOMCharacterDataImpl   fCharacterData;

    XMLCh       *fTarget;
    const XMLCh *fBaseURI;

public:
    DOMProcessingInstructionImpl(DOMDocument *ownerDoc,
                              const XMLCh * target,
                              const XMLCh *data);
    DOMProcessingInstructionImpl(const DOMProcessingInstructionImpl &other,
                              bool deep=false);
    virtual ~DOMProcessingInstructionImpl();

public:
    // Declare all of the functions from DOMNode.
    DOMNODE_FUNCTIONS;

public:
    virtual const XMLCh *getData() const;
    virtual const XMLCh *getTarget() const;
    virtual void setData(const XMLCh *arg);

    // NON-DOM: set base uri
    virtual void setBaseURI(const XMLCh* baseURI);

    // Non standard extension for the range to work
    void         deleteData(XMLSize_t offset, XMLSize_t count);
    const XMLCh* substringData(XMLSize_t offset, XMLSize_t count) const;
    DOMProcessingInstruction* splitText(XMLSize_t offset);

private:
    // -----------------------------------------------------------------------
    // Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    DOMProcessingInstructionImpl & operator = (const DOMProcessingInstructionImpl &);
};

XERCES_CPP_NAMESPACE_END

#endif

