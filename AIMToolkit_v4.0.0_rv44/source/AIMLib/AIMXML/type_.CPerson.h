/*
*  2007 – 2013 Copyright Northwestern University
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
	MemberElement<iso::CST, _altova_mi_altova_CPerson_altova_name> name;
	struct name { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CPerson_altova_id> id;
	struct id { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CTS, _altova_mi_altova_CPerson_altova_birthDate> birthDate;
	struct birthDate { typedef Iterator<iso::CTS> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CPerson_altova_sex> sex;
	struct sex { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CPerson_altova_ethnicGroup> ethnicGroup;
	struct ethnicGroup { typedef Iterator<iso::CST> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CPerson
