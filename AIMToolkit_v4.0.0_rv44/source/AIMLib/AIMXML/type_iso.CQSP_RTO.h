/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSP_RTO
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSP_RTO

#include "type_iso.CQSET_RTO.h"


namespace AIMXML
{

namespace iso
{	

class CQSP_RTO : public ::AIMXML::iso::CQSET_RTO
{
public:
	AIMXML_EXPORT CQSP_RTO(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CQSP_RTO(CQSP_RTO const& init);
	void operator=(CQSP_RTO const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CQSP_RTO); }
	MemberElement<iso::CQSET_RTO, _altova_mi_iso_altova_CQSP_RTO_altova_first> first;
	struct first { typedef Iterator<iso::CQSET_RTO> iterator; };
	MemberElement<iso::CQSET_RTO, _altova_mi_iso_altova_CQSP_RTO_altova_second> second;
	struct second { typedef Iterator<iso::CQSET_RTO> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSP_RTO
