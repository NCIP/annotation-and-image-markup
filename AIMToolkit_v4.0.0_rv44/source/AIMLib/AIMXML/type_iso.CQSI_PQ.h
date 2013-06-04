/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSI_PQ
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSI_PQ

#include "type_iso.CQSET_PQ.h"


namespace AIMXML
{

namespace iso
{	

class CQSI_PQ : public ::AIMXML::iso::CQSET_PQ
{
public:
	AIMXML_EXPORT CQSI_PQ(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CQSI_PQ(CQSI_PQ const& init);
	void operator=(CQSI_PQ const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CQSI_PQ); }
	MemberElement<iso::CQSET_PQ, _altova_mi_iso_altova_CQSI_PQ_altova_term> term;
	struct term { typedef Iterator<iso::CQSET_PQ> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSI_PQ
