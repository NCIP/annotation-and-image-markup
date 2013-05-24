/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CEN_PN
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CEN_PN

#include "type_iso.CEN.h"


namespace AIMXML
{

namespace iso
{	

class CEN_PN : public ::AIMXML::iso::CEN
{
public:
	AIMXML_EXPORT CEN_PN(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CEN_PN(CEN_PN const& init);
	void operator=(CEN_PN const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CEN_PN); }
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CEN_PN
