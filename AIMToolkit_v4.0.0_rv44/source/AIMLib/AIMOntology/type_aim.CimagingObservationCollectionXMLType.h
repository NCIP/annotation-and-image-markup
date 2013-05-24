#ifndef _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CimagingObservationCollectionXMLType
#define _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CimagingObservationCollectionXMLType



namespace AIMOntology
{

namespace aim
{	

class CimagingObservationCollectionXMLType : public TypeBase
{
public:
	AIMOntology_EXPORT CimagingObservationCollectionXMLType(xercesc::DOMNode* const& init);
	AIMOntology_EXPORT CimagingObservationCollectionXMLType(CimagingObservationCollectionXMLType const& init);
	void operator=(CimagingObservationCollectionXMLType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_aim_altova_CimagingObservationCollectionXMLType); }
	MemberElement<aim::CImagingObservationXML, _altova_mi_aim_altova_CimagingObservationCollectionXMLType_altova_ImagingObservationXML> ImagingObservationXML;
	struct ImagingObservationXML { typedef Iterator<aim::CImagingObservationXML> iterator; };
};



} // namespace aim

}	// namespace AIMOntology

#endif // _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CimagingObservationCollectionXMLType
