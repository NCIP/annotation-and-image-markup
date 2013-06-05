/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CtableType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CtableType



namespace AIMXML
{

class CtableType : public TypeBase
{
public:
	AIMXML_EXPORT CtableType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CtableType(CtableType const& init);
	void operator=(CtableType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CtableType); }

	MemberAttribute<string_type,_altova_mi_altova_CtableType_altova_ID, 0, 0> ID;	// ID CID

	MemberAttribute<string_type,_altova_mi_altova_CtableType_altova_language, 0, 0> language;	// language CNMTOKEN

	MemberAttribute<string_type,_altova_mi_altova_CtableType_altova_styleCode, 0, 0> styleCode;	// styleCode CNMTOKENS

	MemberAttribute<string_type,_altova_mi_altova_CtableType_altova_summary, 0, 0> summary;	// summary Cstring

	MemberAttribute<string_type,_altova_mi_altova_CtableType_altova_width, 0, 0> width;	// width Cstring

	MemberAttribute<string_type,_altova_mi_altova_CtableType_altova_border, 0, 0> border;	// border Cstring
	MemberAttribute<string_type,_altova_mi_altova_CtableType_altova_frame, 0, 9> frame;	// frame CframeType
	MemberAttribute<string_type,_altova_mi_altova_CtableType_altova_rules, 0, 5> rules;	// rules CrulesType

	MemberAttribute<string_type,_altova_mi_altova_CtableType_altova_cellspacing, 0, 0> cellspacing;	// cellspacing Cstring

	MemberAttribute<string_type,_altova_mi_altova_CtableType_altova_cellpadding, 0, 0> cellpadding;	// cellpadding Cstring
	MemberElement<CcaptionType, _altova_mi_altova_CtableType_altova_caption> caption;
	struct caption { typedef Iterator<CcaptionType> iterator; };
	MemberElement<CcolType, _altova_mi_altova_CtableType_altova_col> col;
	struct col { typedef Iterator<CcolType> iterator; };
	MemberElement<CcolgroupType, _altova_mi_altova_CtableType_altova_colgroup> colgroup;
	struct colgroup { typedef Iterator<CcolgroupType> iterator; };
	MemberElement<CtheadType, _altova_mi_altova_CtableType_altova_thead> thead;
	struct thead { typedef Iterator<CtheadType> iterator; };
	MemberElement<CtfootType, _altova_mi_altova_CtableType_altova_tfoot> tfoot;
	struct tfoot { typedef Iterator<CtfootType> iterator; };
	MemberElement<CtbodyType, _altova_mi_altova_CtableType_altova_tbody> tbody;
	struct tbody { typedef Iterator<CtbodyType> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CtableType
