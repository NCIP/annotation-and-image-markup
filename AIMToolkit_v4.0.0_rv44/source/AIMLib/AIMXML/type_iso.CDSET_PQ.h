/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_PQ
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_PQ

#include "type_iso.CCOLL_PQ.h"


namespace AIMXML
{

namespace iso
{	

class CDSET_PQ : public ::AIMXML::iso::CCOLL_PQ
{
public:
	AIMXML_EXPORT CDSET_PQ(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CDSET_PQ(CDSET_PQ const& init);
	void operator=(CDSET_PQ const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CDSET_PQ); }
	MemberElement<iso::CPQ, _altova_mi_iso_altova_CDSET_PQ_altova_item> item;
	struct item { typedef Iterator<iso::CPQ> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_PQ
