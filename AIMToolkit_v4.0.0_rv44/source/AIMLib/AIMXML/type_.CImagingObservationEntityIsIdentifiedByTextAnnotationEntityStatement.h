/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImagingObservationEntityIsIdentifiedByTextAnnotationEntityStatement
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImagingObservationEntityIsIdentifiedByTextAnnotationEntityStatement

#include "type_.CImageAnnotationStatement.h"


namespace AIMXML
{

class CImagingObservationEntityIsIdentifiedByTextAnnotationEntityStatement : public ::AIMXML::CImageAnnotationStatement
{
public:
	AIMXML_EXPORT CImagingObservationEntityIsIdentifiedByTextAnnotationEntityStatement(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CImagingObservationEntityIsIdentifiedByTextAnnotationEntityStatement(CImagingObservationEntityIsIdentifiedByTextAnnotationEntityStatement const& init);
	void operator=(CImagingObservationEntityIsIdentifiedByTextAnnotationEntityStatement const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CImagingObservationEntityIsIdentifiedByTextAnnotationEntityStatement); }
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImagingObservationEntityIsIdentifiedByTextAnnotationEntityStatement
