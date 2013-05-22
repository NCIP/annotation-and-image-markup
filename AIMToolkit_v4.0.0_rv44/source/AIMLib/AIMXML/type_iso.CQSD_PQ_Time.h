/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSD_PQ_Time
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSD_PQ_Time

#include "type_iso.CQSET_PQ_Time.h"


namespace AIMXML
{

namespace iso
{	

class CQSD_PQ_Time : public ::AIMXML::iso::CQSET_PQ_Time
{
public:
	AIMXML_EXPORT CQSD_PQ_Time(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CQSD_PQ_Time(CQSD_PQ_Time const& init);
	void operator=(CQSD_PQ_Time const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CQSD_PQ_Time); }
	MemberElement<iso::CQSET_PQ_Time, _altova_mi_iso_altova_CQSD_PQ_Time_altova_first> first;
	struct first { typedef Iterator<iso::CQSET_PQ_Time> iterator; };
	MemberElement<iso::CQSET_PQ_Time, _altova_mi_iso_altova_CQSD_PQ_Time_altova_second> second;
	struct second { typedef Iterator<iso::CQSET_PQ_Time> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSD_PQ_Time
