/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQTY
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQTY

#include "type_iso.CANY.h"


namespace AIMXML
{

namespace iso
{	

class CQTY : public ::AIMXML::iso::CANY
{
public:
	AIMXML_EXPORT CQTY(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CQTY(CQTY const& init);
	void operator=(CQTY const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_iso_altova_CQTY); }

	MemberAttribute<string_type,_altova_mi_iso_altova_CQTY_altova_expressionLanguage, 0, 0> expressionLanguage;	// expressionLanguage CCode
	MemberAttribute<string_type,_altova_mi_iso_altova_CQTY_altova_uncertaintyType, 0, 9> uncertaintyType;	// uncertaintyType CUncertaintyType
	MemberElement<iso::CED, _altova_mi_iso_altova_CQTY_altova_expression> expression;
	struct expression { typedef Iterator<iso::CED> iterator; };
	MemberElement<iso::CED_Text, _altova_mi_iso_altova_CQTY_altova_originalText> originalText;
	struct originalText { typedef Iterator<iso::CED_Text> iterator; };
	MemberElement<iso::CQTY, _altova_mi_iso_altova_CQTY_altova_uncertainty> uncertainty;
	struct uncertainty { typedef Iterator<iso::CQTY> iterator; };
	AIMXML_EXPORT void SetXsiType();
};



} // namespace iso

}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA_iso_ALTOVA_CQTY
