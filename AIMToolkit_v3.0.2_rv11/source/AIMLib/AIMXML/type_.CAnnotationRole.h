/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAnnotationRole
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAnnotationRole



namespace AIMXML
{

class CAnnotationRole : public TypeBase
{
public:
	AIMXML_EXPORT CAnnotationRole(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CAnnotationRole(CAnnotationRole const& init);
	void operator=(CAnnotationRole const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CAnnotationRole); }

	MemberAttribute<__int64,_altova_mi_altova_CAnnotationRole_altova_cagridId, 0, 0> cagridId;	// cagridId Cinteger

	MemberAttribute<string_type,_altova_mi_altova_CAnnotationRole_altova_codeValue, 0, 0> codeValue;	// codeValue Cstring

	MemberAttribute<string_type,_altova_mi_altova_CAnnotationRole_altova_codeMeaning, 0, 0> codeMeaning;	// codeMeaning Cstring

	MemberAttribute<string_type,_altova_mi_altova_CAnnotationRole_altova_codingSchemeDesignator, 0, 0> codingSchemeDesignator;	// codingSchemeDesignator Cstring

	MemberAttribute<string_type,_altova_mi_altova_CAnnotationRole_altova_codingSchemeVersion, 0, 0> codingSchemeVersion;	// codingSchemeVersion Cstring

	MemberAttribute<__int64,_altova_mi_altova_CAnnotationRole_altova_roleSequenceNumber, 0, 0> roleSequenceNumber;	// roleSequenceNumber Cinteger
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAnnotationRole
