/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_TS_Birth
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_TS_Birth

#include "type_iso.CLIST_TS_Birth.h"


namespace AIMXML
{

namespace iso
{	

class CHIST_TS_Birth : public ::AIMXML::iso::CLIST_TS_Birth
{
public:
	AIMXML_EXPORT CHIST_TS_Birth(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CHIST_TS_Birth(CHIST_TS_Birth const& init);
	void operator=(CHIST_TS_Birth const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CHIST_TS_Birth); }
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_TS_Birth
