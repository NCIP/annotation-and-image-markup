/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_INT_NonNeg
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_INT_NonNeg

#include "type_iso.CLIST_INT_NonNeg.h"


namespace AIMXML
{

namespace iso
{	

class CHIST_INT_NonNeg : public ::AIMXML::iso::CLIST_INT_NonNeg
{
public:
	AIMXML_EXPORT CHIST_INT_NonNeg(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CHIST_INT_NonNeg(CHIST_INT_NonNeg const& init);
	void operator=(CHIST_INT_NonNeg const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CHIST_INT_NonNeg); }
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_INT_NonNeg
