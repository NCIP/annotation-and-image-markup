/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSP_PQ
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSP_PQ

#include "type_iso.CQSET_PQ.h"


namespace AIMXML
{

namespace iso
{	

class CQSP_PQ : public ::AIMXML::iso::CQSET_PQ
{
public:
	AIMXML_EXPORT CQSP_PQ(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CQSP_PQ(CQSP_PQ const& init);
	void operator=(CQSP_PQ const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CQSP_PQ); }
	MemberElement<iso::CQSET_PQ, _altova_mi_iso_altova_CQSP_PQ_altova_first> first;
	struct first { typedef Iterator<iso::CQSET_PQ> iterator; };
	MemberElement<iso::CQSET_PQ, _altova_mi_iso_altova_CQSP_PQ_altova_second> second;
	struct second { typedef Iterator<iso::CQSET_PQ> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSP_PQ
