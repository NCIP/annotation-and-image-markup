/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CSegmentationEntity
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CSegmentationEntity

#include "type_.CEntity.h"


namespace AIMXML
{

class CSegmentationEntity : public ::AIMXML::CEntity
{
public:
	AIMXML_EXPORT CSegmentationEntity(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CSegmentationEntity(CSegmentationEntity const& init);
	void operator=(CSegmentationEntity const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CSegmentationEntity); }
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CSegmentationEntity
