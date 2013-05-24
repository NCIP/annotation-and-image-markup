/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_BL
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_BL

#include "type_iso.CCOLL_BL.h"


namespace AIMXML
{

namespace iso
{	

class CDSET_BL : public ::AIMXML::iso::CCOLL_BL
{
public:
	AIMXML_EXPORT CDSET_BL(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CDSET_BL(CDSET_BL const& init);
	void operator=(CDSET_BL const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CDSET_BL); }
	MemberElement<iso::CBL, _altova_mi_iso_altova_CDSET_BL_altova_item> item;
	struct item { typedef Iterator<iso::CBL> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_BL
