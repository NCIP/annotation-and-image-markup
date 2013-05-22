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


#if !defined(XERCESC_INCLUDE_GUARD_DOMTYPEINFOIMPL_HPP)
#define XERCESC_INCLUDE_GUARD_DOMTYPEINFOIMPL_HPP

//------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------
#include <xercesc/dom/DOMTypeInfo.hpp>
#include <xercesc/dom/DOMPSVITypeInfo.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class DOMDocumentImpl;

class CDOM_EXPORT DOMTypeInfoImpl : public DOMTypeInfo, public DOMPSVITypeInfo
{
public:

    //-----------------------------------------------------------------------------------
    //  Constructor
    //-----------------------------------------------------------------------------------
    DOMTypeInfoImpl(const XMLCh* namespaceUri=0, const XMLCh* name=0);
    DOMTypeInfoImpl(DOMDocumentImpl* ownerDoc, const DOMPSVITypeInfo* sourcePSVI);

    static DOMTypeInfoImpl  g_DtdValidatedElement;
    static DOMTypeInfoImpl  g_DtdNotValidatedAttribute;
    static DOMTypeInfoImpl  g_DtdValidatedCDATAAttribute;
    static DOMTypeInfoImpl  g_DtdValidatedIDAttribute;
    static DOMTypeInfoImpl  g_DtdValidatedIDREFAttribute;
    static DOMTypeInfoImpl  g_DtdValidatedIDREFSAttribute;
    static DOMTypeInfoImpl  g_DtdValidatedENTITYAttribute;
    static DOMTypeInfoImpl  g_DtdValidatedENTITIESAttribute;
    static DOMTypeInfoImpl  g_DtdValidatedNMTOKENAttribute;
    static DOMTypeInfoImpl  g_DtdValidatedNMTOKENSAttribute;
    static DOMTypeInfoImpl  g_DtdValidatedNOTATIONAttribute;
    static DOMTypeInfoImpl  g_DtdValidatedENUMERATIONAttribute;

    // -----------------------------------------------------------------------
    //  DOMTypeInfo interface
    // -----------------------------------------------------------------------
    virtual const XMLCh* getTypeName() const;
    virtual const XMLCh* getTypeNamespace() const;
    virtual bool isDerivedFrom(const XMLCh* typeNamespaceArg, const XMLCh* typeNameArg, DerivationMethods derivationMethod) const;

    // -----------------------------------------------------------------------
    //  DOMPSVITypeInfo interface
    // -----------------------------------------------------------------------
    virtual const XMLCh* getStringProperty(PSVIProperty prop) const;
    virtual int getNumericProperty(PSVIProperty prop) const;

    // -----------------------------------------------------------------------
    //  Setter methods
    // -----------------------------------------------------------------------
    virtual void setStringProperty(PSVIProperty prop, const XMLCh* value);
    virtual void setNumericProperty(PSVIProperty prop, int value);

protected:
    int             fBitFields;
    const XMLCh*    fTypeName;
    const XMLCh*    fTypeNamespace;
    const XMLCh*    fMemberTypeName;
    const XMLCh*    fMemberTypeNamespace;
    const XMLCh*    fDefaultValue;
    const XMLCh*    fNormalizedValue;

private:
    // -----------------------------------------------------------------------
    // Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    DOMTypeInfoImpl (const DOMTypeInfoImpl&);
    DOMTypeInfoImpl & operator = (const DOMTypeInfoImpl &);
};

XERCES_CPP_NAMESPACE_END

#endif

/**
 * End of file DOMTypeInfo.hpp
 */
