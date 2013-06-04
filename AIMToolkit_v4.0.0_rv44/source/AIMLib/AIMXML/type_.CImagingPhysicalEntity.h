/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImagingPhysicalEntity
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImagingPhysicalEntity

#include "type_.CEntity.h"


namespace AIMXML
{

class CImagingPhysicalEntity : public ::AIMXML::CEntity
{
public:
	AIMXML_EXPORT CImagingPhysicalEntity(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CImagingPhysicalEntity(CImagingPhysicalEntity const& init);
	void operator=(CImagingPhysicalEntity const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CImagingPhysicalEntity); }
	MemberElement<iso::CCD, _altova_mi_altova_CImagingPhysicalEntity_altova_typeCode> typeCode;
	struct typeCode { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CCD, _altova_mi_altova_CImagingPhysicalEntity_altova_questionTypeCode> questionTypeCode;
	struct questionTypeCode { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CBL, _altova_mi_altova_CImagingPhysicalEntity_altova_isPresent> isPresent;
	struct isPresent { typedef Iterator<iso::CBL> iterator; };
	MemberElement<iso::CREAL, _altova_mi_altova_CImagingPhysicalEntity_altova_annotatorConfidence> annotatorConfidence;
	struct annotatorConfidence { typedef Iterator<iso::CREAL> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CImagingPhysicalEntity_altova_label> label;
	struct label { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CINT, _altova_mi_altova_CImagingPhysicalEntity_altova_questionIndex> questionIndex;
	struct questionIndex { typedef Iterator<iso::CINT> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CImagingPhysicalEntity_altova_comment> comment;
	struct comment { typedef Iterator<iso::CST> iterator; };
	MemberElement<CimagingPhysicalEntityCharacteristicCollectionType, _altova_mi_altova_CImagingPhysicalEntity_altova_imagingPhysicalEntityCharacteristicCollection> imagingPhysicalEntityCharacteristicCollection;
	struct imagingPhysicalEntityCharacteristicCollection { typedef Iterator<CimagingPhysicalEntityCharacteristicCollectionType> iterator; };
	MemberElement<CimagingObservationCharacteristicCollectionType2, _altova_mi_altova_CImagingPhysicalEntity_altova_imagingObservationCharacteristicCollection> imagingObservationCharacteristicCollection;
	struct imagingObservationCharacteristicCollection { typedef Iterator<CimagingObservationCharacteristicCollectionType2> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImagingPhysicalEntity
