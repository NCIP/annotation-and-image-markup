/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImagingPhysicalEntityHasTextAnnotationEntityStatement
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImagingPhysicalEntityHasTextAnnotationEntityStatement

#include "type_.CImageAnnotationStatement.h"


namespace AIMXML
{

class CImagingPhysicalEntityHasTextAnnotationEntityStatement : public ::AIMXML::CImageAnnotationStatement
{
public:
	AIMXML_EXPORT CImagingPhysicalEntityHasTextAnnotationEntityStatement(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CImagingPhysicalEntityHasTextAnnotationEntityStatement(CImagingPhysicalEntityHasTextAnnotationEntityStatement const& init);
	void operator=(CImagingPhysicalEntityHasTextAnnotationEntityStatement const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CImagingPhysicalEntityHasTextAnnotationEntityStatement); }
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImagingPhysicalEntityHasTextAnnotationEntityStatement
