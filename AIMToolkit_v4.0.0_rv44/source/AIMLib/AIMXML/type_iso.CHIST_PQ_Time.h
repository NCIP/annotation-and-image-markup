/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_PQ_Time
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_PQ_Time

#include "type_iso.CLIST_PQ_Time.h"


namespace AIMXML
{

namespace iso
{	

class CHIST_PQ_Time : public ::AIMXML::iso::CLIST_PQ_Time
{
public:
	AIMXML_EXPORT CHIST_PQ_Time(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CHIST_PQ_Time(CHIST_PQ_Time const& init);
	void operator=(CHIST_PQ_Time const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CHIST_PQ_Time); }
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_PQ_Time
