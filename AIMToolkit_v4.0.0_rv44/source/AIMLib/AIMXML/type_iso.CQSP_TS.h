/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSP_TS
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSP_TS

#include "type_iso.CQSET_TS.h"


namespace AIMXML
{

namespace iso
{	

class CQSP_TS : public ::AIMXML::iso::CQSET_TS
{
public:
	AIMXML_EXPORT CQSP_TS(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CQSP_TS(CQSP_TS const& init);
	void operator=(CQSP_TS const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CQSP_TS); }
	MemberElement<iso::CQSET_TS, _altova_mi_iso_altova_CQSP_TS_altova_first> first;
	struct first { typedef Iterator<iso::CQSET_TS> iterator; };
	MemberElement<iso::CQSET_TS, _altova_mi_iso_altova_CQSP_TS_altova_second> second;
	struct second { typedef Iterator<iso::CQSET_TS> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSP_TS
