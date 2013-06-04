/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CEN
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CEN

#include "type_iso.CANY.h"


namespace AIMXML
{

namespace iso
{	

class CEN : public ::AIMXML::iso::CANY
{
public:
	AIMXML_EXPORT CEN(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CEN(CEN const& init);
	void operator=(CEN const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CEN); }
	MemberAttribute<string_type,_altova_mi_iso_altova_CEN_altova_use, 1, 12> use;	// use Cset_EntityNameUse
	MemberElement<iso::CENXP, _altova_mi_iso_altova_CEN_altova_part> part;
	struct part { typedef Iterator<iso::CENXP> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CEN
