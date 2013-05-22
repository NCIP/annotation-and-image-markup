/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XMLSchemaDescriptionImpl.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XMLSCHEMADESCRIPTIONIMPL_HPP)
#define XERCESC_INCLUDE_GUARD_XMLSCHEMADESCRIPTIONIMPL_HPP

#include <xercesc/framework/XMLSchemaDescription.hpp>
#include <xercesc/util/RefVectorOf.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLAttDefs;

class XMLPARSER_EXPORT XMLSchemaDescriptionImpl : public XMLSchemaDescription
{
public :
    // -----------------------------------------------------------------------
    /** @name constructor and destructor */
    // -----------------------------------------------------------------------
    //@{
    XMLSchemaDescriptionImpl(
                             const XMLCh* const   targetNamespace 
                           , MemoryManager* const memMgr
                             );

    ~XMLSchemaDescriptionImpl();
    //@}

    // -----------------------------------------------------------------------
    /** @name Implementation of GrammarDescription Interface */
    // -----------------------------------------------------------------------
    //@{
    /**
      * getGrammarKey
      *
      */
    virtual const XMLCh*           getGrammarKey() const;
    //@}

    // -----------------------------------------------------------------------
    /** @name Implementation of SchemaDescription Interface */
    // -----------------------------------------------------------------------
    //@{

    /**
      * getContextType
      *
      */	
    virtual ContextType            getContextType() const;

    /**
      * getTargetNamespace
      *
      */	
    virtual const XMLCh*           getTargetNamespace() const;

    /**
      * getLocationHints
      *
      */	
    virtual const RefArrayVectorOf<XMLCh>*   getLocationHints() const;

    /**
      * getTriggeringComponent
      *
      */	
    virtual const QName*           getTriggeringComponent() const;

    /**
      * getenclosingElementName
      *
      */	
    virtual const QName*           getEnclosingElementName() const;

    /**
      * getAttributes
      *
      */	
    virtual const XMLAttDef*       getAttributes() const;

    /**
      * setContextType
      *
      */	
    virtual void                   setContextType(ContextType);

    /**
      * setTargetNamespace
      *
      */	
    virtual void                   setTargetNamespace(const XMLCh* const);

    /**
      * setLocationHints
      *
      */	
    virtual void                   setLocationHints(const XMLCh* const);

    /**
      * setTriggeringComponent
      *
      */	
    virtual void                   setTriggeringComponent(QName* const);

    /**
      * getenclosingElementName
      *
      */	
    virtual void                   setEnclosingElementName(QName* const);

    /**
      * setAttributes
      *
      */	
    virtual void                   setAttributes(XMLAttDef* const);          
    //@}

    /***
     * Support for Serialization/De-serialization
     ***/
    DECL_XSERIALIZABLE(XMLSchemaDescriptionImpl)

    XMLSchemaDescriptionImpl(MemoryManager* const memMgr = XMLPlatformUtils::fgMemoryManager);

private :
    // -----------------------------------------------------------------------
    /** name  Unimplemented copy constructor and operator= */
    // -----------------------------------------------------------------------
    //@{
    XMLSchemaDescriptionImpl(const XMLSchemaDescriptionImpl& );
    XMLSchemaDescriptionImpl& operator=(const XMLSchemaDescriptionImpl& );
    //@}

    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  All data member in this implementation are owned to out survive
    //  parser. Except for fNamespace which is replicated upon set, the
    //  rest shall be created by the embedded memoryManager.
    //
    //  fContextType  
    //
    //  fNamespace            owned
    //
    //  fLocationHints        owned
    //
    //  fTriggeringComponent  owned
    //
    //  fEnclosingElementName owned
    //                       
    //  fAttributes           referenced
    //
    // -----------------------------------------------------------------------

    XMLSchemaDescription::ContextType      fContextType;
    const XMLCh*                           fNamespace;
    RefArrayVectorOf<XMLCh>*               fLocationHints;
    const QName*                           fTriggeringComponent;
    const QName*                           fEnclosingElementName;
    const XMLAttDef*                       fAttributes; 

};


XERCES_CPP_NAMESPACE_END

#endif
