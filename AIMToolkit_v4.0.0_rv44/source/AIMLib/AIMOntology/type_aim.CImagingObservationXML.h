/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/
#ifndef _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CImagingObservationXML
#define _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CImagingObservationXML



namespace AIMOntology
{

namespace aim
{	

class CImagingObservationXML : public TypeBase
{
public:
	AIMOntology_EXPORT CImagingObservationXML(xercesc::DOMNode* const& init);
	AIMOntology_EXPORT CImagingObservationXML(CImagingObservationXML const& init);
	void operator=(CImagingObservationXML const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_aim_altova_CImagingObservationXML); }
	MemberElement<xs::CstringType, _altova_mi_aim_altova_CImagingObservationXML_altova_codeMeaning> codeMeaning;
	struct codeMeaning { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_aim_altova_CImagingObservationXML_altova_codingSchemeDesignator> codingSchemeDesignator;
	struct codingSchemeDesignator { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_aim_altova_CImagingObservationXML_altova_codeValue> codeValue;
	struct codeValue { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_aim_altova_CImagingObservationXML_altova_comment> comment;
	struct comment { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_aim_altova_CImagingObservationXML_altova_relationship> relationship;
	struct relationship { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<aim::CrelatedImagingObservationXMLType, _altova_mi_aim_altova_CImagingObservationXML_altova_relatedImagingObservationXML> relatedImagingObservationXML;
	struct relatedImagingObservationXML { typedef Iterator<aim::CrelatedImagingObservationXMLType> iterator; };
	MemberElement<aim::CimagingObservationCharacteristicCollectionXMLType, _altova_mi_aim_altova_CImagingObservationXML_altova_imagingObservationCharacteristicCollectionXML> imagingObservationCharacteristicCollectionXML;
	struct imagingObservationCharacteristicCollectionXML { typedef Iterator<aim::CimagingObservationCharacteristicCollectionXMLType> iterator; };
	AIMOntology_EXPORT void SetXsiType();
};



} // namespace aim

}	// namespace AIMOntology

#endif // _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CImagingObservationXML
