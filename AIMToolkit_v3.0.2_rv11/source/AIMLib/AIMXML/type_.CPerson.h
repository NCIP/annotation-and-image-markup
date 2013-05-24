/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CPerson
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CPerson



namespace AIMXML
{

class CPerson : public TypeBase
{
public:
	AIMXML_EXPORT CPerson(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CPerson(CPerson const& init);
	void operator=(CPerson const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CPerson); }

	MemberAttribute<__int64,_altova_mi_altova_CPerson_altova_cagridId, 0, 0> cagridId;	// cagridId Cinteger

	MemberAttribute<string_type,_altova_mi_altova_CPerson_altova_name, 0, 0> name;	// name Cstring

	MemberAttribute<string_type,_altova_mi_altova_CPerson_altova_id, 0, 0> id;	// id Cstring

	MemberAttribute<altova::DateTime,_altova_mi_altova_CPerson_altova_birthDate, 0, 0> birthDate;	// birthDate CdateTime

	MemberAttribute<string_type,_altova_mi_altova_CPerson_altova_sex, 0, 0> sex;	// sex Cstring

	MemberAttribute<string_type,_altova_mi_altova_CPerson_altova_ethnicGroup, 0, 0> ethnicGroup;	// ethnicGroup Cstring
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CPerson
