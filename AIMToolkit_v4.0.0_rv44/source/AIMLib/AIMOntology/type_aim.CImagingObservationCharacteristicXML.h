#ifndef _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CImagingObservationCharacteristicXML
#define _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CImagingObservationCharacteristicXML



namespace AIMOntology
{

namespace aim
{	

class CImagingObservationCharacteristicXML : public TypeBase
{
public:
	AIMOntology_EXPORT CImagingObservationCharacteristicXML(xercesc::DOMNode* const& init);
	AIMOntology_EXPORT CImagingObservationCharacteristicXML(CImagingObservationCharacteristicXML const& init);
	void operator=(CImagingObservationCharacteristicXML const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_aim_altova_CImagingObservationCharacteristicXML); }
	MemberElement<xs::CstringType, _altova_mi_aim_altova_CImagingObservationCharacteristicXML_altova_codeMeaning> codeMeaning;
	struct codeMeaning { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_aim_altova_CImagingObservationCharacteristicXML_altova_codingSchemeDesignator> codingSchemeDesignator;
	struct codingSchemeDesignator { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_aim_altova_CImagingObservationCharacteristicXML_altova_codeValue> codeValue;
	struct codeValue { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_aim_altova_CImagingObservationCharacteristicXML_altova_comment> comment;
	struct comment { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_aim_altova_CImagingObservationCharacteristicXML_altova_relationship> relationship;
	struct relationship { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<aim::CrelatedImagingObservationCharacteristicXMLType, _altova_mi_aim_altova_CImagingObservationCharacteristicXML_altova_relatedImagingObservationCharacteristicXML> relatedImagingObservationCharacteristicXML;
	struct relatedImagingObservationCharacteristicXML { typedef Iterator<aim::CrelatedImagingObservationCharacteristicXMLType> iterator; };
	AIMOntology_EXPORT void SetXsiType();
};



} // namespace aim

}	// namespace AIMOntology

#endif // _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CImagingObservationCharacteristicXML
