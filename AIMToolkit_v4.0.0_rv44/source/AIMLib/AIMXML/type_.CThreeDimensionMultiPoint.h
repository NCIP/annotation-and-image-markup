/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CThreeDimensionMultiPoint
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CThreeDimensionMultiPoint

#include "type_.CThreeDimensionGeometricShapeEntity.h"


namespace AIMXML
{

class CThreeDimensionMultiPoint : public ::AIMXML::CThreeDimensionGeometricShapeEntity
{
public:
	AIMXML_EXPORT CThreeDimensionMultiPoint(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CThreeDimensionMultiPoint(CThreeDimensionMultiPoint const& init);
	void operator=(CThreeDimensionMultiPoint const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CThreeDimensionMultiPoint); }
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CThreeDimensionMultiPoint
