/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImageAnnotationHasThreeDimensionGeometricShapeEntityStatement
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImageAnnotationHasThreeDimensionGeometricShapeEntityStatement

#include "type_.CImageAnnotationStatement.h"


namespace AIMXML
{

class CImageAnnotationHasThreeDimensionGeometricShapeEntityStatement : public ::AIMXML::CImageAnnotationStatement
{
public:
	AIMXML_EXPORT CImageAnnotationHasThreeDimensionGeometricShapeEntityStatement(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CImageAnnotationHasThreeDimensionGeometricShapeEntityStatement(CImageAnnotationHasThreeDimensionGeometricShapeEntityStatement const& init);
	void operator=(CImageAnnotationHasThreeDimensionGeometricShapeEntityStatement const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CImageAnnotationHasThreeDimensionGeometricShapeEntityStatement); }
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImageAnnotationHasThreeDimensionGeometricShapeEntityStatement
