/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CGeometricShape
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CGeometricShape



namespace AIMXML
{

class CGeometricShape : public TypeBase
{
public:
	AIMXML_EXPORT CGeometricShape(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CGeometricShape(CGeometricShape const& init);
	void operator=(CGeometricShape const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CGeometricShape); }

	MemberAttribute<__int64,_altova_mi_altova_CGeometricShape_altova_cagridId, 0, 0> cagridId;	// cagridId Cinteger

	MemberAttribute<string_type,_altova_mi_altova_CGeometricShape_altova_lineColor, 0, 0> lineColor;	// lineColor Cstring

	MemberAttribute<string_type,_altova_mi_altova_CGeometricShape_altova_lineOpacity, 0, 0> lineOpacity;	// lineOpacity Cstring

	MemberAttribute<string_type,_altova_mi_altova_CGeometricShape_altova_lineStyle, 0, 0> lineStyle;	// lineStyle Cstring

	MemberAttribute<string_type,_altova_mi_altova_CGeometricShape_altova_lineThickness, 0, 0> lineThickness;	// lineThickness Cstring

	MemberAttribute<bool,_altova_mi_altova_CGeometricShape_altova_includeFlag, 0, 0> includeFlag;	// includeFlag Cboolean

	MemberAttribute<__int64,_altova_mi_altova_CGeometricShape_altova_shapeIdentifier, 0, 0> shapeIdentifier;	// shapeIdentifier Cinteger
	MemberElement<CspatialCoordinateCollectionType, _altova_mi_altova_CGeometricShape_altova_spatialCoordinateCollection> spatialCoordinateCollection;
	struct spatialCoordinateCollection { typedef Iterator<CspatialCoordinateCollectionType> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CGeometricShape
