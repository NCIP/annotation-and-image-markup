/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSI_TS_DateTime
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSI_TS_DateTime

#include "type_iso.CQSET_TS_DateTime.h"


namespace AIMXML
{

namespace iso
{	

class CQSI_TS_DateTime : public ::AIMXML::iso::CQSET_TS_DateTime
{
public:
	AIMXML_EXPORT CQSI_TS_DateTime(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CQSI_TS_DateTime(CQSI_TS_DateTime const& init);
	void operator=(CQSI_TS_DateTime const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CQSI_TS_DateTime); }
	MemberElement<iso::CQSET_TS_DateTime, _altova_mi_iso_altova_CQSI_TS_DateTime_altova_term> term;
	struct term { typedef Iterator<iso::CQSET_TS_DateTime> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSI_TS_DateTime
