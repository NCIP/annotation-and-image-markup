/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CCOLL_TS_Birth
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CCOLL_TS_Birth

#include "type_iso.CANY.h"


namespace AIMXML
{

namespace iso
{	

class CCOLL_TS_Birth : public ::AIMXML::iso::CANY
{
public:
	AIMXML_EXPORT CCOLL_TS_Birth(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CCOLL_TS_Birth(CCOLL_TS_Birth const& init);
	void operator=(CCOLL_TS_Birth const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CCOLL_TS_Birth); }
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CCOLL_TS_Birth
