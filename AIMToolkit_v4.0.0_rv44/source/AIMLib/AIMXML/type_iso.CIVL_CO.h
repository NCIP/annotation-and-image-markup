/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIVL_CO
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIVL_CO

#include "type_iso.CQSET_CO.h"


namespace AIMXML
{

namespace iso
{	

class CIVL_CO : public ::AIMXML::iso::CQSET_CO
{
public:
	AIMXML_EXPORT CIVL_CO(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CIVL_CO(CIVL_CO const& init);
	void operator=(CIVL_CO const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CIVL_CO); }

	MemberAttribute<bool,_altova_mi_iso_altova_CIVL_CO_altova_lowClosed, 0, 0> lowClosed;	// lowClosed Cboolean

	MemberAttribute<bool,_altova_mi_iso_altova_CIVL_CO_altova_highClosed, 0, 0> highClosed;	// highClosed Cboolean
	MemberElement<iso::CCO, _altova_mi_iso_altova_CIVL_CO_altova_low> low;
	struct low { typedef Iterator<iso::CCO> iterator; };
	MemberElement<iso::CCO, _altova_mi_iso_altova_CIVL_CO_altova_high> high;
	struct high { typedef Iterator<iso::CCO> iterator; };
	MemberElement<iso::CQTY, _altova_mi_iso_altova_CIVL_CO_altova_width> width;
	struct width { typedef Iterator<iso::CQTY> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CIVL_CO
