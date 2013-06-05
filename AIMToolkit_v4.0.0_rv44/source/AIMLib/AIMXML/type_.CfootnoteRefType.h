/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CfootnoteRefType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CfootnoteRefType



namespace AIMXML
{

class CfootnoteRefType : public TypeBase
{
public:
	AIMXML_EXPORT CfootnoteRefType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CfootnoteRefType(CfootnoteRefType const& init);
	void operator=(CfootnoteRefType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CfootnoteRefType); }

	MemberAttribute<string_type,_altova_mi_altova_CfootnoteRefType_altova_ID, 0, 0> ID;	// ID CID

	MemberAttribute<string_type,_altova_mi_altova_CfootnoteRefType_altova_language, 0, 0> language;	// language CNMTOKEN

	MemberAttribute<string_type,_altova_mi_altova_CfootnoteRefType_altova_styleCode, 0, 0> styleCode;	// styleCode CNMTOKENS

	MemberAttribute<string_type,_altova_mi_altova_CfootnoteRefType_altova_IDREF, 0, 0> IDREF;	// IDREF CIDREF
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CfootnoteRefType
