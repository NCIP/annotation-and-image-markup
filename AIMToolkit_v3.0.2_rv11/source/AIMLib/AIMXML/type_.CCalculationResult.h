/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCalculationResult
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCalculationResult



namespace AIMXML
{

class CCalculationResult : public TypeBase
{
public:
	AIMXML_EXPORT CCalculationResult(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CCalculationResult(CCalculationResult const& init);
	void operator=(CCalculationResult const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CCalculationResult); }

	MemberAttribute<__int64,_altova_mi_altova_CCalculationResult_altova_cagridId, 0, 0> cagridId;	// cagridId Cinteger
	MemberAttribute<string_type,_altova_mi_altova_CCalculationResult_altova_type, 0, 5> type;	// type CCalculationResultIdentifier

	MemberAttribute<__int64,_altova_mi_altova_CCalculationResult_altova_numberOfDimensions, 0, 0> numberOfDimensions;	// numberOfDimensions Cinteger

	MemberAttribute<string_type,_altova_mi_altova_CCalculationResult_altova_unitOfMeasure, 0, 0> unitOfMeasure;	// unitOfMeasure Cstring
	MemberElement<CcalculationDataCollectionType, _altova_mi_altova_CCalculationResult_altova_calculationDataCollection> calculationDataCollection;
	struct calculationDataCollection { typedef Iterator<CcalculationDataCollectionType> iterator; };
	MemberElement<CdimensionCollectionType, _altova_mi_altova_CCalculationResult_altova_dimensionCollection> dimensionCollection;
	struct dimensionCollection { typedef Iterator<CdimensionCollectionType> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCalculationResult
