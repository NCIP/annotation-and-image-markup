/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCalculation
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCalculation



namespace AIMXML
{

class CCalculation : public TypeBase
{
public:
	AIMXML_EXPORT CCalculation(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CCalculation(CCalculation const& init);
	void operator=(CCalculation const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CCalculation); }

	MemberAttribute<__int64,_altova_mi_altova_CCalculation_altova_cagridId, 0, 0> cagridId;	// cagridId Cinteger

	MemberAttribute<string_type,_altova_mi_altova_CCalculation_altova_uid, 0, 0> uid;	// uid Cstring

	MemberAttribute<string_type,_altova_mi_altova_CCalculation_altova_description, 0, 0> description;	// description Cstring

	MemberAttribute<string_type,_altova_mi_altova_CCalculation_altova_mathML, 0, 0> mathML;	// mathML Cstring

	MemberAttribute<string_type,_altova_mi_altova_CCalculation_altova_codeValue, 0, 0> codeValue;	// codeValue Cstring

	MemberAttribute<string_type,_altova_mi_altova_CCalculation_altova_codeMeaning, 0, 0> codeMeaning;	// codeMeaning Cstring

	MemberAttribute<string_type,_altova_mi_altova_CCalculation_altova_codingSchemeDesignator, 0, 0> codingSchemeDesignator;	// codingSchemeDesignator Cstring

	MemberAttribute<string_type,_altova_mi_altova_CCalculation_altova_codingSchemeVersion, 0, 0> codingSchemeVersion;	// codingSchemeVersion Cstring

	MemberAttribute<string_type,_altova_mi_altova_CCalculation_altova_algorithmName, 0, 0> algorithmName;	// algorithmName Cstring

	MemberAttribute<string_type,_altova_mi_altova_CCalculation_altova_algorithmVersion, 0, 0> algorithmVersion;	// algorithmVersion Cstring
	MemberElement<CreferencedCalculationCollectionType, _altova_mi_altova_CCalculation_altova_referencedCalculationCollection> referencedCalculationCollection;
	struct referencedCalculationCollection { typedef Iterator<CreferencedCalculationCollectionType> iterator; };
	MemberElement<CcalculationResultCollectionType, _altova_mi_altova_CCalculation_altova_calculationResultCollection> calculationResultCollection;
	struct calculationResultCollection { typedef Iterator<CcalculationResultCollectionType> iterator; };
	MemberElement<CreferencedGeometricShapeCollectionType, _altova_mi_altova_CCalculation_altova_referencedGeometricShapeCollection> referencedGeometricShapeCollection;
	struct referencedGeometricShapeCollection { typedef Iterator<CreferencedGeometricShapeCollectionType> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CCalculation
