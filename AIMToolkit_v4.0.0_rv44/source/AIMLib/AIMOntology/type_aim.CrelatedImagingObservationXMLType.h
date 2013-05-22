/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/
#ifndef _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CrelatedImagingObservationXMLType
#define _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CrelatedImagingObservationXMLType



namespace AIMOntology
{

namespace aim
{	

class CrelatedImagingObservationXMLType : public TypeBase
{
public:
	AIMOntology_EXPORT CrelatedImagingObservationXMLType(xercesc::DOMNode* const& init);
	AIMOntology_EXPORT CrelatedImagingObservationXMLType(CrelatedImagingObservationXMLType const& init);
	void operator=(CrelatedImagingObservationXMLType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_aim_altova_CrelatedImagingObservationXMLType); }
	MemberElement<aim::CImagingObservationXML, _altova_mi_aim_altova_CrelatedImagingObservationXMLType_altova_ImagingObservationXML> ImagingObservationXML;
	struct ImagingObservationXML { typedef Iterator<aim::CImagingObservationXML> iterator; };
};



} // namespace aim

}	// namespace AIMOntology

#endif // _ALTOVA_INCLUDED_AIMOntology_ALTOVA_aim_ALTOVA_CrelatedImagingObservationXMLType
