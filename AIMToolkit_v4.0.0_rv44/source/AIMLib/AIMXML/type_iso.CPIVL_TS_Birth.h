/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CPIVL_TS_Birth
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CPIVL_TS_Birth

#include "type_iso.CQSET_TS_Birth.h"


namespace AIMXML
{

namespace iso
{	

class CPIVL_TS_Birth : public ::AIMXML::iso::CQSET_TS_Birth
{
public:
	AIMXML_EXPORT CPIVL_TS_Birth(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CPIVL_TS_Birth(CPIVL_TS_Birth const& init);
	void operator=(CPIVL_TS_Birth const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CPIVL_TS_Birth); }
	MemberAttribute<string_type,_altova_mi_iso_altova_CPIVL_TS_Birth_altova_alignment, 0, 15> alignment;	// alignment CCalendarCycle

	MemberAttribute<bool,_altova_mi_iso_altova_CPIVL_TS_Birth_altova_institutionSpecified, 0, 0> institutionSpecified;	// institutionSpecified Cboolean
	MemberElement<iso::CIVL_TS_Birth, _altova_mi_iso_altova_CPIVL_TS_Birth_altova_phase> phase;
	struct phase { typedef Iterator<iso::CIVL_TS_Birth> iterator; };
	MemberElement<iso::CPQ, _altova_mi_iso_altova_CPIVL_TS_Birth_altova_period> period;
	struct period { typedef Iterator<iso::CPQ> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CPIVL_TS_Birth
