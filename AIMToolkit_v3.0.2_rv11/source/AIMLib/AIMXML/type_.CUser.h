/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CUser
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CUser



namespace AIMXML
{

class CUser : public TypeBase
{
public:
	AIMXML_EXPORT CUser(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CUser(CUser const& init);
	void operator=(CUser const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CUser); }

	MemberAttribute<__int64,_altova_mi_altova_CUser_altova_cagridId, 0, 0> cagridId;	// cagridId Cinteger

	MemberAttribute<string_type,_altova_mi_altova_CUser_altova_name, 0, 0> name;	// name Cstring

	MemberAttribute<string_type,_altova_mi_altova_CUser_altova_loginName, 0, 0> loginName;	// loginName Cstring

	MemberAttribute<string_type,_altova_mi_altova_CUser_altova_roleInTrial, 0, 0> roleInTrial;	// roleInTrial Cstring

	MemberAttribute<__int64,_altova_mi_altova_CUser_altova_numberWithinRoleOfClinicalTrial, 0, 0> numberWithinRoleOfClinicalTrial;	// numberWithinRoleOfClinicalTrial Cinteger
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CUser
