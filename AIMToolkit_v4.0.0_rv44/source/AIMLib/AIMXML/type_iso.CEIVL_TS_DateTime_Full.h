/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CEIVL_TS_DateTime_Full
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CEIVL_TS_DateTime_Full

#include "type_iso.CQSET_TS_DateTime_Full.h"


namespace AIMXML
{

namespace iso
{	

class CEIVL_TS_DateTime_Full : public ::AIMXML::iso::CQSET_TS_DateTime_Full
{
public:
	AIMXML_EXPORT CEIVL_TS_DateTime_Full(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CEIVL_TS_DateTime_Full(CEIVL_TS_DateTime_Full const& init);
	void operator=(CEIVL_TS_DateTime_Full const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CEIVL_TS_DateTime_Full); }
	MemberAttribute<string_type,_altova_mi_iso_altova_CEIVL_TS_DateTime_Full_altova_event, 0, 5> event;	// event CTimingEvent
	MemberElement<iso::CIVL_PQ, _altova_mi_iso_altova_CEIVL_TS_DateTime_Full_altova_offset> offset;
	struct offset { typedef Iterator<iso::CIVL_PQ> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CEIVL_TS_DateTime_Full
