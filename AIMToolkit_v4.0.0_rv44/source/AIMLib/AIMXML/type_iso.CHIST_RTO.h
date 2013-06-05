/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_RTO
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_RTO

#include "type_iso.CLIST_RTO.h"


namespace AIMXML
{

namespace iso
{	

class CHIST_RTO : public ::AIMXML::iso::CLIST_RTO
{
public:
	AIMXML_EXPORT CHIST_RTO(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CHIST_RTO(CHIST_RTO const& init);
	void operator=(CHIST_RTO const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CHIST_RTO); }
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_RTO
