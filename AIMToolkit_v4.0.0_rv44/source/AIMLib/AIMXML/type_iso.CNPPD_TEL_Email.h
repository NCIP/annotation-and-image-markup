/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CNPPD_TEL_Email
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CNPPD_TEL_Email

#include "type_iso.CANY.h"


namespace AIMXML
{

namespace iso
{	

class CNPPD_TEL_Email : public ::AIMXML::iso::CANY
{
public:
	AIMXML_EXPORT CNPPD_TEL_Email(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CNPPD_TEL_Email(CNPPD_TEL_Email const& init);
	void operator=(CNPPD_TEL_Email const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CNPPD_TEL_Email); }
	MemberElement<iso::CUVP_TEL_Email, _altova_mi_iso_altova_CNPPD_TEL_Email_altova_item> item;
	struct item { typedef Iterator<iso::CUVP_TEL_Email> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CNPPD_TEL_Email
