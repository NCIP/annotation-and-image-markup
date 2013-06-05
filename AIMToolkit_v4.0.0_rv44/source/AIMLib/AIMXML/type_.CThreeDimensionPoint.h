/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CThreeDimensionPoint
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CThreeDimensionPoint

#include "type_.CThreeDimensionGeometricShapeEntity.h"


namespace AIMXML
{

class CThreeDimensionPoint : public ::AIMXML::CThreeDimensionGeometricShapeEntity
{
public:
	AIMXML_EXPORT CThreeDimensionPoint(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CThreeDimensionPoint(CThreeDimensionPoint const& init);
	void operator=(CThreeDimensionPoint const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CThreeDimensionPoint); }
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CThreeDimensionPoint
