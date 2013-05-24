/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CPQ
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CPQ

#include "type_iso.CQTY.h"


namespace AIMXML
{

namespace iso
{	

class CPQ : public ::AIMXML::iso::CQTY
{
public:
	AIMXML_EXPORT CPQ(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CPQ(CPQ const& init);
	void operator=(CPQ const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CPQ); }

	MemberAttribute<double,_altova_mi_iso_altova_CPQ_altova_value2, 0, 0> value2;	// value Cdouble

	MemberAttribute<int,_altova_mi_iso_altova_CPQ_altova_precision, 0, 0> precision;	// precision Cint

	MemberAttribute<string_type,_altova_mi_iso_altova_CPQ_altova_unit, 0, 0> unit;	// unit CCode
	MemberAttribute<string_type,_altova_mi_iso_altova_CPQ_altova_codingRationale, 1, 4> codingRationale;	// codingRationale Cset_CodingRationale
	MemberElement<iso::CPQR, _altova_mi_iso_altova_CPQ_altova_translation> translation;
	struct translation { typedef Iterator<iso::CPQR> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CPQ
