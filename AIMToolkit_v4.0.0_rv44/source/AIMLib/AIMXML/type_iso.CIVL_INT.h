/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIVL_INT
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIVL_INT

#include "type_iso.CQSET_INT.h"


namespace AIMXML
{

namespace iso
{	

class CIVL_INT : public ::AIMXML::iso::CQSET_INT
{
public:
	AIMXML_EXPORT CIVL_INT(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CIVL_INT(CIVL_INT const& init);
	void operator=(CIVL_INT const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CIVL_INT); }

	MemberAttribute<bool,_altova_mi_iso_altova_CIVL_INT_altova_lowClosed, 0, 0> lowClosed;	// lowClosed Cboolean

	MemberAttribute<bool,_altova_mi_iso_altova_CIVL_INT_altova_highClosed, 0, 0> highClosed;	// highClosed Cboolean
	MemberElement<iso::CINT, _altova_mi_iso_altova_CIVL_INT_altova_low> low;
	struct low { typedef Iterator<iso::CINT> iterator; };
	MemberElement<iso::CINT, _altova_mi_iso_altova_CIVL_INT_altova_high> high;
	struct high { typedef Iterator<iso::CINT> iterator; };
	MemberElement<iso::CQTY, _altova_mi_iso_altova_CIVL_INT_altova_width> width;
	struct width { typedef Iterator<iso::CQTY> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIVL_INT
