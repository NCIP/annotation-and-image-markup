/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_PQ_Time
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_PQ_Time

#include "type_iso.CCOLL_PQ_Time.h"


namespace AIMXML
{

namespace iso
{	

class CBAG_PQ_Time : public ::AIMXML::iso::CCOLL_PQ_Time
{
public:
	AIMXML_EXPORT CBAG_PQ_Time(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CBAG_PQ_Time(CBAG_PQ_Time const& init);
	void operator=(CBAG_PQ_Time const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CBAG_PQ_Time); }
	MemberElement<iso::CPQ_Time, _altova_mi_iso_altova_CBAG_PQ_Time_altova_item> item;
	struct item { typedef Iterator<iso::CPQ_Time> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_PQ_Time
