/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XMLInitializer.hpp 695427 2008-09-15 11:05:36Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XMLINITIALIZER_HPP)
#define XERCESC_INCLUDE_GUARD_XMLINITIALIZER_HPP

#include <xercesc/util/XercesDefs.hpp>

XERCES_CPP_NAMESPACE_BEGIN


/**
  * Utilities that must be implemented in a class-specific way.
  *
  * This class contains methods that must be implemented by different
  * classes that have static data (class or local) that they need
  * to initialize when XMLPlatformUtils::Initialize is invoked.
  */
class XMLUTIL_EXPORT XMLInitializer
{
protected :
    /** @name Initialization methods */
    //@{

    /** Perform per-class allocationa and initialization of static data
      *
      * These functions should be called from XMLPlatformUtils::Initialize.
      */
    static void initializeTransService();
    static void initializeStaticData();

    /** Perform per-class release of static data
      *
      * These functions should be called from XMLPlatformUtils::Terminate.
      */
    static void terminateStaticData();
    static void terminateTransService();

    //@}

    friend class XMLPlatformUtils;

private :
    XMLInitializer();
    XMLInitializer(const XMLInitializer& toCopy);
    XMLInitializer& operator=(const XMLInitializer&);

private:
    // Note: The name of each function should be in the form
    // initialize<class-name>.
    //
    // Note: In some cases order of initialization is important.
    //

    //
    // Initialize
    //

    // Core
    //
    static void initializeEncodingValidator();
    static void initializeXMLException();
    static void initializeXMLScanner();
    static void initializeXMLValidator();

    // Regex
    //
    static void initializeRangeTokenMap();
    static void initializeRegularExpression();

    // DTD
    //
    static void initializeDTDGrammar();

    // Schema
    //
    static void initializeXSDErrorReporter();
    static void initializeDatatypeValidatorFactory();
    static void initializeGeneralAttributeCheck();
    static void initializeXSValue();
    static void initializeComplexTypeInfo();

    // DOM
    //
    static void initializeDOMImplementationRegistry();
    static void initializeDOMImplementationImpl();
    static void initializeDOMDocumentTypeImpl();
    static void initializeDOMNodeListImpl();
    static void initializeDOMNormalizer();


    //
    // Terminate
    //

    // Core
    //
    static void terminateEncodingValidator();
    static void terminateXMLException();
    static void terminateXMLScanner();
    static void terminateXMLValidator();

    // Regex
    //
    static void terminateRangeTokenMap();
    static void terminateRegularExpression();

    // DTD
    //
    static void terminateDTDGrammar();

    // Schema
    //
    static void terminateXSDErrorReporter();
    static void terminateDatatypeValidatorFactory();
    static void terminateGeneralAttributeCheck();
    static void terminateXSValue();
    static void terminateComplexTypeInfo();

    // DOM
    //
    static void terminateDOMImplementationRegistry();
    static void terminateDOMImplementationImpl();
    static void terminateDOMDocumentTypeImpl();
    static void terminateDOMNodeListImpl();
    static void terminateDOMNormalizer();

    //
    // Extra initialization.
    //
    static void initializeDOMHeap (XMLSize_t initialHeapAllocSize,
                                   XMLSize_t maxHeapAllocSize,
                                   XMLSize_t maxSubAllocationSize);
};


XERCES_CPP_NAMESPACE_END

#endif
