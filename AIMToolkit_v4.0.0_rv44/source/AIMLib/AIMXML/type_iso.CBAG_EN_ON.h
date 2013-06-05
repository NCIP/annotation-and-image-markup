/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_EN_ON
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_EN_ON

#include "type_iso.CCOLL_EN_ON.h"


namespace AIMXML
{

namespace iso
{	

class CBAG_EN_ON : public ::AIMXML::iso::CCOLL_EN_ON
{
public:
	AIMXML_EXPORT CBAG_EN_ON(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CBAG_EN_ON(CBAG_EN_ON const& init);
	void operator=(CBAG_EN_ON const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CBAG_EN_ON); }
	MemberElement<iso::CEN_ON, _altova_mi_iso_altova_CBAG_EN_ON_altova_item> item;
	struct item { typedef Iterator<iso::CEN_ON> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_EN_ON
