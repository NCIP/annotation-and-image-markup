/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImagingPhysicalEntityHasCalculationEntityStatement
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImagingPhysicalEntityHasCalculationEntityStatement

#include "type_.CAnnotationStatement.h"


namespace AIMXML
{

class CImagingPhysicalEntityHasCalculationEntityStatement : public ::AIMXML::CAnnotationStatement
{
public:
	AIMXML_EXPORT CImagingPhysicalEntityHasCalculationEntityStatement(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CImagingPhysicalEntityHasCalculationEntityStatement(CImagingPhysicalEntityHasCalculationEntityStatement const& init);
	void operator=(CImagingPhysicalEntityHasCalculationEntityStatement const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CImagingPhysicalEntityHasCalculationEntityStatement); }
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImagingPhysicalEntityHasCalculationEntityStatement
