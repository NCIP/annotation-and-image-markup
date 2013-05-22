/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CGLIST_CO
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CGLIST_CO

#include "type_iso.CANY.h"


namespace AIMXML
{

namespace iso
{	

class CGLIST_CO : public ::AIMXML::iso::CANY
{
public:
	AIMXML_EXPORT CGLIST_CO(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CGLIST_CO(CGLIST_CO const& init);
	void operator=(CGLIST_CO const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CGLIST_CO); }

	MemberAttribute<int,_altova_mi_iso_altova_CGLIST_CO_altova_denominator, 0, 0> denominator;	// denominator Cint

	MemberAttribute<int,_altova_mi_iso_altova_CGLIST_CO_altova_period, 0, 0> period;	// period Cint
	MemberElement<iso::CCO, _altova_mi_iso_altova_CGLIST_CO_altova_head> head;
	struct head { typedef Iterator<iso::CCO> iterator; };
	MemberElement<iso::CQTY, _altova_mi_iso_altova_CGLIST_CO_altova_increment> increment;
	struct increment { typedef Iterator<iso::CQTY> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CGLIST_CO
