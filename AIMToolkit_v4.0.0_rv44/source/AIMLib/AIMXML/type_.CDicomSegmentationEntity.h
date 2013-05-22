/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CDicomSegmentationEntity
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CDicomSegmentationEntity

#include "type_.CSegmentationEntity.h"


namespace AIMXML
{

class CDicomSegmentationEntity : public ::AIMXML::CSegmentationEntity
{
public:
	AIMXML_EXPORT CDicomSegmentationEntity(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CDicomSegmentationEntity(CDicomSegmentationEntity const& init);
	void operator=(CDicomSegmentationEntity const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CDicomSegmentationEntity); }
	MemberElement<iso::CII, _altova_mi_altova_CDicomSegmentationEntity_altova_sopInstanceUid> sopInstanceUid;
	struct sopInstanceUid { typedef Iterator<iso::CII> iterator; };
	MemberElement<iso::CII, _altova_mi_altova_CDicomSegmentationEntity_altova_sopClassUid> sopClassUid;
	struct sopClassUid { typedef Iterator<iso::CII> iterator; };
	MemberElement<iso::CII, _altova_mi_altova_CDicomSegmentationEntity_altova_referencedSopInstanceUid> referencedSopInstanceUid;
	struct referencedSopInstanceUid { typedef Iterator<iso::CII> iterator; };
	MemberElement<iso::CINT, _altova_mi_altova_CDicomSegmentationEntity_altova_segmentNumber> segmentNumber;
	struct segmentNumber { typedef Iterator<iso::CINT> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CDicomSegmentationEntity
