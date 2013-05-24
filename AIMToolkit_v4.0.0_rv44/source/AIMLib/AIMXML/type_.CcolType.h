/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CcolType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CcolType



namespace AIMXML
{

class CcolType : public TypeBase
{
public:
	AIMXML_EXPORT CcolType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CcolType(CcolType const& init);
	void operator=(CcolType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CcolType); }

	MemberAttribute<string_type,_altova_mi_altova_CcolType_altova_ID, 0, 0> ID;	// ID CID

	MemberAttribute<string_type,_altova_mi_altova_CcolType_altova_language, 0, 0> language;	// language CNMTOKEN

	MemberAttribute<string_type,_altova_mi_altova_CcolType_altova_styleCode, 0, 0> styleCode;	// styleCode CNMTOKENS

	MemberAttribute<string_type,_altova_mi_altova_CcolType_altova_span, 0, 0> span;	// span Cstring

	MemberAttribute<string_type,_altova_mi_altova_CcolType_altova_width, 0, 0> width;	// width Cstring
	MemberAttribute<string_type,_altova_mi_altova_CcolType_altova_align, 0, 5> align;	// align CalignType

	MemberAttribute<string_type,_altova_mi_altova_CcolType_altova_char2, 0, 0> char2;	// char Cstring

	MemberAttribute<string_type,_altova_mi_altova_CcolType_altova_charoff, 0, 0> charoff;	// charoff Cstring
	MemberAttribute<string_type,_altova_mi_altova_CcolType_altova_valign, 0, 4> valign;	// valign CvalignType
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CcolType
