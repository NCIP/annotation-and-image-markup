/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CWebImageReference
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CWebImageReference

#include "type_.CImageReference.h"


namespace AIMXML
{

class CWebImageReference : public ::AIMXML::CImageReference
{
public:
	AIMXML_EXPORT CWebImageReference(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CWebImageReference(CWebImageReference const& init);
	void operator=(CWebImageReference const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CWebImageReference); }

	MemberAttribute<string_type,_altova_mi_altova_CWebImageReference_altova_uri, 0, 0> uri;	// uri Cstring
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CWebImageReference
