/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/
#ifndef _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CimagingObservationCharacteristicCollectionXMLType
#define _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CimagingObservationCharacteristicCollectionXMLType



namespace AIMOntology
{

namespace aim
{	

class CimagingObservationCharacteristicCollectionXMLType : public TypeBase
{
public:
	AIMOntology_EXPORT CimagingObservationCharacteristicCollectionXMLType(xercesc::DOMNode* const& init);
	AIMOntology_EXPORT CimagingObservationCharacteristicCollectionXMLType(CimagingObservationCharacteristicCollectionXMLType const& init);
	void operator=(CimagingObservationCharacteristicCollectionXMLType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_aim_altova_CimagingObservationCharacteristicCollectionXMLType); }
	MemberElement<aim::CImagingObservationCharacteristicXML, _altova_mi_aim_altova_CimagingObservationCharacteristicCollectionXMLType_altova_ImagingObservationCharacteristicXML> ImagingObservationCharacteristicXML;
	struct ImagingObservationCharacteristicXML { typedef Iterator<aim::CImagingObservationCharacteristicXML> iterator; };
};



} // namespace aim

}	// namespace AIMOntology

#endif // _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CimagingObservationCharacteristicCollectionXMLType
