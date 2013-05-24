/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CGeneralLesionObservationEntityHasImagingPhysicalEntityStatement
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CGeneralLesionObservationEntityHasImagingPhysicalEntityStatement

#include "type_.CImageAnnotationStatement.h"


namespace AIMXML
{

class CGeneralLesionObservationEntityHasImagingPhysicalEntityStatement : public ::AIMXML::CImageAnnotationStatement
{
public:
	AIMXML_EXPORT CGeneralLesionObservationEntityHasImagingPhysicalEntityStatement(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CGeneralLesionObservationEntityHasImagingPhysicalEntityStatement(CGeneralLesionObservationEntityHasImagingPhysicalEntityStatement const& init);
	void operator=(CGeneralLesionObservationEntityHasImagingPhysicalEntityStatement const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CGeneralLesionObservationEntityHasImagingPhysicalEntityStatement); }
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CGeneralLesionObservationEntityHasImagingPhysicalEntityStatement
