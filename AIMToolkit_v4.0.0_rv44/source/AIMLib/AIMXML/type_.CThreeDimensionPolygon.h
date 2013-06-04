/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CThreeDimensionPolygon
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CThreeDimensionPolygon

#include "type_.CThreeDimensionGeometricShapeEntity.h"


namespace AIMXML
{

class CThreeDimensionPolygon : public ::AIMXML::CThreeDimensionGeometricShapeEntity
{
public:
	AIMXML_EXPORT CThreeDimensionPolygon(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CThreeDimensionPolygon(CThreeDimensionPolygon const& init);
	void operator=(CThreeDimensionPolygon const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CThreeDimensionPolygon); }
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CThreeDimensionPolygon
