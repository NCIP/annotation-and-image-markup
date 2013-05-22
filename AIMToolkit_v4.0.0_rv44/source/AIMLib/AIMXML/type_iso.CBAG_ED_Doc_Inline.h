/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_ED_Doc_Inline
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_ED_Doc_Inline

#include "type_iso.CCOLL_ED_Doc_Inline.h"


namespace AIMXML
{

namespace iso
{	

class CBAG_ED_Doc_Inline : public ::AIMXML::iso::CCOLL_ED_Doc_Inline
{
public:
	AIMXML_EXPORT CBAG_ED_Doc_Inline(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CBAG_ED_Doc_Inline(CBAG_ED_Doc_Inline const& init);
	void operator=(CBAG_ED_Doc_Inline const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CBAG_ED_Doc_Inline); }
	MemberElement<iso::CED_Doc_Inline, _altova_mi_iso_altova_CBAG_ED_Doc_Inline_altova_item> item;
	struct item { typedef Iterator<iso::CED_Doc_Inline> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_ED_Doc_Inline
