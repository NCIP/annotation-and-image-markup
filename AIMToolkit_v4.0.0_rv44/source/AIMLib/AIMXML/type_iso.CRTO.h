/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CRTO
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CRTO

#include "type_iso.CQTY.h"


namespace AIMXML
{

namespace iso
{	

class CRTO : public ::AIMXML::iso::CQTY
{
public:
	AIMXML_EXPORT CRTO(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CRTO(CRTO const& init);
	void operator=(CRTO const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CRTO); }
	MemberElement<iso::CQTY, _altova_mi_iso_altova_CRTO_altova_numerator> numerator;
	struct numerator { typedef Iterator<iso::CQTY> iterator; };
	MemberElement<iso::CQTY, _altova_mi_iso_altova_CRTO_altova_denominator> denominator;
	struct denominator { typedef Iterator<iso::CQTY> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CRTO
