/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CTwoDimensionPoint
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CTwoDimensionPoint

#include "type_.CTwoDimensionGeometricShapeEntity.h"


namespace AIMXML
{

class CTwoDimensionPoint : public ::AIMXML::CTwoDimensionGeometricShapeEntity
{
public:
	AIMXML_EXPORT CTwoDimensionPoint(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CTwoDimensionPoint(CTwoDimensionPoint const& init);
	void operator=(CTwoDimensionPoint const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CTwoDimensionPoint); }
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CTwoDimensionPoint
