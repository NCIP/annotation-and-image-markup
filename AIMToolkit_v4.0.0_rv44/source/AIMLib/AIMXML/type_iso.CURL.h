/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CURL
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CURL

#include "type_iso.CANY.h"


namespace AIMXML
{

namespace iso
{	

class CURL : public ::AIMXML::iso::CANY
{
public:
	AIMXML_EXPORT CURL(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CURL(CURL const& init);
	void operator=(CURL const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CURL); }

	MemberAttribute<string_type,_altova_mi_iso_altova_CURL_altova_value2, 0, 0> value2;	// value CanyURI
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CURL
