/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

/*
 * $Id: XSAttributeUse.hpp 527149 2007-04-10 14:56:39Z amassari $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XSATTRIBUTEUSE_HPP)
#define XERCESC_INCLUDE_GUARD_XSATTRIBUTEUSE_HPP

#include <xercesc/framework/psvi/XSObject.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/**
 * This class describes all properties of a Schema Attribute
 * Use component.
 * This is *always* owned by the validator /parser object from which
 * it is obtained.  
 */

// forward declarations
class XSAttributeDeclaration;

class XMLPARSER_EXPORT XSAttributeUse : public XSObject
{
public:

    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    /** @name Constructors */
    //@{

    /**
      * The default constructor 
      * @param  xsAttDecl
      * @param  xsModel
      * @param  manager     The configurable memory manager
      */
    XSAttributeUse
    (
        XSAttributeDeclaration* const xsAttDecl,
        XSModel* const xsModel,
        MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );

    //@};

    /** @name Destructor */
    //@{
    ~XSAttributeUse();
    //@}

    //---------------------
    /** @name XSAttributeUse methods */

    //@{

    /**
     * [required]: determines whether this use of an attribute declaration 
     * requires an appropriate attribute information item to be present, or 
     * merely allows it. 
     */
    bool getRequired() const;

    /**
     * [attribute declaration]: provides the attribute declaration itself, 
     * which will in turn determine the simple type definition used. 
     */
    XSAttributeDeclaration *getAttrDeclaration() const;

    /**
     * Value Constraint: one of default, fixed. 
     */
    XSConstants::VALUE_CONSTRAINT getConstraintType() const;

    /**
     * Value Constraint: The actual value. 
     */
    const XMLCh *getConstraintValue();

    //@}

    //----------------------------------
    /** methods needed by implementation */

    //@{

    //@}

private:

    // set data
    void set
    (
        const bool isRequired
        , XSConstants::VALUE_CONSTRAINT constraintType
        , const XMLCh* const constraintValue
    );

    friend class XSObjectFactory;
    
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XSAttributeUse(const XSAttributeUse&);
    XSAttributeUse & operator=(const XSAttributeUse &);

protected:

    // -----------------------------------------------------------------------
    //  data members
    // -----------------------------------------------------------------------
    bool                          fRequired;
    XSConstants::VALUE_CONSTRAINT fConstraintType;   
    const XMLCh*                  fConstraintValue;
    XSAttributeDeclaration*       fXSAttributeDeclaration;
};

inline XSAttributeDeclaration *XSAttributeUse::getAttrDeclaration() const
{
    return fXSAttributeDeclaration;
}

inline bool XSAttributeUse::getRequired() const
{
    return fRequired;
}

inline XSConstants::VALUE_CONSTRAINT XSAttributeUse::getConstraintType() const
{
    return fConstraintType;
}

inline const XMLCh *XSAttributeUse::getConstraintValue()
{
    return fConstraintValue;
}

XERCES_CPP_NAMESPACE_END

#endif
