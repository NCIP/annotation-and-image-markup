/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

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
	MemberElement<iso::CST, _altova_mi_altova_CUser_altova_name> name;
	struct name { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CUser_altova_loginName> loginName;
	struct loginName { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CUser_altova_roleInTrial> roleInTrial;
	struct roleInTrial { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CINT, _altova_mi_altova_CUser_altova_numberWithinRoleOfClinicalTrial> numberWithinRoleOfClinicalTrial;
	struct numberWithinRoleOfClinicalTrial { typedef Iterator<iso::CINT> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CUser
