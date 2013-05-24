/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CgeometricShapeCollectionType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CgeometricShapeCollectionType



namespace AIMXML
{

class CgeometricShapeCollectionType : public TypeBase
{
public:
	AIMXML_EXPORT CgeometricShapeCollectionType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CgeometricShapeCollectionType(CgeometricShapeCollectionType const& init);
	void operator=(CgeometricShapeCollectionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CgeometricShapeCollectionType); }
	MemberElement<CGeometricShape, _altova_mi_altova_CgeometricShapeCollectionType_altova_GeometricShape> GeometricShape;
	struct GeometricShape { typedef Iterator<CGeometricShape> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CgeometricShapeCollectionType
