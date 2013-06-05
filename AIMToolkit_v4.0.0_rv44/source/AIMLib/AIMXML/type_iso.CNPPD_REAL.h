/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CNPPD_REAL
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CNPPD_REAL

#include "type_iso.CANY.h"


namespace AIMXML
{

namespace iso
{	

class CNPPD_REAL : public ::AIMXML::iso::CANY
{
public:
	AIMXML_EXPORT CNPPD_REAL(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CNPPD_REAL(CNPPD_REAL const& init);
	void operator=(CNPPD_REAL const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CNPPD_REAL); }
	MemberElement<iso::CUVP_REAL, _altova_mi_iso_altova_CNPPD_REAL_altova_item> item;
	struct item { typedef Iterator<iso::CUVP_REAL> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CNPPD_REAL
