/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CimagingObservationCollectionType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CimagingObservationCollectionType



namespace AIMXML
{

class CimagingObservationCollectionType : public TypeBase
{
public:
	AIMXML_EXPORT CimagingObservationCollectionType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CimagingObservationCollectionType(CimagingObservationCollectionType const& init);
	void operator=(CimagingObservationCollectionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CimagingObservationCollectionType); }
	MemberElement<CImagingObservation, _altova_mi_altova_CimagingObservationCollectionType_altova_ImagingObservation> ImagingObservation;
	struct ImagingObservation { typedef Iterator<CImagingObservation> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CimagingObservationCollectionType
