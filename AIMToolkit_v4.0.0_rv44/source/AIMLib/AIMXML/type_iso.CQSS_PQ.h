/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSS_PQ
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSS_PQ

#include "type_iso.CQSET_PQ.h"


namespace AIMXML
{

namespace iso
{	

class CQSS_PQ : public ::AIMXML::iso::CQSET_PQ
{
public:
	AIMXML_EXPORT CQSS_PQ(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CQSS_PQ(CQSS_PQ const& init);
	void operator=(CQSS_PQ const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CQSS_PQ); }
	MemberElement<iso::CPQ, _altova_mi_iso_altova_CQSS_PQ_altova_term> term;
	struct term { typedef Iterator<iso::CPQ> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSS_PQ
