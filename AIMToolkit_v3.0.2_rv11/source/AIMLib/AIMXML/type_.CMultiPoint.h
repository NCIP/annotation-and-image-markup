/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CMultiPoint
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CMultiPoint

#include "type_.CGeometricShape.h"


namespace AIMXML
{

class CMultiPoint : public ::AIMXML::CGeometricShape
{
public:
	AIMXML_EXPORT CMultiPoint(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CMultiPoint(CMultiPoint const& init);
	void operator=(CMultiPoint const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CMultiPoint); }
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CMultiPoint
