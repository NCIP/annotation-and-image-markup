/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CpersonType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CpersonType



namespace AIMXML
{

class CpersonType : public TypeBase
{
public:
	AIMXML_EXPORT CpersonType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CpersonType(CpersonType const& init);
	void operator=(CpersonType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CpersonType); }
	MemberElement<CPerson, _altova_mi_altova_CpersonType_altova_Person> Person;
	struct Person { typedef Iterator<CPerson> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CpersonType
