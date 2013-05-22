/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CTwoDimensionMultiPoint
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CTwoDimensionMultiPoint

#include "type_.CTwoDimensionGeometricShapeEntity.h"


namespace AIMXML
{

class CTwoDimensionMultiPoint : public ::AIMXML::CTwoDimensionGeometricShapeEntity
{
public:
	AIMXML_EXPORT CTwoDimensionMultiPoint(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CTwoDimensionMultiPoint(CTwoDimensionMultiPoint const& init);
	void operator=(CTwoDimensionMultiPoint const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CTwoDimensionMultiPoint); }
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CTwoDimensionMultiPoint
