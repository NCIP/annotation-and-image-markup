/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAnatomicEntityCharacteristic
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAnatomicEntityCharacteristic



namespace AIMXML
{

class CAnatomicEntityCharacteristic : public TypeBase
{
public:
	AIMXML_EXPORT CAnatomicEntityCharacteristic(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CAnatomicEntityCharacteristic(CAnatomicEntityCharacteristic const& init);
	void operator=(CAnatomicEntityCharacteristic const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CAnatomicEntityCharacteristic); }

	MemberAttribute<__int64,_altova_mi_altova_CAnatomicEntityCharacteristic_altova_cagridId, 0, 0> cagridId;	// cagridId Cinteger

	MemberAttribute<string_type,_altova_mi_altova_CAnatomicEntityCharacteristic_altova_codeValue, 0, 0> codeValue;	// codeValue Cstring

	MemberAttribute<string_type,_altova_mi_altova_CAnatomicEntityCharacteristic_altova_codeMeaning, 0, 0> codeMeaning;	// codeMeaning Cstring

	MemberAttribute<string_type,_altova_mi_altova_CAnatomicEntityCharacteristic_altova_codingSchemeDesignator, 0, 0> codingSchemeDesignator;	// codingSchemeDesignator Cstring

	MemberAttribute<string_type,_altova_mi_altova_CAnatomicEntityCharacteristic_altova_codingSchemeVersion, 0, 0> codingSchemeVersion;	// codingSchemeVersion Cstring

	MemberAttribute<double,_altova_mi_altova_CAnatomicEntityCharacteristic_altova_annotatorConfidence, 0, 0> annotatorConfidence;	// annotatorConfidence Cdouble

	MemberAttribute<string_type,_altova_mi_altova_CAnatomicEntityCharacteristic_altova_label, 0, 0> label;	// label Cstring
	MemberElement<CcharacteristicQuantificationCollectionType, _altova_mi_altova_CAnatomicEntityCharacteristic_altova_characteristicQuantificationCollection> characteristicQuantificationCollection;
	struct characteristicQuantificationCollection { typedef Iterator<CcharacteristicQuantificationCollectionType> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAnatomicEntityCharacteristic
