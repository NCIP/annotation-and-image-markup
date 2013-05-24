/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_ED_Doc
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_ED_Doc

#include "type_iso.CCOLL_ED_Doc.h"


namespace AIMXML
{

namespace iso
{	

class CDSET_ED_Doc : public ::AIMXML::iso::CCOLL_ED_Doc
{
public:
	AIMXML_EXPORT CDSET_ED_Doc(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CDSET_ED_Doc(CDSET_ED_Doc const& init);
	void operator=(CDSET_ED_Doc const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CDSET_ED_Doc); }
	MemberElement<iso::CED_Doc, _altova_mi_iso_altova_CDSET_ED_Doc_altova_item> item;
	struct item { typedef Iterator<iso::CED_Doc> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_ED_Doc
