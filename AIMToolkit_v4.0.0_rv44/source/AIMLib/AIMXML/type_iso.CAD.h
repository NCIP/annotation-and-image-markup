/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CAD
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CAD

#include "type_iso.CANY.h"


namespace AIMXML
{

namespace iso
{	

class CAD : public ::AIMXML::iso::CANY
{
public:
	AIMXML_EXPORT CAD(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CAD(CAD const& init);
	void operator=(CAD const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CAD); }
	MemberAttribute<string_type,_altova_mi_iso_altova_CAD_altova_use, 1, 15> use;	// use Cset_PostalAddressUse

	MemberAttribute<bool,_altova_mi_iso_altova_CAD_altova_isNotOrdered, 0, 0> isNotOrdered;	// isNotOrdered Cboolean
	MemberElement<iso::CADXP, _altova_mi_iso_altova_CAD_altova_part> part;
	struct part { typedef Iterator<iso::CADXP> iterator; };
	MemberElement<iso::CQSET_TS, _altova_mi_iso_altova_CAD_altova_useablePeriod> useablePeriod;
	struct useablePeriod { typedef Iterator<iso::CQSET_TS> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CAD
