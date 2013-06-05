/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_TS_DateTime_Full
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_TS_DateTime_Full

#include "type_iso.CCOLL_TS_DateTime_Full.h"


namespace AIMXML
{

namespace iso
{	

class CDSET_TS_DateTime_Full : public ::AIMXML::iso::CCOLL_TS_DateTime_Full
{
public:
	AIMXML_EXPORT CDSET_TS_DateTime_Full(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CDSET_TS_DateTime_Full(CDSET_TS_DateTime_Full const& init);
	void operator=(CDSET_TS_DateTime_Full const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CDSET_TS_DateTime_Full); }
	MemberElement<iso::CTS_DateTime_Full, _altova_mi_iso_altova_CDSET_TS_DateTime_Full_altova_item> item;
	struct item { typedef Iterator<iso::CTS_DateTime_Full> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CDSET_TS_DateTime_Full
