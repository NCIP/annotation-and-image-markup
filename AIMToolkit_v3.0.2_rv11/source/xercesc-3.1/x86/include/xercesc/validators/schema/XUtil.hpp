/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XUtil.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XUTIL_HPP)
#define XERCESC_INCLUDE_GUARD_XUTIL_HPP

#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <xercesc/dom/DOMNode.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class DOMNode;
class DOMElement;

/**
 * Some useful utility methods.
 */
class VALIDATORS_EXPORT XUtil
{
public:

    // Finds and returns the first child element node.
    static DOMElement* getFirstChildElement(const DOMNode* const parent);

    // Finds and returns the first child node with the given qualifiedname.
    static DOMElement* getFirstChildElementNS(const DOMNode* const parent
                                              , const XMLCh** const elemNames
                                              , const XMLCh* const uriStr
                                              , unsigned int       length);

    // Finds and returns the next sibling element node.
    static DOMElement* getNextSiblingElement(const DOMNode* const node);

    static DOMElement* getNextSiblingElementNS(const DOMNode* const node
                                               , const XMLCh** const elemNames
                                               , const XMLCh* const uriStr
                                               , unsigned int        length);

private:
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------

	// This class cannot be instantiated.
     XUtil() {};
	~XUtil() {};
};

XERCES_CPP_NAMESPACE_END

#endif
