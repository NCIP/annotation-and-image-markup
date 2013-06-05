/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CNPPD_SC
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CNPPD_SC

#include "type_iso.CANY.h"


namespace AIMXML
{

namespace iso
{	

class CNPPD_SC : public ::AIMXML::iso::CANY
{
public:
	AIMXML_EXPORT CNPPD_SC(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CNPPD_SC(CNPPD_SC const& init);
	void operator=(CNPPD_SC const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CNPPD_SC); }
	MemberElement<iso::CUVP_SC, _altova_mi_iso_altova_CNPPD_SC_altova_item> item;
	struct item { typedef Iterator<iso::CUVP_SC> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CNPPD_SC
