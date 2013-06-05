/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_CS
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_CS

#include "type_iso.CLIST_CS.h"


namespace AIMXML
{

namespace iso
{	

class CHIST_CS : public ::AIMXML::iso::CLIST_CS
{
public:
	AIMXML_EXPORT CHIST_CS(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CHIST_CS(CHIST_CS const& init);
	void operator=(CHIST_CS const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CHIST_CS); }
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_CS
