/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CENXP
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CENXP



namespace AIMXML
{

namespace iso
{	

class CENXP : public TypeBase
{
public:
	AIMXML_EXPORT CENXP(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CENXP(CENXP const& init);
	void operator=(CENXP const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CENXP); }

	MemberAttribute<string_type,_altova_mi_iso_altova_CENXP_altova_value2, 0, 0> value2;	// value Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CENXP_altova_code, 0, 0> code;	// code Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CENXP_altova_codeSystem, 0, 0> codeSystem;	// codeSystem Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CENXP_altova_codeSystemVersion, 0, 0> codeSystemVersion;	// codeSystemVersion Cstring
	MemberAttribute<string_type,_altova_mi_iso_altova_CENXP_altova_type, 0, 5> type;	// type CEntityNamePartType
	MemberAttribute<string_type,_altova_mi_iso_altova_CENXP_altova_qualifier, 1, 11> qualifier;	// qualifier Cset_EntityNamePartQualifier
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CENXP
