/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIVL_REAL
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIVL_REAL

#include "type_iso.CQSET_REAL.h"


namespace AIMXML
{

namespace iso
{	

class CIVL_REAL : public ::AIMXML::iso::CQSET_REAL
{
public:
	AIMXML_EXPORT CIVL_REAL(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CIVL_REAL(CIVL_REAL const& init);
	void operator=(CIVL_REAL const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CIVL_REAL); }

	MemberAttribute<bool,_altova_mi_iso_altova_CIVL_REAL_altova_lowClosed, 0, 0> lowClosed;	// lowClosed Cboolean

	MemberAttribute<bool,_altova_mi_iso_altova_CIVL_REAL_altova_highClosed, 0, 0> highClosed;	// highClosed Cboolean
	MemberElement<iso::CREAL, _altova_mi_iso_altova_CIVL_REAL_altova_low> low;
	struct low { typedef Iterator<iso::CREAL> iterator; };
	MemberElement<iso::CREAL, _altova_mi_iso_altova_CIVL_REAL_altova_high> high;
	struct high { typedef Iterator<iso::CREAL> iterator; };
	MemberElement<iso::CQTY, _altova_mi_iso_altova_CIVL_REAL_altova_width> width;
	struct width { typedef Iterator<iso::CQTY> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIVL_REAL
