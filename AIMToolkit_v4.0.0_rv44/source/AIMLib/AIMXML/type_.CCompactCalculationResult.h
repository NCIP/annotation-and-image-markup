/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCompactCalculationResult
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCompactCalculationResult

#include "type_.CCalculationResult.h"


namespace AIMXML
{

class CCompactCalculationResult : public ::AIMXML::CCalculationResult
{
public:
	AIMXML_EXPORT CCompactCalculationResult(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CCompactCalculationResult(CCompactCalculationResult const& init);
	void operator=(CCompactCalculationResult const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CCompactCalculationResult); }
	MemberElement<iso::CST, _altova_mi_altova_CCompactCalculationResult_altova_value2> value2;
	struct value2 { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CCD, _altova_mi_altova_CCompactCalculationResult_altova_encoding> encoding;
	struct encoding { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CCD, _altova_mi_altova_CCompactCalculationResult_altova_compression> compression;
	struct compression { typedef Iterator<iso::CCD> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCompactCalculationResult
