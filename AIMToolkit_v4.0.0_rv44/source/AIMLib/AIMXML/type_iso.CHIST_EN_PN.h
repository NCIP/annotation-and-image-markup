/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_EN_PN
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_EN_PN

#include "type_iso.CLIST_EN_PN.h"


namespace AIMXML
{

namespace iso
{	

class CHIST_EN_PN : public ::AIMXML::iso::CLIST_EN_PN
{
public:
	AIMXML_EXPORT CHIST_EN_PN(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CHIST_EN_PN(CHIST_EN_PN const& init);
	void operator=(CHIST_EN_PN const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CHIST_EN_PN); }
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_EN_PN
