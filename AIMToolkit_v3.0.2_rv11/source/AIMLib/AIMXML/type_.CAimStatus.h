/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAimStatus
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAimStatus



namespace AIMXML
{

class CAimStatus : public TypeBase
{
public:
	AIMXML_EXPORT CAimStatus(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CAimStatus(CAimStatus const& init);
	void operator=(CAimStatus const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CAimStatus); }

	MemberAttribute<__int64,_altova_mi_altova_CAimStatus_altova_cagridId, 0, 0> cagridId;	// cagridId Cinteger

	MemberAttribute<double,_altova_mi_altova_CAimStatus_altova_annotationVersion, 0, 0> annotationVersion;	// annotationVersion Cdouble

	MemberAttribute<string_type,_altova_mi_altova_CAimStatus_altova_codeValue, 0, 0> codeValue;	// codeValue Cstring

	MemberAttribute<string_type,_altova_mi_altova_CAimStatus_altova_codeMeaning, 0, 0> codeMeaning;	// codeMeaning Cstring

	MemberAttribute<string_type,_altova_mi_altova_CAimStatus_altova_codingSchemeDesignator, 0, 0> codingSchemeDesignator;	// codingSchemeDesignator Cstring

	MemberAttribute<string_type,_altova_mi_altova_CAimStatus_altova_codingSchemeVersion, 0, 0> codingSchemeVersion;	// codingSchemeVersion Cstring

	MemberAttribute<string_type,_altova_mi_altova_CAimStatus_altova_authorizedBy, 0, 0> authorizedBy;	// authorizedBy Cstring
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAimStatus
