/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CNumerical
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CNumerical

#include "type_.CCharacteristicQuantification.h"


namespace AIMXML
{

class CNumerical : public ::AIMXML::CCharacteristicQuantification
{
public:
	AIMXML_EXPORT CNumerical(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CNumerical(CNumerical const& init);
	void operator=(CNumerical const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CNumerical); }
	MemberAttribute<string_type,_altova_mi_altova_CNumerical_altova_operator2, 0, 6> operator2;	// operator CComparisonOperator
	MemberElement<iso::CST, _altova_mi_altova_CNumerical_altova_ucumString> ucumString;
	struct ucumString { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CREAL, _altova_mi_altova_CNumerical_altova_value2> value2;
	struct value2 { typedef Iterator<iso::CREAL> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CNumerical
