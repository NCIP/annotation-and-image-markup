/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSD_MO
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSD_MO

#include "type_iso.CQSET_MO.h"


namespace AIMXML
{

namespace iso
{	

class CQSD_MO : public ::AIMXML::iso::CQSET_MO
{
public:
	AIMXML_EXPORT CQSD_MO(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CQSD_MO(CQSD_MO const& init);
	void operator=(CQSD_MO const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CQSD_MO); }
	MemberElement<iso::CQSET_MO, _altova_mi_iso_altova_CQSD_MO_altova_first> first;
	struct first { typedef Iterator<iso::CQSET_MO> iterator; };
	MemberElement<iso::CQSET_MO, _altova_mi_iso_altova_CQSD_MO_altova_second> second;
	struct second { typedef Iterator<iso::CQSET_MO> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSD_MO
