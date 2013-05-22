/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/
#ifndef _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CAnnotationDescriptionXML
#define _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CAnnotationDescriptionXML



namespace AIMOntology
{

namespace aim
{	

class CAnnotationDescriptionXML : public TypeBase
{
public:
	AIMOntology_EXPORT CAnnotationDescriptionXML(xercesc::DOMNode* const& init);
	AIMOntology_EXPORT CAnnotationDescriptionXML(CAnnotationDescriptionXML const& init);
	void operator=(CAnnotationDescriptionXML const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_aim_altova_CAnnotationDescriptionXML); }
	MemberElement<aim::CanatomicEntityCollectionXMLType, _altova_mi_aim_altova_CAnnotationDescriptionXML_altova_anatomicEntityCollectionXML> anatomicEntityCollectionXML;
	struct anatomicEntityCollectionXML { typedef Iterator<aim::CanatomicEntityCollectionXMLType> iterator; };
	MemberElement<aim::CimagingObservationCollectionXMLType, _altova_mi_aim_altova_CAnnotationDescriptionXML_altova_imagingObservationCollectionXML> imagingObservationCollectionXML;
	struct imagingObservationCollectionXML { typedef Iterator<aim::CimagingObservationCollectionXMLType> iterator; };
	AIMOntology_EXPORT void SetXsiType();
};



} // namespace aim

}	// namespace AIMOntology

#endif // _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CAnnotationDescriptionXML
