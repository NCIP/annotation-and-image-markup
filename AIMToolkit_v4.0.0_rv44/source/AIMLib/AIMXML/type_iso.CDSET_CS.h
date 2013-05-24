/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_CS
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_CS

#include "type_iso.CCOLL_CS.h"


namespace AIMXML
{

namespace iso
{	

class CDSET_CS : public ::AIMXML::iso::CCOLL_CS
{
public:
	AIMXML_EXPORT CDSET_CS(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CDSET_CS(CDSET_CS const& init);
	void operator=(CDSET_CS const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CDSET_CS); }
	MemberElement<iso::CCS, _altova_mi_iso_altova_CDSET_CS_altova_item> item;
	struct item { typedef Iterator<iso::CCS> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_CS
