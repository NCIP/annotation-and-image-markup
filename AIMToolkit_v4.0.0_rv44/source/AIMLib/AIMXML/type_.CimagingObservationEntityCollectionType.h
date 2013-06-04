/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CimagingObservationEntityCollectionType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CimagingObservationEntityCollectionType



namespace AIMXML
{

class CimagingObservationEntityCollectionType : public TypeBase
{
public:
	AIMXML_EXPORT CimagingObservationEntityCollectionType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CimagingObservationEntityCollectionType(CimagingObservationEntityCollectionType const& init);
	void operator=(CimagingObservationEntityCollectionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CimagingObservationEntityCollectionType); }
	MemberElement<CImagingObservationEntity, _altova_mi_altova_CimagingObservationEntityCollectionType_altova_ImagingObservationEntity> ImagingObservationEntity;
	struct ImagingObservationEntity { typedef Iterator<CImagingObservationEntity> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CimagingObservationEntityCollectionType
