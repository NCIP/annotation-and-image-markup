/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CtdType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CtdType



namespace AIMXML
{

class CtdType : public TypeBase
{
public:
	AIMXML_EXPORT CtdType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CtdType(CtdType const& init);
	void operator=(CtdType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CtdType); }
	AIMXML_EXPORT void operator=(const string_type& value);
	AIMXML_EXPORT operator string_type();

	MemberAttribute<string_type,_altova_mi_altova_CtdType_altova_ID, 0, 0> ID;	// ID CID

	MemberAttribute<string_type,_altova_mi_altova_CtdType_altova_language, 0, 0> language;	// language CNMTOKEN

	MemberAttribute<string_type,_altova_mi_altova_CtdType_altova_styleCode, 0, 0> styleCode;	// styleCode CNMTOKENS

	MemberAttribute<string_type,_altova_mi_altova_CtdType_altova_abbr, 0, 0> abbr;	// abbr Cstring

	MemberAttribute<string_type,_altova_mi_altova_CtdType_altova_axis, 0, 0> axis;	// axis Cstring

	MemberAttribute<string_type,_altova_mi_altova_CtdType_altova_headers, 0, 0> headers;	// headers CIDREFS
	MemberAttribute<string_type,_altova_mi_altova_CtdType_altova_scope, 0, 4> scope;	// scope CscopeType

	MemberAttribute<string_type,_altova_mi_altova_CtdType_altova_rowspan, 0, 0> rowspan;	// rowspan Cstring

	MemberAttribute<string_type,_altova_mi_altova_CtdType_altova_colspan, 0, 0> colspan;	// colspan Cstring
	MemberAttribute<string_type,_altova_mi_altova_CtdType_altova_align, 0, 5> align;	// align CalignType4

	MemberAttribute<string_type,_altova_mi_altova_CtdType_altova_char2, 0, 0> char2;	// char Cstring

	MemberAttribute<string_type,_altova_mi_altova_CtdType_altova_charoff, 0, 0> charoff;	// charoff Cstring
	MemberAttribute<string_type,_altova_mi_altova_CtdType_altova_valign, 0, 4> valign;	// valign CvalignType4
	MemberElement<CcontentType, _altova_mi_altova_CtdType_altova_content> content;
	struct content { typedef Iterator<CcontentType> iterator; };
	MemberElement<ClinkHtmlType, _altova_mi_altova_CtdType_altova_linkHtml> linkHtml;
	struct linkHtml { typedef Iterator<ClinkHtmlType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CtdType_altova_sub> sub;
	struct sub { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_altova_CtdType_altova_sup> sup;
	struct sup { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<CbrType, _altova_mi_altova_CtdType_altova_br> br;
	struct br { typedef Iterator<CbrType> iterator; };
	MemberElement<CfootnoteType, _altova_mi_altova_CtdType_altova_footnote> footnote;
	struct footnote { typedef Iterator<CfootnoteType> iterator; };
	MemberElement<CfootnoteRefType, _altova_mi_altova_CtdType_altova_footnoteRef> footnoteRef;
	struct footnoteRef { typedef Iterator<CfootnoteRefType> iterator; };
	MemberElement<CrenderMultiMediaType, _altova_mi_altova_CtdType_altova_renderMultiMedia> renderMultiMedia;
	struct renderMultiMedia { typedef Iterator<CrenderMultiMediaType> iterator; };
	MemberElement<CparagraphType, _altova_mi_altova_CtdType_altova_paragraph> paragraph;
	struct paragraph { typedef Iterator<CparagraphType> iterator; };
	MemberElement<ClistType, _altova_mi_altova_CtdType_altova_list> list;
	struct list { typedef Iterator<ClistType> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CtdType
