/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CTwoDimensionSpatialCoordinate
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CTwoDimensionSpatialCoordinate

#include "type_.CSpatialCoordinate.h"


namespace AIMXML
{

class CTwoDimensionSpatialCoordinate : public ::AIMXML::CSpatialCoordinate
{
public:
	AIMXML_EXPORT CTwoDimensionSpatialCoordinate(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CTwoDimensionSpatialCoordinate(CTwoDimensionSpatialCoordinate const& init);
	void operator=(CTwoDimensionSpatialCoordinate const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CTwoDimensionSpatialCoordinate); }

	MemberAttribute<string_type,_altova_mi_altova_CTwoDimensionSpatialCoordinate_altova_imageReferenceUID, 0, 0> imageReferenceUID;	// imageReferenceUID Cstring

	MemberAttribute<__int64,_altova_mi_altova_CTwoDimensionSpatialCoordinate_altova_referencedFrameNumber, 0, 0> referencedFrameNumber;	// referencedFrameNumber Cinteger

	MemberAttribute<double,_altova_mi_altova_CTwoDimensionSpatialCoordinate_altova_x, 0, 0> x;	// x Cdouble

	MemberAttribute<double,_altova_mi_altova_CTwoDimensionSpatialCoordinate_altova_y, 0, 0> y;	// y Cdouble
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CTwoDimensionSpatialCoordinate
