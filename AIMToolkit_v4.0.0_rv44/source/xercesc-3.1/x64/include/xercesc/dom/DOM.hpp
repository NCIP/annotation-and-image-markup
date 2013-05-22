/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: DOM.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_DOM_HPP)
#define XERCESC_INCLUDE_GUARD_DOM_HPP

//
//  This is the primary header file for inclusion in application
//  programs using the C++ XML Document Object Model API.
//

#include <xercesc/dom/DOMAttr.hpp>
#include <xercesc/dom/DOMCDATASection.hpp>
#include <xercesc/dom/DOMCharacterData.hpp>
#include <xercesc/dom/DOMComment.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMDocumentFragment.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMEntity.hpp>
#include <xercesc/dom/DOMEntityReference.hpp>
#include <xercesc/dom/DOMException.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMNotation.hpp>
#include <xercesc/dom/DOMProcessingInstruction.hpp>
#include <xercesc/dom/DOMText.hpp>

// Introduced in DOM Level 2
#include <xercesc/dom/DOMDocumentRange.hpp>
#include <xercesc/dom/DOMDocumentTraversal.hpp>
#include <xercesc/dom/DOMNodeFilter.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMRange.hpp>
#include <xercesc/dom/DOMRangeException.hpp>
#include <xercesc/dom/DOMTreeWalker.hpp>

// Introduced in DOM Level 3
#include <xercesc/dom/DOMLSParser.hpp>
#include <xercesc/dom/DOMLSParserFilter.hpp>
#include <xercesc/dom/DOMConfiguration.hpp>
#include <xercesc/dom/DOMLSResourceResolver.hpp>
#include <xercesc/dom/DOMError.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMImplementationList.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>
#include <xercesc/dom/DOMImplementationSource.hpp>
#include <xercesc/dom/DOMLSInput.hpp>
#include <xercesc/dom/DOMLSOutput.hpp>
#include <xercesc/dom/DOMLocator.hpp>
#include <xercesc/dom/DOMPSVITypeInfo.hpp>
#include <xercesc/dom/DOMStringList.hpp>
#include <xercesc/dom/DOMTypeInfo.hpp>
#include <xercesc/dom/DOMUserDataHandler.hpp>
#include <xercesc/dom/DOMLSSerializer.hpp>
#include <xercesc/dom/DOMLSSerializerFilter.hpp>

#include <xercesc/dom/DOMXPathEvaluator.hpp>
#include <xercesc/dom/DOMXPathNSResolver.hpp>
#include <xercesc/dom/DOMXPathException.hpp>
#include <xercesc/dom/DOMXPathExpression.hpp>
#include <xercesc/dom/DOMXPathResult.hpp>
#include <xercesc/dom/DOMXPathNamespace.hpp>


#endif
