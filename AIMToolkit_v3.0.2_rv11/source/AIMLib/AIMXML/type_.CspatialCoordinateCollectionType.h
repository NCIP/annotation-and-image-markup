/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CspatialCoordinateCollectionType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CspatialCoordinateCollectionType



namespace AIMXML
{

class CspatialCoordinateCollectionType : public TypeBase
{
public:
	AIMXML_EXPORT CspatialCoordinateCollectionType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CspatialCoordinateCollectionType(CspatialCoordinateCollectionType const& init);
	void operator=(CspatialCoordinateCollectionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CspatialCoordinateCollectionType); }
	MemberElement<CSpatialCoordinate, _altova_mi_altova_CspatialCoordinateCollectionType_altova_SpatialCoordinate> SpatialCoordinate;
	struct SpatialCoordinate { typedef Iterator<CSpatialCoordinate> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CspatialCoordinateCollectionType
