/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_EN
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_EN

#include "type_iso.CCOLL_EN.h"


namespace AIMXML
{

namespace iso
{	

class CDSET_EN : public ::AIMXML::iso::CCOLL_EN
{
public:
	AIMXML_EXPORT CDSET_EN(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CDSET_EN(CDSET_EN const& init);
	void operator=(CDSET_EN const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CDSET_EN); }
	MemberElement<iso::CEN, _altova_mi_iso_altova_CDSET_EN_altova_item> item;
	struct item { typedef Iterator<iso::CEN> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_EN
