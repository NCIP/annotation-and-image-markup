/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CTextAnnotationEntity
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CTextAnnotationEntity

#include "type_.CMarkupEntity.h"


namespace AIMXML
{

class CTextAnnotationEntity : public ::AIMXML::CMarkupEntity
{
public:
	AIMXML_EXPORT CTextAnnotationEntity(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CTextAnnotationEntity(CTextAnnotationEntity const& init);
	void operator=(CTextAnnotationEntity const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CTextAnnotationEntity); }
	MemberElement<iso::CST, _altova_mi_altova_CTextAnnotationEntity_altova_text> text;
	struct text { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CTextAnnotationEntity_altova_font> font;
	struct font { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CTextAnnotationEntity_altova_fontColor> fontColor;
	struct fontColor { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CTextAnnotationEntity_altova_fontEffect> fontEffect;
	struct fontEffect { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CTextAnnotationEntity_altova_fontSize> fontSize;
	struct fontSize { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CTextAnnotationEntity_altova_fontStyle> fontStyle;
	struct fontStyle { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CTextAnnotationEntity_altova_textJustify> textJustify;
	struct textJustify { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CTextAnnotationEntity_altova_fontOpacity> fontOpacity;
	struct fontOpacity { typedef Iterator<iso::CST> iterator; };
	MemberElement<CGeometricShapeEntity, _altova_mi_altova_CTextAnnotationEntity_altova_geometricShapeEntity> geometricShapeEntity;
	struct geometricShapeEntity { typedef Iterator<CGeometricShapeEntity> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CTextAnnotationEntity
