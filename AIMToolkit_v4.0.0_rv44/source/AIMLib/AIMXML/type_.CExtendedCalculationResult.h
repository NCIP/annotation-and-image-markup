/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CExtendedCalculationResult
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CExtendedCalculationResult

#include "type_.CCalculationResult.h"


namespace AIMXML
{

class CExtendedCalculationResult : public ::AIMXML::CCalculationResult
{
public:
	AIMXML_EXPORT CExtendedCalculationResult(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CExtendedCalculationResult(CExtendedCalculationResult const& init);
	void operator=(CExtendedCalculationResult const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CExtendedCalculationResult); }
	MemberElement<CcalculationDataCollectionType, _altova_mi_altova_CExtendedCalculationResult_altova_calculationDataCollection> calculationDataCollection;
	struct calculationDataCollection { typedef Iterator<CcalculationDataCollectionType> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CExtendedCalculationResult
