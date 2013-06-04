/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_TS_Date_Full
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_TS_Date_Full

#include "type_iso.CCOLL_TS_Date_Full.h"


namespace AIMXML
{

namespace iso
{	

class CBAG_TS_Date_Full : public ::AIMXML::iso::CCOLL_TS_Date_Full
{
public:
	AIMXML_EXPORT CBAG_TS_Date_Full(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CBAG_TS_Date_Full(CBAG_TS_Date_Full const& init);
	void operator=(CBAG_TS_Date_Full const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CBAG_TS_Date_Full); }
	MemberElement<iso::CTS_Date_Full, _altova_mi_iso_altova_CBAG_TS_Date_Full_altova_item> item;
	struct item { typedef Iterator<iso::CTS_Date_Full> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_TS_Date_Full
