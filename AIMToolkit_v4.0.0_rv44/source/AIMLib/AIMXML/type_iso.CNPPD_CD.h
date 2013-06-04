/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CNPPD_CD
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CNPPD_CD

#include "type_iso.CANY.h"


namespace AIMXML
{

namespace iso
{	

class CNPPD_CD : public ::AIMXML::iso::CANY
{
public:
	AIMXML_EXPORT CNPPD_CD(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CNPPD_CD(CNPPD_CD const& init);
	void operator=(CNPPD_CD const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CNPPD_CD); }
	MemberElement<iso::CUVP_CD, _altova_mi_iso_altova_CNPPD_CD_altova_item> item;
	struct item { typedef Iterator<iso::CUVP_CD> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CNPPD_CD
