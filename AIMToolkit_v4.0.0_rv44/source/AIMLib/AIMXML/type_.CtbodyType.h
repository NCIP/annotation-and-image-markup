/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CtbodyType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CtbodyType



namespace AIMXML
{

class CtbodyType : public TypeBase
{
public:
	AIMXML_EXPORT CtbodyType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CtbodyType(CtbodyType const& init);
	void operator=(CtbodyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CtbodyType); }

	MemberAttribute<string_type,_altova_mi_altova_CtbodyType_altova_ID, 0, 0> ID;	// ID CID

	MemberAttribute<string_type,_altova_mi_altova_CtbodyType_altova_language, 0, 0> language;	// language CNMTOKEN

	MemberAttribute<string_type,_altova_mi_altova_CtbodyType_altova_styleCode, 0, 0> styleCode;	// styleCode CNMTOKENS
	MemberAttribute<string_type,_altova_mi_altova_CtbodyType_altova_align, 0, 5> align;	// align CalignType3

	MemberAttribute<string_type,_altova_mi_altova_CtbodyType_altova_char2, 0, 0> char2;	// char Cstring

	MemberAttribute<string_type,_altova_mi_altova_CtbodyType_altova_charoff, 0, 0> charoff;	// charoff Cstring
	MemberAttribute<string_type,_altova_mi_altova_CtbodyType_altova_valign, 0, 4> valign;	// valign CvalignType3
	MemberElement<CtrType, _altova_mi_altova_CtbodyType_altova_tr> tr;
	struct tr { typedef Iterator<CtrType> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CtbodyType
