/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_ClesionObservationEntityCollectionType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_ClesionObservationEntityCollectionType



namespace AIMXML
{

class ClesionObservationEntityCollectionType : public TypeBase
{
public:
	AIMXML_EXPORT ClesionObservationEntityCollectionType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT ClesionObservationEntityCollectionType(ClesionObservationEntityCollectionType const& init);
	void operator=(ClesionObservationEntityCollectionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_ClesionObservationEntityCollectionType); }
	MemberElement<CLesionObservationEntity, _altova_mi_altova_ClesionObservationEntityCollectionType_altova_LesionObservationEntity> LesionObservationEntity;
	struct LesionObservationEntity { typedef Iterator<CLesionObservationEntity> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_ClesionObservationEntityCollectionType
