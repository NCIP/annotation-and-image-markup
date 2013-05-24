/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImagingObservationEntity
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImagingObservationEntity

#include "type_.CEntity.h"


namespace AIMXML
{

class CImagingObservationEntity : public ::AIMXML::CEntity
{
public:
	AIMXML_EXPORT CImagingObservationEntity(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CImagingObservationEntity(CImagingObservationEntity const& init);
	void operator=(CImagingObservationEntity const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CImagingObservationEntity); }
	MemberElement<iso::CCD, _altova_mi_altova_CImagingObservationEntity_altova_typeCode> typeCode;
	struct typeCode { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CCD, _altova_mi_altova_CImagingObservationEntity_altova_questionTypeCode> questionTypeCode;
	struct questionTypeCode { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CREAL, _altova_mi_altova_CImagingObservationEntity_altova_annotatorConfidence> annotatorConfidence;
	struct annotatorConfidence { typedef Iterator<iso::CREAL> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CImagingObservationEntity_altova_label> label;
	struct label { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CImagingObservationEntity_altova_comment> comment;
	struct comment { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CBL, _altova_mi_altova_CImagingObservationEntity_altova_isPresent> isPresent;
	struct isPresent { typedef Iterator<iso::CBL> iterator; };
	MemberElement<iso::CINT, _altova_mi_altova_CImagingObservationEntity_altova_questionIndex> questionIndex;
	struct questionIndex { typedef Iterator<iso::CINT> iterator; };
	MemberElement<CimagingObservationCharacteristicCollectionType, _altova_mi_altova_CImagingObservationEntity_altova_imagingObservationCharacteristicCollection> imagingObservationCharacteristicCollection;
	struct imagingObservationCharacteristicCollection { typedef Iterator<CimagingObservationCharacteristicCollectionType> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CImagingObservationEntity
