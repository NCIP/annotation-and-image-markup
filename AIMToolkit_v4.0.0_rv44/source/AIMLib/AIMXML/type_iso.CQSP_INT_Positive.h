/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSP_INT_Positive
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSP_INT_Positive

#include "type_iso.CQSET_INT_Positive.h"


namespace AIMXML
{

namespace iso
{	

class CQSP_INT_Positive : public ::AIMXML::iso::CQSET_INT_Positive
{
public:
	AIMXML_EXPORT CQSP_INT_Positive(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CQSP_INT_Positive(CQSP_INT_Positive const& init);
	void operator=(CQSP_INT_Positive const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CQSP_INT_Positive); }
	MemberElement<iso::CQSET_INT_Positive, _altova_mi_iso_altova_CQSP_INT_Positive_altova_first> first;
	struct first { typedef Iterator<iso::CQSET_INT_Positive> iterator; };
	MemberElement<iso::CQSET_INT_Positive, _altova_mi_iso_altova_CQSP_INT_Positive_altova_second> second;
	struct second { typedef Iterator<iso::CQSET_INT_Positive> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSP_INT_Positive
