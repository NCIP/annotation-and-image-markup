/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CuserType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CuserType



namespace AIMXML
{

class CuserType : public TypeBase
{
public:
	AIMXML_EXPORT CuserType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CuserType(CuserType const& init);
	void operator=(CuserType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CuserType); }
	MemberElement<CUser, _altova_mi_altova_CuserType_altova_User> User;
	struct User { typedef Iterator<CUser> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CuserType
