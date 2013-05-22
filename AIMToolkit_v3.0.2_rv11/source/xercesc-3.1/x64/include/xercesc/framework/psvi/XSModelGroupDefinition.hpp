/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XSModelGroupDefinition.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XSMODELGROUPDEFINITION_HPP)
#define XERCESC_INCLUDE_GUARD_XSMODELGROUPDEFINITION_HPP

#include <xercesc/framework/psvi/XSObject.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/**
 * This class describes all properties of a Schema Model Group
 * Definition component.
 * This is *always* owned by the validator /parser object from which
 * it is obtained.  
 */

// forward declarations
class XSAnnotation;
class XSModelGroup;
class XSParticle;
class XercesGroupInfo;

class XMLPARSER_EXPORT XSModelGroupDefinition : public XSObject
{
public:

    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    /** @name Constructors */
    //@{

    /**
      * The default constructor 
      *
      * @param  groupInfo
      * @param  groupParticle
      * @param  annot
      * @param  xsModel
      * @param  manager     The configurable memory manager
      */
    XSModelGroupDefinition
    (
        XercesGroupInfo* const groupInfo
        , XSParticle* const    groupParticle
        , XSAnnotation* const  annot
        , XSModel* const       xsModel
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );

    //@};

    /** @name Destructor */
    //@{
    ~XSModelGroupDefinition();
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
    /** @name XSModelGroupDefinition methods */

    //@{

    /**
     * A model group. 
     */
    XSModelGroup *getModelGroup();

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
    XSModelGroupDefinition(const XSModelGroupDefinition&);
    XSModelGroupDefinition & operator=(const XSModelGroupDefinition &);

protected:

    // -----------------------------------------------------------------------
    //  data members
    // -----------------------------------------------------------------------
    XercesGroupInfo* fGroupInfo;
    XSParticle*      fModelGroupParticle;
    XSAnnotation*    fAnnotation;
};

inline XSAnnotation* XSModelGroupDefinition::getAnnotation() const
{
    return fAnnotation;
}



XERCES_CPP_NAMESPACE_END

#endif
