/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CCS
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CCS

#include "type_iso.CANY.h"


namespace AIMXML
{

namespace iso
{	

class CCS : public ::AIMXML::iso::CANY
{
public:
	AIMXML_EXPORT CCS(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CCS(CCS const& init);
	void operator=(CCS const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CCS); }

	MemberAttribute<string_type,_altova_mi_iso_altova_CCS_altova_code, 0, 0> code;	// code Cstring
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CCS
