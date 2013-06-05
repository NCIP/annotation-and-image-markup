/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CthreeDimensionSpatialCoordinateCollectionType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CthreeDimensionSpatialCoordinateCollectionType



namespace AIMXML
{

class CthreeDimensionSpatialCoordinateCollectionType : public TypeBase
{
public:
	AIMXML_EXPORT CthreeDimensionSpatialCoordinateCollectionType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CthreeDimensionSpatialCoordinateCollectionType(CthreeDimensionSpatialCoordinateCollectionType const& init);
	void operator=(CthreeDimensionSpatialCoordinateCollectionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CthreeDimensionSpatialCoordinateCollectionType); }
	MemberElement<CThreeDimensionSpatialCoordinate, _altova_mi_altova_CthreeDimensionSpatialCoordinateCollectionType_altova_ThreeDimensionSpatialCoordinate> ThreeDimensionSpatialCoordinate;
	struct ThreeDimensionSpatialCoordinate { typedef Iterator<CThreeDimensionSpatialCoordinate> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CthreeDimensionSpatialCoordinateCollectionType
