/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_TEL_Url
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_TEL_Url

#include "type_iso.CCOLL_TEL_Url.h"


namespace AIMXML
{

namespace iso
{	

class CBAG_TEL_Url : public ::AIMXML::iso::CCOLL_TEL_Url
{
public:
	AIMXML_EXPORT CBAG_TEL_Url(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CBAG_TEL_Url(CBAG_TEL_Url const& init);
	void operator=(CBAG_TEL_Url const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CBAG_TEL_Url); }
	MemberElement<iso::CTEL_Url, _altova_mi_iso_altova_CBAG_TEL_Url_altova_item> item;
	struct item { typedef Iterator<iso::CTEL_Url> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CBAG_TEL_Url
