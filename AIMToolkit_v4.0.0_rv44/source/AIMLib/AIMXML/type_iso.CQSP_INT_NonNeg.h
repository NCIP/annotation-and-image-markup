/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSP_INT_NonNeg
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSP_INT_NonNeg

#include "type_iso.CQSET_INT_NonNeg.h"


namespace AIMXML
{

namespace iso
{	

class CQSP_INT_NonNeg : public ::AIMXML::iso::CQSET_INT_NonNeg
{
public:
	AIMXML_EXPORT CQSP_INT_NonNeg(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CQSP_INT_NonNeg(CQSP_INT_NonNeg const& init);
	void operator=(CQSP_INT_NonNeg const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CQSP_INT_NonNeg); }
	MemberElement<iso::CQSET_INT_NonNeg, _altova_mi_iso_altova_CQSP_INT_NonNeg_altova_first> first;
	struct first { typedef Iterator<iso::CQSET_INT_NonNeg> iterator; };
	MemberElement<iso::CQSET_INT_NonNeg, _altova_mi_iso_altova_CQSP_INT_NonNeg_altova_second> second;
	struct second { typedef Iterator<iso::CQSET_INT_NonNeg> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSP_INT_NonNeg
