/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSD_PQ
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSD_PQ

#include "type_iso.CQSET_PQ.h"


namespace AIMXML
{

namespace iso
{	

class CQSD_PQ : public ::AIMXML::iso::CQSET_PQ
{
public:
	AIMXML_EXPORT CQSD_PQ(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CQSD_PQ(CQSD_PQ const& init);
	void operator=(CQSD_PQ const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CQSD_PQ); }
	MemberElement<iso::CQSET_PQ, _altova_mi_iso_altova_CQSD_PQ_altova_first> first;
	struct first { typedef Iterator<iso::CQSET_PQ> iterator; };
	MemberElement<iso::CQSET_PQ, _altova_mi_iso_altova_CQSD_PQ_altova_second> second;
	struct second { typedef Iterator<iso::CQSET_PQ> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSD_PQ
