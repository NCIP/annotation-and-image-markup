/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XMLSchemaDescription.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XMLSCHEMADESCRIPTION_HPP)
#define XERCESC_INCLUDE_GUARD_XMLSCHEMADESCRIPTION_HPP

#include <xercesc/framework/XMLGrammarDescription.hpp>
#include <xercesc/util/RefArrayVectorOf.hpp>

XERCES_CPP_NAMESPACE_BEGIN

typedef const XMLCh* const LocationHint;

class XMLPARSER_EXPORT XMLSchemaDescription : public XMLGrammarDescription
{
public :
    // -----------------------------------------------------------------------
    /** @name Virtual destructor for derived classes */
    // -----------------------------------------------------------------------
    //@{
    /**
      * virtual destructor
      *
      */
    virtual ~XMLSchemaDescription();
    //@}

    // -----------------------------------------------------------------------
    /** @name Implementation of Grammar Description Interface */
    // -----------------------------------------------------------------------
    //@{     
    /**
      * getGrammarType
      *
      */
    virtual Grammar::GrammarType   getGrammarType() const
    {
        return Grammar::SchemaGrammarType;
    }
    //@}

    // -----------------------------------------------------------------------
    /** @name The SchemaDescription Interface */
    // -----------------------------------------------------------------------
    //@{

    enum ContextType 
         {
            CONTEXT_INCLUDE,
            CONTEXT_REDEFINE,
            CONTEXT_IMPORT,
            CONTEXT_PREPARSE,
            CONTEXT_INSTANCE,
            CONTEXT_ELEMENT,
            CONTEXT_ATTRIBUTE,
            CONTEXT_XSITYPE,
            CONTEXT_UNKNOWN
         };

    /**
      * getContextType
      *
      */	
    virtual ContextType                getContextType() const = 0;

    /**
      * getTargetNamespace
      *
      */	
    virtual const XMLCh*               getTargetNamespace() const = 0;

    /**
      * getLocationHints
      *
      */	
    virtual const RefArrayVectorOf<XMLCh>*   getLocationHints() const = 0;

    /**
      * getTriggeringComponent
      *
      */	
    virtual const QName*               getTriggeringComponent() const = 0;

    /**
      * getenclosingElementName
      *
      */	
    virtual const QName*               getEnclosingElementName() const = 0;

    /**
      * getAttributes
      *
      */	
    virtual const XMLAttDef*           getAttributes() const = 0;

    /**
      * setContextType
      *
      */	
    virtual void                       setContextType(ContextType) = 0;

    /**
      * setTargetNamespace
      *
      */	
    virtual void                       setTargetNamespace(const XMLCh* const) = 0;

    /**
      * setLocationHints
      *
      */	
    virtual void                       setLocationHints(const XMLCh* const) = 0;

    /**
      * setTriggeringComponent
      *
      */	
    virtual void                       setTriggeringComponent(QName* const) = 0;

    /**
      * getenclosingElementName
      *
      */	
    virtual void                       setEnclosingElementName(QName* const) = 0;

    /**
      * setAttributes
      *
      */	
    virtual void                       setAttributes(XMLAttDef* const) = 0;
    //@}	          
	          
    /***
     * Support for Serialization/De-serialization
     ***/
    DECL_XSERIALIZABLE(XMLSchemaDescription)

protected :
    // -----------------------------------------------------------------------
    /**  Hidden Constructors */
    // -----------------------------------------------------------------------
    //@{
    XMLSchemaDescription(MemoryManager* const memMgr = XMLPlatformUtils::fgMemoryManager);
    //@}

private :
    // -----------------------------------------------------------------------
    /** name  Unimplemented copy constructor and operator= */
    // -----------------------------------------------------------------------
    //@{
    XMLSchemaDescription(const XMLSchemaDescription& );
    XMLSchemaDescription& operator=(const XMLSchemaDescription& );
    //@}

};


XERCES_CPP_NAMESPACE_END

#endif
