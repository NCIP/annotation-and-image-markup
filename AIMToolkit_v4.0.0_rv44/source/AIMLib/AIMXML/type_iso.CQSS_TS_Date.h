/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSS_TS_Date
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSS_TS_Date

#include "type_iso.CQSET_TS_Date.h"


namespace AIMXML
{

namespace iso
{	

class CQSS_TS_Date : public ::AIMXML::iso::CQSET_TS_Date
{
public:
	AIMXML_EXPORT CQSS_TS_Date(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CQSS_TS_Date(CQSS_TS_Date const& init);
	void operator=(CQSS_TS_Date const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CQSS_TS_Date); }
	MemberElement<iso::CTS_Date, _altova_mi_iso_altova_CQSS_TS_Date_altova_term> term;
	struct term { typedef Iterator<iso::CTS_Date> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSS_TS_Date
