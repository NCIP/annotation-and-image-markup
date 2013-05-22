/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

//
//  This file is part of the internal implementation of the C++ XML DOM.
//  It should NOT be included or used directly by application programs.
//
//  Applications should include the file <xercesc/dom/DOM.hpp> for the entire
//  DOM API, or xercesc/dom/DOM*.hpp for individual DOM classes, where the class
//  name is substituded for the *.
//

#if !defined(XERCESC_INCLUDE_GUARD_DOMCONFIGURATIONIMPL_HPP)
#define XERCESC_INCLUDE_GUARD_DOMCONFIGURATIONIMPL_HPP

//------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------
#include <xercesc/dom/DOMConfiguration.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>
#include <xercesc/util/XMLString.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class DOMDocumentImpl;
class DOMStringListImpl;

class CDOM_EXPORT DOMConfigurationImpl : public DOMConfiguration
{
private:
    //unimplemented
    DOMConfigurationImpl(const DOMConfiguration &);
    DOMConfigurationImpl & operator = (const DOMConfiguration &);


public:

    //-----------------------------------------------------------------------------------
    //  Constructor
    //-----------------------------------------------------------------------------------
    DOMConfigurationImpl(MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);
    ~DOMConfigurationImpl();
    
    enum DOMConfigurationFeature {
        FEATURE_CANONICAL_FORM                = 0x0001,
        FEATURE_CDATA_SECTIONS                = 0x0002,
        FEATURE_COMMENTS                      = 0x0004,
        FEATURE_DATATYPE_NORMALIZATION        = 0x0008,
        FEATURE_DISCARD_DEFAULT_CONTENT       = 0x0010, 
        FEATURE_ENTITIES                      = 0x0020,  
        FEATURE_INFOSET                       = 0x0040, 
        FEATURE_NAMESPACES                    = 0x0080, 
        FEATURE_NAMESPACE_DECLARATIONS        = 0x0100, 
        FEATURE_NORMALIZE_CHARACTERS          = 0x0200, 
        FEATURE_SPLIT_CDATA_SECTIONS          = 0x0400, 
        FEATURE_VALIDATE                      = 0x0800, 
        FEATURE_VALIDATE_IF_SCHEMA            = 0x1000, 
        FEATURE_ELEMENT_CONTENT_WHITESPACE    = 0x2000
    };

    unsigned short featureValues;

    // -----------------------------------------------------------------------
    //  Setter methods
    // -----------------------------------------------------------------------

    virtual void setParameter(const XMLCh* name, const void* value);
    virtual void setParameter(const XMLCh* name, bool value);

    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    
    virtual const void* getParameter(const XMLCh* name) const;

                                        
    // -----------------------------------------------------------------------
    //  Query methods
    // -----------------------------------------------------------------------

    virtual bool canSetParameter(const XMLCh* name, const void* value) const;
    virtual bool canSetParameter(const XMLCh* name, bool value) const;

    virtual const DOMStringList* getParameterNames() const;

    // ---------------------------------------------------------------------------
    // Impl specific methods
    // ---------------------------------------------------------------------------
    
    /* specific get and set methods for non-boolean parameters
     * */

    DOMErrorHandler* getErrorHandler() const;

    const XMLCh* getSchemaType() const;

    const XMLCh* getSchemaLocation() const;

    void setErrorHandler(DOMErrorHandler *erHandler);

    void setSchemaType(const XMLCh* st);

    void setSchemaLocation(const XMLCh* sl);
    
    // The default values for the boolean parameters
    // from CANONICAL_FORM to ELEMENT_CONTENT_WHITESPACE
    // 10010110010110 = 0x2596
    static const unsigned short fDEFAULT_VALUES;
    

protected:
    // implements a simple map between the name and its enum value
    DOMConfigurationFeature getFeatureFlag(const XMLCh* name) const;

    // the error handler
    DOMErrorHandler* fErrorHandler;
    
    // the schema type
    const XMLCh* fSchemaType;
    
    // the schema location
    const XMLCh* fSchemaLocation;

    // the list of supported parameters
    DOMStringListImpl* fSupportedParameters;

    MemoryManager* fMemoryManager;
};

XERCES_CPP_NAMESPACE_END

#endif

/**
 * End of file DOMConfigurationImpl.hpp
 */
