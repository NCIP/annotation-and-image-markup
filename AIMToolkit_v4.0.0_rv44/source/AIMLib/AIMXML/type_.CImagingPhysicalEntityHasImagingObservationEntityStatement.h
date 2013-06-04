/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImagingPhysicalEntityHasImagingObservationEntityStatement
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImagingPhysicalEntityHasImagingObservationEntityStatement

#include "type_.CAnnotationStatement.h"


namespace AIMXML
{

class CImagingPhysicalEntityHasImagingObservationEntityStatement : public ::AIMXML::CAnnotationStatement
{
public:
	AIMXML_EXPORT CImagingPhysicalEntityHasImagingObservationEntityStatement(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CImagingPhysicalEntityHasImagingObservationEntityStatement(CImagingPhysicalEntityHasImagingObservationEntityStatement const& init);
	void operator=(CImagingPhysicalEntityHasImagingObservationEntityStatement const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CImagingPhysicalEntityHasImagingObservationEntityStatement); }
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImagingPhysicalEntityHasImagingObservationEntityStatement
