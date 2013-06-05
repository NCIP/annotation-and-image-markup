/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CTwoDimensionSpatialCoordinate
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CTwoDimensionSpatialCoordinate



namespace AIMXML
{

class CTwoDimensionSpatialCoordinate : public TypeBase
{
public:
	AIMXML_EXPORT CTwoDimensionSpatialCoordinate(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CTwoDimensionSpatialCoordinate(CTwoDimensionSpatialCoordinate const& init);
	void operator=(CTwoDimensionSpatialCoordinate const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CTwoDimensionSpatialCoordinate); }
	MemberElement<iso::CINT, _altova_mi_altova_CTwoDimensionSpatialCoordinate_altova_coordinateIndex> coordinateIndex;
	struct coordinateIndex { typedef Iterator<iso::CINT> iterator; };
	MemberElement<iso::CREAL, _altova_mi_altova_CTwoDimensionSpatialCoordinate_altova_x> x;
	struct x { typedef Iterator<iso::CREAL> iterator; };
	MemberElement<iso::CREAL, _altova_mi_altova_CTwoDimensionSpatialCoordinate_altova_y> y;
	struct y { typedef Iterator<iso::CREAL> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CTwoDimensionSpatialCoordinate
