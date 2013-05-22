/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XSNotationDeclaration.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XSNOTATIONDECLARATION_HPP)
#define XERCESC_INCLUDE_GUARD_XSNOTATIONDECLARATION_HPP

#include <xercesc/framework/psvi/XSObject.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/**
 * This class describes all properties of a Schema Notation Declaration
 * component.
 * This is *always* owned by the validator /parser object from which
 * it is obtained.  
 */

// forward declarations
class XSAnnotation;
class XMLNotationDecl;

class XMLPARSER_EXPORT XSNotationDeclaration : public XSObject
{
public:

    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    /** @name Constructors */
    //@{

    /**
      * The default constructor 
      *
      * @param  xmlNotationDecl
      * @param  annot
      * @param  xsModel
      * @param  manager     The configurable memory manager
      */
    XSNotationDeclaration
    (
        XMLNotationDecl*  const xmlNotationDecl
        , XSAnnotation* const   annot
        , XSModel* const        xsModel
        , MemoryManager* const  manager = XMLPlatformUtils::fgMemoryManager
    );

    //@};

    /** @name Destructor */
    //@{
    ~XSNotationDeclaration();
    //@}

    //---------------------
    /** @name overridden XSXSObject methods */

    //@{

    /**
     * The name of type <code>NCName</code> of this declaration as defined in 
     * XML Namespaces.
     */
    const XMLCh* getName() const;

    /**
     *  The [target namespace] of this object, or <code>null</code> if it is 
     * unspecified. 
     */
    const XMLCh* getNamespace();

    /**
     * A namespace schema information item corresponding to the target 
     * namespace of the component, if it's globally declared; or null 
     * otherwise.
     */
    XSNamespaceItem *getNamespaceItem();

    //@}

    //---------------------
    /** @name XSNotationDeclaration methods */

    //@{

    /**
     *  The URI reference representing the system identifier for the notation 
     * declaration, if present, <code>null</code> otherwise. 
     */
    const XMLCh *getSystemId();

    /**
     *  The string representing the public identifier for this notation 
     * declaration, if present; <code>null</code> otherwise. 
     */
    const XMLCh *getPublicId();

    /**
     * Optional. An [annotation]. 
     */
    XSAnnotation *getAnnotation() const;

    //@}

    //----------------------------------
    /** methods needed by implementation */

    //@{

    //@}
private:

    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XSNotationDeclaration(const XSNotationDeclaration&);
    XSNotationDeclaration & operator=(const XSNotationDeclaration &);

protected:

    // -----------------------------------------------------------------------
    //  data members
    // -----------------------------------------------------------------------
    XMLNotationDecl* fXMLNotationDecl;
    XSAnnotation*    fAnnotation;
};

inline XSAnnotation* XSNotationDeclaration::getAnnotation() const
{
    return fAnnotation;
}



XERCES_CPP_NAMESPACE_END

#endif
