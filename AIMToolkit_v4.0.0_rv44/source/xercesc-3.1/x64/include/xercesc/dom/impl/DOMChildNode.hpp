/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOMChildNode.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOMCHILDNODE_HPP)
#define XERCESC_INCLUDE_GUARD_DOMCHILDNODE_HPP

//
//  This file is part of the internal implementation of the C++ XML DOM.
//  It should NOT be included or used directly by application programs.
//
//  Applications should include the file <xercesc/dom/DOM.hpp> for the entire
//  DOM API, or xercesc/dom/DOM*.hpp for individual DOM classes, where the class
//  name is substituded for the *.
//

/**
 * ChildNode adds to NodeImpl the capability of being a child, this is having
 * siblings.
 **/

#include <xercesc/util/XercesDefs.hpp>

XERCES_CPP_NAMESPACE_BEGIN


class DOMDocument;
class DOMNode;


class CDOM_EXPORT DOMChildNode {

public:
    DOMNode                *previousSibling;
    DOMNode                *nextSibling;

    DOMChildNode();
    DOMChildNode(const DOMChildNode &other);
    ~DOMChildNode();

    DOMNode * getNextSibling() const;
    DOMNode * getParentNode(const DOMNode *thisNode) const;
    DOMNode * getPreviousSibling(const DOMNode *thisNode) const;

private:
    // -----------------------------------------------------------------------
    // Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    DOMChildNode & operator = (const DOMChildNode &);   
};


XERCES_CPP_NAMESPACE_END

#endif
