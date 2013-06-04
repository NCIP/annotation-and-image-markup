/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CimagingPhysicalEntityCollectionType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CimagingPhysicalEntityCollectionType



namespace AIMXML
{

class CimagingPhysicalEntityCollectionType : public TypeBase
{
public:
	AIMXML_EXPORT CimagingPhysicalEntityCollectionType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CimagingPhysicalEntityCollectionType(CimagingPhysicalEntityCollectionType const& init);
	void operator=(CimagingPhysicalEntityCollectionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CimagingPhysicalEntityCollectionType); }
	MemberElement<CImagingPhysicalEntity, _altova_mi_altova_CimagingPhysicalEntityCollectionType_altova_ImagingPhysicalEntity> ImagingPhysicalEntity;
	struct ImagingPhysicalEntity { typedef Iterator<CImagingPhysicalEntity> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CimagingPhysicalEntityCollectionType
