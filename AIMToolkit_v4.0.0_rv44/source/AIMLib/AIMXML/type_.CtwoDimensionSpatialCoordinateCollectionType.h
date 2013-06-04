/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CtwoDimensionSpatialCoordinateCollectionType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CtwoDimensionSpatialCoordinateCollectionType



namespace AIMXML
{

class CtwoDimensionSpatialCoordinateCollectionType : public TypeBase
{
public:
	AIMXML_EXPORT CtwoDimensionSpatialCoordinateCollectionType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CtwoDimensionSpatialCoordinateCollectionType(CtwoDimensionSpatialCoordinateCollectionType const& init);
	void operator=(CtwoDimensionSpatialCoordinateCollectionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CtwoDimensionSpatialCoordinateCollectionType); }
	MemberElement<CTwoDimensionSpatialCoordinate, _altova_mi_altova_CtwoDimensionSpatialCoordinateCollectionType_altova_TwoDimensionSpatialCoordinate> TwoDimensionSpatialCoordinate;
	struct TwoDimensionSpatialCoordinate { typedef Iterator<CTwoDimensionSpatialCoordinate> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CtwoDimensionSpatialCoordinateCollectionType
