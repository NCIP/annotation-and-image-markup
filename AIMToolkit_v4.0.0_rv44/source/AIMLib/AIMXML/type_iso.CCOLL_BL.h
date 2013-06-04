/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CCOLL_BL
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CCOLL_BL

#include "type_iso.CANY.h"


namespace AIMXML
{

namespace iso
{	

class CCOLL_BL : public ::AIMXML::iso::CANY
{
public:
	AIMXML_EXPORT CCOLL_BL(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CCOLL_BL(CCOLL_BL const& init);
	void operator=(CCOLL_BL const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CCOLL_BL); }
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CCOLL_BL
