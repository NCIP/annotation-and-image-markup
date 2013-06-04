/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIVL_INT_NonNeg
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIVL_INT_NonNeg

#include "type_iso.CQSET_INT_NonNeg.h"


namespace AIMXML
{

namespace iso
{	

class CIVL_INT_NonNeg : public ::AIMXML::iso::CQSET_INT_NonNeg
{
public:
	AIMXML_EXPORT CIVL_INT_NonNeg(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CIVL_INT_NonNeg(CIVL_INT_NonNeg const& init);
	void operator=(CIVL_INT_NonNeg const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CIVL_INT_NonNeg); }

	MemberAttribute<bool,_altova_mi_iso_altova_CIVL_INT_NonNeg_altova_lowClosed, 0, 0> lowClosed;	// lowClosed Cboolean

	MemberAttribute<bool,_altova_mi_iso_altova_CIVL_INT_NonNeg_altova_highClosed, 0, 0> highClosed;	// highClosed Cboolean
	MemberElement<iso::CINT_NonNeg, _altova_mi_iso_altova_CIVL_INT_NonNeg_altova_low> low;
	struct low { typedef Iterator<iso::CINT_NonNeg> iterator; };
	MemberElement<iso::CINT_NonNeg, _altova_mi_iso_altova_CIVL_INT_NonNeg_altova_high> high;
	struct high { typedef Iterator<iso::CINT_NonNeg> iterator; };
	MemberElement<iso::CQTY, _altova_mi_iso_altova_CIVL_INT_NonNeg_altova_width> width;
	struct width { typedef Iterator<iso::CQTY> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIVL_INT_NonNeg
