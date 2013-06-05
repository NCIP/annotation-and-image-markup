/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CST
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CST

#include "type_iso.CANY.h"


namespace AIMXML
{

namespace iso
{	

class CST : public ::AIMXML::iso::CANY
{
public:
	AIMXML_EXPORT CST(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CST(CST const& init);
	void operator=(CST const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CST); }

	MemberAttribute<string_type,_altova_mi_iso_altova_CST_altova_value2, 0, 0> value2;	// value Cstring

	MemberAttribute<string_type,_altova_mi_iso_altova_CST_altova_language, 0, 0> language;	// language CCode
	MemberElement<iso::CST, _altova_mi_iso_altova_CST_altova_translation> translation;
	struct translation { typedef Iterator<iso::CST> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CST
