/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CcolgroupType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CcolgroupType



namespace AIMXML
{

class CcolgroupType : public TypeBase
{
public:
	AIMXML_EXPORT CcolgroupType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CcolgroupType(CcolgroupType const& init);
	void operator=(CcolgroupType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CcolgroupType); }

	MemberAttribute<string_type,_altova_mi_altova_CcolgroupType_altova_ID, 0, 0> ID;	// ID CID

	MemberAttribute<string_type,_altova_mi_altova_CcolgroupType_altova_language, 0, 0> language;	// language CNMTOKEN

	MemberAttribute<string_type,_altova_mi_altova_CcolgroupType_altova_styleCode, 0, 0> styleCode;	// styleCode CNMTOKENS

	MemberAttribute<string_type,_altova_mi_altova_CcolgroupType_altova_span, 0, 0> span;	// span Cstring

	MemberAttribute<string_type,_altova_mi_altova_CcolgroupType_altova_width, 0, 0> width;	// width Cstring
	MemberAttribute<string_type,_altova_mi_altova_CcolgroupType_altova_align, 0, 5> align;	// align CalignType2

	MemberAttribute<string_type,_altova_mi_altova_CcolgroupType_altova_char2, 0, 0> char2;	// char Cstring

	MemberAttribute<string_type,_altova_mi_altova_CcolgroupType_altova_charoff, 0, 0> charoff;	// charoff Cstring
	MemberAttribute<string_type,_altova_mi_altova_CcolgroupType_altova_valign, 0, 4> valign;	// valign CvalignType2
	MemberElement<CcolType, _altova_mi_altova_CcolgroupType_altova_col> col;
	struct col { typedef Iterator<CcolType> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CcolgroupType
