/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CLIST_II
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CLIST_II

#include "type_iso.CANY.h"


namespace AIMXML
{

namespace iso
{	

class CLIST_II : public ::AIMXML::iso::CANY
{
public:
	AIMXML_EXPORT CLIST_II(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CLIST_II(CLIST_II const& init);
	void operator=(CLIST_II const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CLIST_II); }
	MemberElement<iso::CII, _altova_mi_iso_altova_CLIST_II_altova_item> item;
	struct item { typedef Iterator<iso::CII> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CLIST_II
