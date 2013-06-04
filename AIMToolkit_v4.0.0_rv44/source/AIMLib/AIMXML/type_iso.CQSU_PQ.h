/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSU_PQ
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSU_PQ

#include "type_iso.CQSET_PQ.h"


namespace AIMXML
{

namespace iso
{	

class CQSU_PQ : public ::AIMXML::iso::CQSET_PQ
{
public:
	AIMXML_EXPORT CQSU_PQ(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CQSU_PQ(CQSU_PQ const& init);
	void operator=(CQSU_PQ const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CQSU_PQ); }
	MemberElement<iso::CQSET_PQ, _altova_mi_iso_altova_CQSU_PQ_altova_term> term;
	struct term { typedef Iterator<iso::CQSET_PQ> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSU_PQ
