/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CLIST_RTO
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CLIST_RTO

#include "type_iso.CANY.h"


namespace AIMXML
{

namespace iso
{	

class CLIST_RTO : public ::AIMXML::iso::CANY
{
public:
	AIMXML_EXPORT CLIST_RTO(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CLIST_RTO(CLIST_RTO const& init);
	void operator=(CLIST_RTO const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CLIST_RTO); }
	MemberElement<iso::CRTO, _altova_mi_iso_altova_CLIST_RTO_altova_item> item;
	struct item { typedef Iterator<iso::CRTO> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CLIST_RTO
