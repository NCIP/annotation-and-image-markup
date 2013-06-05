/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_ED_Signature
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_ED_Signature

#include "type_iso.CLIST_ED_Signature.h"


namespace AIMXML
{

namespace iso
{	

class CHIST_ED_Signature : public ::AIMXML::iso::CLIST_ED_Signature
{
public:
	AIMXML_EXPORT CHIST_ED_Signature(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CHIST_ED_Signature(CHIST_ED_Signature const& init);
	void operator=(CHIST_ED_Signature const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CHIST_ED_Signature); }
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CHIST_ED_Signature
