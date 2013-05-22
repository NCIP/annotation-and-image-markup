/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CsegmentationEntityCollectionType
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CsegmentationEntityCollectionType



namespace AIMXML
{

class CsegmentationEntityCollectionType : public TypeBase
{
public:
	AIMXML_EXPORT CsegmentationEntityCollectionType(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CsegmentationEntityCollectionType(CsegmentationEntityCollectionType const& init);
	void operator=(CsegmentationEntityCollectionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CsegmentationEntityCollectionType); }
	MemberElement<CSegmentationEntity, _altova_mi_altova_CsegmentationEntityCollectionType_altova_SegmentationEntity> SegmentationEntity;
	struct SegmentationEntity { typedef Iterator<CSegmentationEntity> iterator; };
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CsegmentationEntityCollectionType
