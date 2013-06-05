/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSS_PQ_Time
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSS_PQ_Time

#include "type_iso.CQSET_PQ_Time.h"


namespace AIMXML
{

namespace iso
{	

class CQSS_PQ_Time : public ::AIMXML::iso::CQSET_PQ_Time
{
public:
	AIMXML_EXPORT CQSS_PQ_Time(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CQSS_PQ_Time(CQSS_PQ_Time const& init);
	void operator=(CQSS_PQ_Time const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CQSS_PQ_Time); }
	MemberElement<iso::CPQ_Time, _altova_mi_iso_altova_CQSS_PQ_Time_altova_term> term;
	struct term { typedef Iterator<iso::CPQ_Time> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSS_PQ_Time
