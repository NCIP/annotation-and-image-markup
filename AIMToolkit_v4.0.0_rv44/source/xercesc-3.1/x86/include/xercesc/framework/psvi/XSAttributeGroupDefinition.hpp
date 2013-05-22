/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XSAttributeGroupDefinition.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XSATTRIBUTEGROUPDEFINITION_HPP)
#define XERCESC_INCLUDE_GUARD_XSATTRIBUTEGROUPDEFINITION_HPP

#include <xercesc/framework/psvi/XSObject.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/**
 * This class describes all properties of a Schema Attribute
 * Group Definition component.
 * This is *always* owned by the validator /parser object from which
 * it is obtained.  
 */

// forward declarations
class XSAnnotation;
class XSAttributeUse;
class XSWildcard;
class XercesAttGroupInfo;

class XMLPARSER_EXPORT XSAttributeGroupDefinition : public XSObject
{
public:

    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    /** @name Constructors */
    //@{

    /**
      * The default constructor 
      *
      * @param  xercesAttGroupInfo
      * @param  xsAttList
      * @param  xsWildcard
      * @param  xsAnnot
      * @param  xsModel
      * @param  manager     The configurable memory manager
      */
    XSAttributeGroupDefinition
    (
        XercesAttGroupInfo* const   xercesAttGroupInfo
        , XSAttributeUseList* const xsAttList
        , XSWildcard* const         xsWildcard
        , XSAnnotation* const       xsAnnot
        , XSModel* const            xsModel
        , MemoryManager* const      manager = XMLPlatformUtils::fgMemoryManager
    );

    //@};

    /** @name Destructor */
    //@{
    ~XSAttributeGroupDefinition();
    //@}

    //---------------------
    /** @name overridden XSObject methods */
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
    XSNamespaceItem* getNamespaceItem();

    //@}

    //--------------------- 
    /** @name XSAttributeGroupDefinition methods */

    //@{

    /**
     * A set of [attribute uses]. 
     */
    XSAttributeUseList *getAttributeUses();

    /**
     * Optional. A [wildcard]. 
     */
    XSWildcard *getAttributeWildcard() const;

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
    XSAttributeGroupDefinition(const XSAttributeGroupDefinition&);
    XSAttributeGroupDefinition & operator=(const XSAttributeGroupDefinition &);

protected:

    // -----------------------------------------------------------------------
    //  data members
    // -----------------------------------------------------------------------
    XercesAttGroupInfo*     fXercesAttGroupInfo;
    XSAttributeUseList*     fXSAttributeUseList;
    XSWildcard*             fXSWildcard;
    XSAnnotation*           fAnnotation;
};

inline XSAttributeUseList* XSAttributeGroupDefinition::getAttributeUses()
{
    return fXSAttributeUseList;
}

inline XSWildcard* XSAttributeGroupDefinition::getAttributeWildcard() const
{
    return fXSWildcard;
}

inline XSAnnotation* XSAttributeGroupDefinition::getAnnotation() const
{
    return fAnnotation;
}

XERCES_CPP_NAMESPACE_END

#endif
