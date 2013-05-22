/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: IdentityConstraintHandler.hpp 932887 2010-04-11 13:04:59Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_IDENTITYCONSTRAINT_HANDLER_HPP)
#define XERCESC_INCLUDE_GUARD_IDENTITYCONSTRAINT_HANDLER_HPP

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/validators/schema/identity/ValueStoreCache.hpp>
#include <xercesc/validators/schema/identity/XPathMatcherStack.hpp>

XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  Forward Declarations
// ---------------------------------------------------------------------------

class XMLScanner;
class FieldActivator;
class MemoryManager;
class XMLElementDecl;

class VALIDATORS_EXPORT IdentityConstraintHandler: public XMemory
{
public:

    // -----------------------------------------------------------------------
    //  Constructors/Destructor
    // -----------------------------------------------------------------------
	virtual ~IdentityConstraintHandler();

    IdentityConstraintHandler
              (
               XMLScanner*   const scanner
             , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
              );

    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    inline  XMLSize_t    getMatcherCount() const;

	// -----------------------------------------------------------------------
    //  Setter methods
    // -----------------------------------------------------------------------

	// -----------------------------------------------------------------------
    //  Access methods
    // -----------------------------------------------------------------------
    inline  void         endDocument();

            void         deactivateContext
                             (
                                    SchemaElementDecl* const elem
                            , const XMLCh*             const content
                            , ValidationContext*       validationContext = 0
                            , DatatypeValidator*       actualValidator = 0);

            void         activateIdentityConstraint
                               (
                                     SchemaElementDecl* const     elem
                             ,       int                          elemDepth
                             , const unsigned int                 uriId
                             , const XMLCh*                 const elemPrefix
                             , const RefVectorOf<XMLAttr>&        attrList
                             , const XMLSize_t                    attrCount
                             , ValidationContext*                 validationContext = 0 );

            void         reset();

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    IdentityConstraintHandler(const IdentityConstraintHandler& other);
    IdentityConstraintHandler& operator= (const IdentityConstraintHandler& other);

    // -----------------------------------------------------------------------
    //  CleanUp methods
    // -----------------------------------------------------------------------
    void    cleanUp();

    // -----------------------------------------------------------------------
    //  Helper
    // -----------------------------------------------------------------------
    void    activateSelectorFor(
                                      IdentityConstraint* const ic
                              , const int                       initialDepth
                               ) ;

    // -----------------------------------------------------------------------
    //  Data members
    //
    //  fMatcherStack
    //      Stack of active XPath matchers for identity constraints. All
    //      active XPath matchers are notified of startElement, characters
    //      and endElement callbacks in order to perform their matches.
    //
    //  fValueStoreCache
    //      Cache of value stores for identity constraint fields.
    //
    //  fFieldActivator
    //      Activates fields within a certain scope when a selector matches
    //      its xpath.
    //
    // -----------------------------------------------------------------------
    XMLScanner*                 fScanner;
    MemoryManager*              fMemoryManager;

    XPathMatcherStack*          fMatcherStack;
    ValueStoreCache*            fValueStoreCache;
    FieldActivator*             fFieldActivator;

};


// ---------------------------------------------------------------------------
//  IdentityConstraintHandler: 
// ---------------------------------------------------------------------------

inline 
void  IdentityConstraintHandler::endDocument()
{
    fValueStoreCache->endDocument();
}

inline
XMLSize_t IdentityConstraintHandler::getMatcherCount() const
{
    return fMatcherStack->getMatcherCount();
}

XERCES_CPP_NAMESPACE_END

#endif

/**
  * End of file IdentityConstraintHandler.hpp
  */

