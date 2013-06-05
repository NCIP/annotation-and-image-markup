/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_CS
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_CS

#include "type_iso.CCOLL_CS.h"


namespace AIMXML
{

namespace iso
{	

class CBAG_CS : public ::AIMXML::iso::CCOLL_CS
{
public:
	AIMXML_EXPORT CBAG_CS(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CBAG_CS(CBAG_CS const& init);
	void operator=(CBAG_CS const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CBAG_CS); }
	MemberElement<iso::CCS, _altova_mi_iso_altova_CBAG_CS_altova_item> item;
	struct item { typedef Iterator<iso::CCS> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_CS
