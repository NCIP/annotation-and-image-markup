/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_EN_TN
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_EN_TN

#include "type_iso.CCOLL_EN_TN.h"


namespace AIMXML
{

namespace iso
{	

class CBAG_EN_TN : public ::AIMXML::iso::CCOLL_EN_TN
{
public:
	AIMXML_EXPORT CBAG_EN_TN(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CBAG_EN_TN(CBAG_EN_TN const& init);
	void operator=(CBAG_EN_TN const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CBAG_EN_TN); }
	MemberElement<iso::CEN_TN, _altova_mi_iso_altova_CBAG_EN_TN_altova_item> item;
	struct item { typedef Iterator<iso::CEN_TN> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_EN_TN
