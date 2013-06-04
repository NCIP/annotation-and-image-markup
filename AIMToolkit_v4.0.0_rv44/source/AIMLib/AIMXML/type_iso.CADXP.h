/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CADXP
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CADXP



namespace AIMXML
{

namespace iso
{	

class CADXP : public TypeBase
{
public:
	AIMXML_EXPORT CADXP(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CADXP(CADXP const& init);
	void operator=(CADXP const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CADXP); }

	MemberAttribute<string_type,_altova_mi_iso_altova_CADXP_altova_value2, 0, 0> value2;	// value Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CADXP_altova_code, 0, 0> code;	// code Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CADXP_altova_codeSystem, 0, 0> codeSystem;	// codeSystem Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CADXP_altova_codeSystemVersion, 0, 0> codeSystemVersion;	// codeSystemVersion Cstring
	MemberAttribute<string_type,_altova_mi_iso_altova_CADXP_altova_type, 0, 28> type;	// type CAddressPartType
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CADXP
