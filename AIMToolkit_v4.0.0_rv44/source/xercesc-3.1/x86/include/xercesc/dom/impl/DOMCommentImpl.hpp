/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMCommentImpl.hpp 676911 2008-07-15 13:27:32Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMCOMMENTIMPL_HPP)
#define XERCESC_INCLUDE_GUARD_DOMCOMMENTIMPL_HPP

//
//  This file is part of the internal implementation of the C++ XML DOM.
//  It should NOT be included or used directly by application programs.
//
//  Applications should include the file <xercesc/dom/DOM.hpp> for the entire
//  DOM API, or xercesc/dom/DOM*.hpp for individual DOM classes, where the class
//  name is substituded for the *.
//


#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/dom/DOMComment.hpp>

#include "DOMNodeImpl.hpp"
#include "DOMChildNode.hpp"
#include "DOMCharacterDataImpl.hpp"

XERCES_CPP_NAMESPACE_BEGIN


class CDOM_EXPORT DOMCommentImpl: public DOMComment {
public:
    DOMNodeImpl            fNode;
    DOMChildNode           fChild;
    DOMCharacterDataImpl   fCharacterData;

public:
    DOMCommentImpl(DOMDocument *, const XMLCh *);
    DOMCommentImpl(const DOMCommentImpl &other, bool deep);
    virtual ~DOMCommentImpl();

public:
    // Declare all of the functions from DOMNode.
    DOMNODE_FUNCTIONS;

public:
    // Functions from DOMCharacterData
    virtual void          appendData(const  XMLCh *data);
    virtual void          deleteData(XMLSize_t offset, XMLSize_t count);
    virtual const XMLCh * getData() const;
    virtual XMLSize_t     getLength() const;
    virtual void          insertData(XMLSize_t offset, const XMLCh * data);
    virtual void          replaceData(XMLSize_t offset, XMLSize_t count, const XMLCh * data);
    virtual void          setData(const XMLCh * arg);
    virtual const XMLCh * substringData(XMLSize_t offset, XMLSize_t count) const;

    // Non standard extension for the range to work
    DOMComment* splitText(XMLSize_t offset);

private:
    // -----------------------------------------------------------------------
    // Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    DOMCommentImpl & operator = (const DOMCommentImpl &);
};

XERCES_CPP_NAMESPACE_END

#endif

