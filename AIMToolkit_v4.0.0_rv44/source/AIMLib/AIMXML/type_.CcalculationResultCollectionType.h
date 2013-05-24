/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CcalculationResultCollectionType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CcalculationResultCollectionType



namespace AIMXML
{

class CcalculationResultCollectionType : public TypeBase
{
public:
	AIMXML_EXPORT CcalculationResultCollectionType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CcalculationResultCollectionType(CcalculationResultCollectionType const& init);
	void operator=(CcalculationResultCollectionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CcalculationResultCollectionType); }
	MemberElement<CCalculationResult, _altova_mi_altova_CcalculationResultCollectionType_altova_CalculationResult> CalculationResult;
	struct CalculationResult { typedef Iterator<CCalculationResult> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CcalculationResultCollectionType
