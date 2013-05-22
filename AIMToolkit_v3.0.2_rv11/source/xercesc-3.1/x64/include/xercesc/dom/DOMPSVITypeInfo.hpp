/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#if !defined(XERCESC_INCLUDE_GUARD_DOMPSVITYPEINFO_HPP)
#define XERCESC_INCLUDE_GUARD_DOMPSVITYPEINFO_HPP

//------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------
#include <xercesc/util/XMLString.hpp>


XERCES_CPP_NAMESPACE_BEGIN

/**
  * The <code>DOMPSVITypeInfo</code> interface represent the PSVI info used by 
  * <code>DOMElement</code> or <code>DOMAttr</code> nodes, specified in the 
  * schemas associated with the document. 
  */
class CDOM_EXPORT DOMPSVITypeInfo
{
protected:
    // -----------------------------------------------------------------------
    //  Hidden constructors
    // -----------------------------------------------------------------------
    /** @name Hidden constructors */
    //@{
    DOMPSVITypeInfo() {};
    //@}

private:
    // -----------------------------------------------------------------------
    // Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    /** @name Unimplemented constructors and operators */
    //@{
    DOMPSVITypeInfo(const DOMPSVITypeInfo &);
    DOMPSVITypeInfo & operator = (const DOMPSVITypeInfo &);
    //@}

public:

    enum PSVIProperty
    {
        PSVI_Validity
        , PSVI_Validation_Attempted
        , PSVI_Type_Definition_Type
        , PSVI_Type_Definition_Name
        , PSVI_Type_Definition_Namespace
        , PSVI_Type_Definition_Anonymous
        , PSVI_Nil
        , PSVI_Member_Type_Definition_Name
        , PSVI_Member_Type_Definition_Namespace
        , PSVI_Member_Type_Definition_Anonymous
        , PSVI_Schema_Default
        , PSVI_Schema_Normalized_Value
        , PSVI_Schema_Specified
    };

    // -----------------------------------------------------------------------
    //  All constructors are hidden, just the destructor is available
    // -----------------------------------------------------------------------
    /** @name Destructor */
    //@{
    /**
     * Destructor
     *
     */
    virtual ~DOMPSVITypeInfo() {};
    //@}

    //@{
    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    /**
     * Returns the string value of the specified PSVI property associated to a 
     * <code>DOMElement</code> or <code>DOMAttr</code>, or null if not available.
     *
     *
     * @return the string value of the specified PSVI property associated to a 
     * <code>DOMElement</code> or <code>DOMAttr</code>, or null if not available.
     */
    virtual const XMLCh* getStringProperty(PSVIProperty prop) const = 0;

    /**
     * Returns the numeric value of the specified PSVI property associated to a 
     * <code>DOMElement</code> or <code>DOMAttr</code>, or null if not available.
     *
     *
     * @return the numeric value of the specified PSVI property associated to a 
     * <code>DOMElement</code> or <code>DOMAttr</code>, or null if not available.
     */
    virtual int getNumericProperty(PSVIProperty prop) const = 0;
    //@}
};

XERCES_CPP_NAMESPACE_END

#endif

/**
 * End of file DOMPSVITypeInfo.hpp
 */
