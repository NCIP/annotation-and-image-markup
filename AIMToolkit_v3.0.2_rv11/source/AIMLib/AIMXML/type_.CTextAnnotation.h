/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CTextAnnotation
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CTextAnnotation



namespace AIMXML
{

class CTextAnnotation : public TypeBase
{
public:
	AIMXML_EXPORT CTextAnnotation(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CTextAnnotation(CTextAnnotation const& init);
	void operator=(CTextAnnotation const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CTextAnnotation); }

	MemberAttribute<__int64,_altova_mi_altova_CTextAnnotation_altova_cagridId, 0, 0> cagridId;	// cagridId Cinteger

	MemberAttribute<string_type,_altova_mi_altova_CTextAnnotation_altova_font, 0, 0> font;	// font Cstring

	MemberAttribute<string_type,_altova_mi_altova_CTextAnnotation_altova_fontColor, 0, 0> fontColor;	// fontColor Cstring

	MemberAttribute<string_type,_altova_mi_altova_CTextAnnotation_altova_fontEffect, 0, 0> fontEffect;	// fontEffect Cstring

	MemberAttribute<string_type,_altova_mi_altova_CTextAnnotation_altova_fontSize, 0, 0> fontSize;	// fontSize Cstring

	MemberAttribute<string_type,_altova_mi_altova_CTextAnnotation_altova_fontStyle, 0, 0> fontStyle;	// fontStyle Cstring

	MemberAttribute<string_type,_altova_mi_altova_CTextAnnotation_altova_text, 0, 0> text;	// text Cstring

	MemberAttribute<string_type,_altova_mi_altova_CTextAnnotation_altova_textJustify, 0, 0> textJustify;	// textJustify Cstring

	MemberAttribute<string_type,_altova_mi_altova_CTextAnnotation_altova_fontOpacity, 0, 0> fontOpacity;	// fontOpacity Cstring
	MemberElement<CmultiPointType, _altova_mi_altova_CTextAnnotation_altova_multiPoint> multiPoint;
	struct multiPoint { typedef Iterator<CmultiPointType> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CTextAnnotation
