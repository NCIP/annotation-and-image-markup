/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CGeometricShapeEntity
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CGeometricShapeEntity

#include "type_.CMarkupEntity.h"


namespace AIMXML
{

class CGeometricShapeEntity : public ::AIMXML::CMarkupEntity
{
public:
	AIMXML_EXPORT CGeometricShapeEntity(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CGeometricShapeEntity(CGeometricShapeEntity const& init);
	void operator=(CGeometricShapeEntity const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CGeometricShapeEntity); }
	MemberElement<iso::CCD, _altova_mi_altova_CGeometricShapeEntity_altova_questionTypeCode> questionTypeCode;
	struct questionTypeCode { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CINT, _altova_mi_altova_CGeometricShapeEntity_altova_shapeIdentifier> shapeIdentifier;
	struct shapeIdentifier { typedef Iterator<iso::CINT> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CGeometricShapeEntity_altova_label> label;
	struct label { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CGeometricShapeEntity_altova_description> description;
	struct description { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CBL, _altova_mi_altova_CGeometricShapeEntity_altova_includeFlag> includeFlag;
	struct includeFlag { typedef Iterator<iso::CBL> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CGeometricShapeEntity_altova_comment> comment;
	struct comment { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CGeometricShapeEntity_altova_lineColor> lineColor;
	struct lineColor { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CGeometricShapeEntity_altova_lineOpacity> lineOpacity;
	struct lineOpacity { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CGeometricShapeEntity_altova_lineStyle> lineStyle;
	struct lineStyle { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CGeometricShapeEntity_altova_lineThickness> lineThickness;
	struct lineThickness { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CINT, _altova_mi_altova_CGeometricShapeEntity_altova_questionIndex> questionIndex;
	struct questionIndex { typedef Iterator<iso::CINT> iterator; };
	MemberElement<iso::CCD, _altova_mi_altova_CGeometricShapeEntity_altova_interpolationMethod> interpolationMethod;
	struct interpolationMethod { typedef Iterator<iso::CCD> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CGeometricShapeEntity
