/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_TS_Date_Full
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_TS_Date_Full

#include "type_iso.CLIST_TS_Date_Full.h"


namespace AIMXML
{

namespace iso
{	

class CHIST_TS_Date_Full : public ::AIMXML::iso::CLIST_TS_Date_Full
{
public:
	AIMXML_EXPORT CHIST_TS_Date_Full(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CHIST_TS_Date_Full(CHIST_TS_Date_Full const& init);
	void operator=(CHIST_TS_Date_Full const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CHIST_TS_Date_Full); }
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_TS_Date_Full
