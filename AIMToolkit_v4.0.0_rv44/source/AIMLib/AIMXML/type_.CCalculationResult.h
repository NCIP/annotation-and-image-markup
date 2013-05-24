/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

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
	MemberAttribute<string_type,_altova_mi_altova_CCalculationResult_altova_type, 0, 6> type;	// type CCalculationResultIdentifier
	MemberElement<iso::CST, _altova_mi_altova_CCalculationResult_altova_unitOfMeasure> unitOfMeasure;
	struct unitOfMeasure { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CCD, _altova_mi_altova_CCalculationResult_altova_dataType> dataType;
	struct dataType { typedef Iterator<iso::CCD> iterator; };
	MemberElement<CdimensionCollectionType, _altova_mi_altova_CCalculationResult_altova_dimensionCollection> dimensionCollection;
	struct dimensionCollection { typedef Iterator<CdimensionCollectionType> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCalculationResult
