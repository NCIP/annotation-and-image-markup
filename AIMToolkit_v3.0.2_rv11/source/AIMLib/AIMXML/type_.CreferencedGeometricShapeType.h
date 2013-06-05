/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CreferencedGeometricShapeType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CreferencedGeometricShapeType



namespace AIMXML
{

class CreferencedGeometricShapeType : public TypeBase
{
public:
	AIMXML_EXPORT CreferencedGeometricShapeType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CreferencedGeometricShapeType(CreferencedGeometricShapeType const& init);
	void operator=(CreferencedGeometricShapeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CreferencedGeometricShapeType); }
	MemberElement<CReferencedGeometricShape, _altova_mi_altova_CreferencedGeometricShapeType_altova_ReferencedGeometricShape> ReferencedGeometricShape;
	struct ReferencedGeometricShape { typedef Iterator<CReferencedGeometricShape> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CreferencedGeometricShapeType
