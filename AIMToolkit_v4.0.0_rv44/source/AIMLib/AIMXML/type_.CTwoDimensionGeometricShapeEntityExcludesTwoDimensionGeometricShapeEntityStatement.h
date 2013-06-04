/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CTwoDimensionGeometricShapeEntityExcludesTwoDimensionGeometricShapeEntityStatement
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CTwoDimensionGeometricShapeEntityExcludesTwoDimensionGeometricShapeEntityStatement

#include "type_.CImageAnnotationStatement.h"


namespace AIMXML
{

class CTwoDimensionGeometricShapeEntityExcludesTwoDimensionGeometricShapeEntityStatement : public ::AIMXML::CImageAnnotationStatement
{
public:
	AIMXML_EXPORT CTwoDimensionGeometricShapeEntityExcludesTwoDimensionGeometricShapeEntityStatement(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CTwoDimensionGeometricShapeEntityExcludesTwoDimensionGeometricShapeEntityStatement(CTwoDimensionGeometricShapeEntityExcludesTwoDimensionGeometricShapeEntityStatement const& init);
	void operator=(CTwoDimensionGeometricShapeEntityExcludesTwoDimensionGeometricShapeEntityStatement const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CTwoDimensionGeometricShapeEntityExcludesTwoDimensionGeometricShapeEntityStatement); }
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CTwoDimensionGeometricShapeEntityExcludesTwoDimensionGeometricShapeEntityStatement
