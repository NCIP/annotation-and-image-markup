/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XSObject.hpp 674012 2008-07-04 11:18:21Z borisk $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XSOBJECT_HPP)
#define XERCESC_INCLUDE_GUARD_XSOBJECT_HPP

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/framework/psvi/XSConstants.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/**
 * The XSObject forms the base of the Schema Component Model.  It contains
 * all properties common to the majority of XML Schema components.
 * This is *always* owned by the validator /parser object from which
 * it is obtained.  It is designed to be subclassed; subclasses will
 * specify under what conditions it may be relied upon to have meaningful contents.
 */

// forward declarations
class XSNamespaceItem;
class XSModel;

class XMLPARSER_EXPORT XSObject : public XMemory
{
public:

    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    /** @name Constructors */
    //@{

    /**
      * The default constructor
      *
      * @param  compType
      * @param  xsModel
      * @param  manager     The configurable memory manager
      */
    XSObject
    (
        XSConstants::COMPONENT_TYPE compType
        , XSModel* const xsModel
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );

    //@};

    /** @name Destructor */
    //@{
    virtual ~XSObject();
    //@}

    //---------------------
    /** @name XSObject methods */

    //@{

    /**
     *  The <code>type</code> of this object, i.e.
     * <code>ELEMENT_DECLARATION</code>.
     */
    XSConstants::COMPONENT_TYPE getType() const;

    /**
     * The name of type <code>NCName</code> of this declaration as defined in
     * XML Namespaces.
     */
    virtual const XMLCh* getName() const;

    /**
     *  The [target namespace] of this object, or <code>null</code> if it is
     * unspecified.
     */
    virtual const XMLCh* getNamespace();

    /**
     * A namespace schema information item corresponding to the target
     * namespace of the component, if it's globally declared; or null
     * otherwise.
     */
    virtual XSNamespaceItem *getNamespaceItem();

    /**
      * Optional.  Return a unique identifier for a component within this XSModel, to
      * optimize querying.  May not be defined for all types of component.
      * @return id unique for this type of component within this XSModel or 0
      *     to indicate that this is not supported for this type of component.
      */
    virtual XMLSize_t getId() const;

    //@}

    //----------------------------------
    /** methods needed by implementation */

    //@{
    /**
      * Set the id to be returned on getId().
      */
    void setId(XMLSize_t id);
    //@}

private:

    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XSObject(const XSObject&);
    XSObject & operator=(const XSObject &);

protected:

    // -----------------------------------------------------------------------
    //  data members
    // -----------------------------------------------------------------------
    // fMemoryManager:
    //  used for any memory allocations
    // fComponentType
    //  the type of the actual component
    XSConstants::COMPONENT_TYPE fComponentType;
    XSModel*                    fXSModel;
    MemoryManager*              fMemoryManager;
    XMLSize_t                   fId;
};

inline XSConstants::COMPONENT_TYPE XSObject::getType() const
{
    return fComponentType;
}

XERCES_CPP_NAMESPACE_END

#endif
