/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSS_TS
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSS_TS

#include "type_iso.CQSET_TS.h"


namespace AIMXML
{

namespace iso
{	

class CQSS_TS : public ::AIMXML::iso::CQSET_TS
{
public:
	AIMXML_EXPORT CQSS_TS(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CQSS_TS(CQSS_TS const& init);
	void operator=(CQSS_TS const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CQSS_TS); }
	MemberElement<iso::CTS, _altova_mi_iso_altova_CQSS_TS_altova_term> term;
	struct term { typedef Iterator<iso::CTS> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSS_TS
