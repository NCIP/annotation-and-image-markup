/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CMO
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CMO

#include "type_iso.CQTY.h"


namespace AIMXML
{

namespace iso
{	

class CMO : public ::AIMXML::iso::CQTY
{
public:
	AIMXML_EXPORT CMO(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CMO(CMO const& init);
	void operator=(CMO const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CMO); }

	MemberAttribute<double,_altova_mi_iso_altova_CMO_altova_value2, 0, 0> value2;	// value Cdouble

	MemberAttribute<int,_altova_mi_iso_altova_CMO_altova_precision, 0, 0> precision;	// precision Cint

	MemberAttribute<string_type,_altova_mi_iso_altova_CMO_altova_currency, 0, 0> currency;	// currency CCode
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CMO
