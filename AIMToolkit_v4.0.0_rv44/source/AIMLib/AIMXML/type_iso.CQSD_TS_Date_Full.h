/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSD_TS_Date_Full
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSD_TS_Date_Full

#include "type_iso.CQSET_TS_Date_Full.h"


namespace AIMXML
{

namespace iso
{	

class CQSD_TS_Date_Full : public ::AIMXML::iso::CQSET_TS_Date_Full
{
public:
	AIMXML_EXPORT CQSD_TS_Date_Full(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CQSD_TS_Date_Full(CQSD_TS_Date_Full const& init);
	void operator=(CQSD_TS_Date_Full const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CQSD_TS_Date_Full); }
	MemberElement<iso::CQSET_TS_Date_Full, _altova_mi_iso_altova_CQSD_TS_Date_Full_altova_first> first;
	struct first { typedef Iterator<iso::CQSET_TS_Date_Full> iterator; };
	MemberElement<iso::CQSET_TS_Date_Full, _altova_mi_iso_altova_CQSD_TS_Date_Full_altova_second> second;
	struct second { typedef Iterator<iso::CQSET_TS_Date_Full> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSD_TS_Date_Full
