/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_AD
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_AD

#include "type_iso.CLIST_AD.h"


namespace AIMXML
{

namespace iso
{	

class CHIST_AD : public ::AIMXML::iso::CLIST_AD
{
public:
	AIMXML_EXPORT CHIST_AD(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CHIST_AD(CHIST_AD const& init);
	void operator=(CHIST_AD const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CHIST_AD); }
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_AD
