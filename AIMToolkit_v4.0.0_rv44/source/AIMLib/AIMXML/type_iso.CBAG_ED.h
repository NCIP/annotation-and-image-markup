/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_ED
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_ED

#include "type_iso.CCOLL_ED.h"


namespace AIMXML
{

namespace iso
{	

class CBAG_ED : public ::AIMXML::iso::CCOLL_ED
{
public:
	AIMXML_EXPORT CBAG_ED(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CBAG_ED(CBAG_ED const& init);
	void operator=(CBAG_ED const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CBAG_ED); }
	MemberElement<iso::CED, _altova_mi_iso_altova_CBAG_ED_altova_item> item;
	struct item { typedef Iterator<iso::CED> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_ED
