/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSET_TS_Birth
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSET_TS_Birth

#include "type_iso.CANY.h"


namespace AIMXML
{

namespace iso
{	

class CQSET_TS_Birth : public ::AIMXML::iso::CANY
{
public:
	AIMXML_EXPORT CQSET_TS_Birth(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CQSET_TS_Birth(CQSET_TS_Birth const& init);
	void operator=(CQSET_TS_Birth const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CQSET_TS_Birth); }
	MemberElement<iso::CED_Text, _altova_mi_iso_altova_CQSET_TS_Birth_altova_originalText> originalText;
	struct originalText { typedef Iterator<iso::CED_Text> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQSET_TS_Birth
