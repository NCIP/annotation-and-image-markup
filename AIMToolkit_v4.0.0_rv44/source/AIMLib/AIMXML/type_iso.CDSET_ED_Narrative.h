/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_ED_Narrative
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_ED_Narrative

#include "type_iso.CCOLL_ED_Narrative.h"


namespace AIMXML
{

namespace iso
{	

class CDSET_ED_Narrative : public ::AIMXML::iso::CCOLL_ED_Narrative
{
public:
	AIMXML_EXPORT CDSET_ED_Narrative(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CDSET_ED_Narrative(CDSET_ED_Narrative const& init);
	void operator=(CDSET_ED_Narrative const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CDSET_ED_Narrative); }
	MemberElement<iso::CED_Narrative, _altova_mi_iso_altova_CDSET_ED_Narrative_altova_item> item;
	struct item { typedef Iterator<iso::CED_Narrative> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_ED_Narrative
