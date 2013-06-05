/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_EN
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_EN

#include "type_iso.CLIST_EN.h"


namespace AIMXML
{

namespace iso
{	

class CHIST_EN : public ::AIMXML::iso::CLIST_EN
{
public:
	AIMXML_EXPORT CHIST_EN(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CHIST_EN(CHIST_EN const& init);
	void operator=(CHIST_EN const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CHIST_EN); }
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_EN
