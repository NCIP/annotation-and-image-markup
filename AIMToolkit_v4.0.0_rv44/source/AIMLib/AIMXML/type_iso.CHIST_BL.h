/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_BL
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_BL

#include "type_iso.CLIST_BL.h"


namespace AIMXML
{

namespace iso
{	

class CHIST_BL : public ::AIMXML::iso::CLIST_BL
{
public:
	AIMXML_EXPORT CHIST_BL(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CHIST_BL(CHIST_BL const& init);
	void operator=(CHIST_BL const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CHIST_BL); }
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_BL
