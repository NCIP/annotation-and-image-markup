/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CThreeDimensionSpatialCoordinate
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CThreeDimensionSpatialCoordinate



namespace AIMXML
{

class CThreeDimensionSpatialCoordinate : public TypeBase
{
public:
	AIMXML_EXPORT CThreeDimensionSpatialCoordinate(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CThreeDimensionSpatialCoordinate(CThreeDimensionSpatialCoordinate const& init);
	void operator=(CThreeDimensionSpatialCoordinate const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CThreeDimensionSpatialCoordinate); }
	MemberElement<iso::CINT, _altova_mi_altova_CThreeDimensionSpatialCoordinate_altova_coordinateIndex> coordinateIndex;
	struct coordinateIndex { typedef Iterator<iso::CINT> iterator; };
	MemberElement<iso::CREAL, _altova_mi_altova_CThreeDimensionSpatialCoordinate_altova_x> x;
	struct x { typedef Iterator<iso::CREAL> iterator; };
	MemberElement<iso::CREAL, _altova_mi_altova_CThreeDimensionSpatialCoordinate_altova_y> y;
	struct y { typedef Iterator<iso::CREAL> iterator; };
	MemberElement<iso::CREAL, _altova_mi_altova_CThreeDimensionSpatialCoordinate_altova_z> z;
	struct z { typedef Iterator<iso::CREAL> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CThreeDimensionSpatialCoordinate
