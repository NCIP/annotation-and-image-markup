/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIVL_PQ_Time
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIVL_PQ_Time

#include "type_iso.CQSET_PQ_Time.h"


namespace AIMXML
{

namespace iso
{	

class CIVL_PQ_Time : public ::AIMXML::iso::CQSET_PQ_Time
{
public:
	AIMXML_EXPORT CIVL_PQ_Time(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CIVL_PQ_Time(CIVL_PQ_Time const& init);
	void operator=(CIVL_PQ_Time const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CIVL_PQ_Time); }

	MemberAttribute<bool,_altova_mi_iso_altova_CIVL_PQ_Time_altova_lowClosed, 0, 0> lowClosed;	// lowClosed Cboolean

	MemberAttribute<bool,_altova_mi_iso_altova_CIVL_PQ_Time_altova_highClosed, 0, 0> highClosed;	// highClosed Cboolean
	MemberElement<iso::CPQ_Time, _altova_mi_iso_altova_CIVL_PQ_Time_altova_low> low;
	struct low { typedef Iterator<iso::CPQ_Time> iterator; };
	MemberElement<iso::CPQ_Time, _altova_mi_iso_altova_CIVL_PQ_Time_altova_high> high;
	struct high { typedef Iterator<iso::CPQ_Time> iterator; };
	MemberElement<iso::CQTY, _altova_mi_iso_altova_CIVL_PQ_Time_altova_width> width;
	struct width { typedef Iterator<iso::CQTY> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIVL_PQ_Time
