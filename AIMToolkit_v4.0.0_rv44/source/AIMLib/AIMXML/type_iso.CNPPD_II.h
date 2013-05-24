/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CNPPD_II
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CNPPD_II

#include "type_iso.CANY.h"


namespace AIMXML
{

namespace iso
{	

class CNPPD_II : public ::AIMXML::iso::CANY
{
public:
	AIMXML_EXPORT CNPPD_II(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CNPPD_II(CNPPD_II const& init);
	void operator=(CNPPD_II const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CNPPD_II); }
	MemberElement<iso::CUVP_II, _altova_mi_iso_altova_CNPPD_II_altova_item> item;
	struct item { typedef Iterator<iso::CUVP_II> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CNPPD_II
