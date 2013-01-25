#ifndef _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CrelatedImagingObservationCharacteristicXMLType
#define _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CrelatedImagingObservationCharacteristicXMLType



namespace AIMOntology
{

namespace aim
{	

class CrelatedImagingObservationCharacteristicXMLType : public TypeBase
{
public:
	AIMOntology_EXPORT CrelatedImagingObservationCharacteristicXMLType(xercesc::DOMNode* const& init);
	AIMOntology_EXPORT CrelatedImagingObservationCharacteristicXMLType(CrelatedImagingObservationCharacteristicXMLType const& init);
	void operator=(CrelatedImagingObservationCharacteristicXMLType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_aim_altova_CrelatedImagingObservationCharacteristicXMLType); }
	MemberElement<aim::CImagingObservationCharacteristicXML, _altova_mi_aim_altova_CrelatedImagingObservationCharacteristicXMLType_altova_ImagingObservationCharacteristicXML> ImagingObservationCharacteristicXML;
	struct ImagingObservationCharacteristicXML { typedef Iterator<aim::CImagingObservationCharacteristicXML> iterator; };
};



} // namespace aim

}	// namespace AIMOntology

#endif // _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CrelatedImagingObservationCharacteristicXMLType
