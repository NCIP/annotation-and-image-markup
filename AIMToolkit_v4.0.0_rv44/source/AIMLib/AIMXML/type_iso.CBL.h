/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBL
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBL

#include "type_iso.CANY.h"


namespace AIMXML
{

namespace iso
{	

class CBL : public ::AIMXML::iso::CANY
{
public:
	AIMXML_EXPORT CBL(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CBL(CBL const& init);
	void operator=(CBL const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CBL); }

	MemberAttribute<bool,_altova_mi_iso_altova_CBL_altova_value2, 0, 0> value2;	// value Cboolean
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBL
