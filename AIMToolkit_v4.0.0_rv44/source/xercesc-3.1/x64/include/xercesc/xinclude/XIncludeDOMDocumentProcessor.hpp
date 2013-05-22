/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XIncludeDOMDocumentProcessor.hpp 655706 2008-05-13 01:08:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XINCLUDEDOMDOCUMENTPROCESSOR_HPP)
#define XERCESC_INCLUDE_GUARD_XINCLUDEDOMDOCUMENTPROCESSOR_HPP

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/framework/XMLErrorReporter.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLEntityHandler;

/**
  * Class for representing and manipulating the XMLCh * href's used
  * by an xi:include element.
  *
  * This class is designed primarily for internal use. This class implements
  * the functionality required to calculate relative hrefs and the base URI
  * fixups required for performing XInclude functionality.
  */
class XINCLUDE_EXPORT XIncludeDOMDocumentProcessor
{
public:
     /** Walk the supplied DOMDocument performing all XInclude's as encountered.
      *
      * @param source A DOMDocument to parse, this document is not modified.
      * @param errorHandled An errorHandler to call back in case of problems
      *
      * @return a newly created DOMDocument containing the parsed and actioned
      * xinclude elements.
      */
    DOMDocument *doXIncludeDOMProcess(const DOMDocument * const source, XMLErrorReporter *errorHandler, XMLEntityHandler* entityResolver=NULL);
};

XERCES_CPP_NAMESPACE_END

#endif /* XINCLUDEDOMDOCUMENTPROCESSOR_HPP */

