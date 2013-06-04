/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_MO
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_MO

#include "type_iso.CLIST_MO.h"


namespace AIMXML
{

namespace iso
{	

class CHIST_MO : public ::AIMXML::iso::CLIST_MO
{
public:
	AIMXML_EXPORT CHIST_MO(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CHIST_MO(CHIST_MO const& init);
	void operator=(CHIST_MO const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CHIST_MO); }
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_MO
