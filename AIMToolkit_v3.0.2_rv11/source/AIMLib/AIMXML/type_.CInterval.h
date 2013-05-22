/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CInterval
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CInterval

#include "type_.CCharacteristicQuantification.h"


namespace AIMXML
{

class CInterval : public ::AIMXML::CCharacteristicQuantification
{
public:
	AIMXML_EXPORT CInterval(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CInterval(CInterval const& init);
	void operator=(CInterval const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CInterval); }

	MemberAttribute<double,_altova_mi_altova_CInterval_altova_minValue, 0, 0> minValue;	// minValue Cdouble

	MemberAttribute<double,_altova_mi_altova_CInterval_altova_maxValue, 0, 0> maxValue;	// maxValue Cdouble
	MemberAttribute<string_type,_altova_mi_altova_CInterval_altova_minOperator, 0, 6> minOperator;	// minOperator CComparisonOperators

	MemberAttribute<string_type,_altova_mi_altova_CInterval_altova_ucumString, 0, 0> ucumString;	// ucumString Cstring
	MemberAttribute<string_type,_altova_mi_altova_CInterval_altova_maxOperator, 0, 6> maxOperator;	// maxOperator CComparisonOperators
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CInterval
