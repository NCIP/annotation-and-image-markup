/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCircle
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCircle

#include "type_.CGeometricShape.h"


namespace AIMXML
{

class CCircle : public ::AIMXML::CGeometricShape
{
public:
	AIMXML_EXPORT CCircle(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CCircle(CCircle const& init);
	void operator=(CCircle const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CCircle); }
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCircle
