/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CThreeDimensionPolyline
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CThreeDimensionPolyline

#include "type_.CThreeDimensionGeometricShapeEntity.h"


namespace AIMXML
{

class CThreeDimensionPolyline : public ::AIMXML::CThreeDimensionGeometricShapeEntity
{
public:
	AIMXML_EXPORT CThreeDimensionPolyline(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CThreeDimensionPolyline(CThreeDimensionPolyline const& init);
	void operator=(CThreeDimensionPolyline const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CThreeDimensionPolyline); }
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CThreeDimensionPolyline
