/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CPIVL_TS_Date_Full
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CPIVL_TS_Date_Full

#include "type_iso.CQSET_TS_Date_Full.h"


namespace AIMXML
{

namespace iso
{	

class CPIVL_TS_Date_Full : public ::AIMXML::iso::CQSET_TS_Date_Full
{
public:
	AIMXML_EXPORT CPIVL_TS_Date_Full(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CPIVL_TS_Date_Full(CPIVL_TS_Date_Full const& init);
	void operator=(CPIVL_TS_Date_Full const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CPIVL_TS_Date_Full); }
	MemberAttribute<string_type,_altova_mi_iso_altova_CPIVL_TS_Date_Full_altova_alignment, 0, 15> alignment;	// alignment CCalendarCycle

	MemberAttribute<bool,_altova_mi_iso_altova_CPIVL_TS_Date_Full_altova_institutionSpecified, 0, 0> institutionSpecified;	// institutionSpecified Cboolean
	MemberElement<iso::CIVL_TS_Date_Full, _altova_mi_iso_altova_CPIVL_TS_Date_Full_altova_phase> phase;
	struct phase { typedef Iterator<iso::CIVL_TS_Date_Full> iterator; };
	MemberElement<iso::CPQ, _altova_mi_iso_altova_CPIVL_TS_Date_Full_altova_period> period;
	struct period { typedef Iterator<iso::CPQ> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CPIVL_TS_Date_Full
