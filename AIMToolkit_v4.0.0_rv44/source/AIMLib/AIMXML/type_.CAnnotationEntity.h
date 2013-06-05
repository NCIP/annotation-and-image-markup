/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAnnotationEntity
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAnnotationEntity

#include "type_.CEntity.h"


namespace AIMXML
{

class CAnnotationEntity : public ::AIMXML::CEntity
{
public:
	AIMXML_EXPORT CAnnotationEntity(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CAnnotationEntity(CAnnotationEntity const& init);
	void operator=(CAnnotationEntity const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CAnnotationEntity); }
	MemberElement<iso::CCD, _altova_mi_altova_CAnnotationEntity_altova_typeCode> typeCode;
	struct typeCode { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CTS, _altova_mi_altova_CAnnotationEntity_altova_dateTime> dateTime;
	struct dateTime { typedef Iterator<iso::CTS> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CAnnotationEntity_altova_name> name;
	struct name { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CAnnotationEntity_altova_comment> comment;
	struct comment { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CII, _altova_mi_altova_CAnnotationEntity_altova_precedentReferencedAnnotationUid> precedentReferencedAnnotationUid;
	struct precedentReferencedAnnotationUid { typedef Iterator<iso::CII> iterator; };
	MemberElement<iso::CII, _altova_mi_altova_CAnnotationEntity_altova_templateUid> templateUid;
	struct templateUid { typedef Iterator<iso::CII> iterator; };
	MemberElement<CauditTrailCollectionType, _altova_mi_altova_CAnnotationEntity_altova_auditTrailCollection> auditTrailCollection;
	struct auditTrailCollection { typedef Iterator<CauditTrailCollectionType> iterator; };
	MemberElement<CimagingPhysicalEntityCollectionType, _altova_mi_altova_CAnnotationEntity_altova_imagingPhysicalEntityCollection> imagingPhysicalEntityCollection;
	struct imagingPhysicalEntityCollection { typedef Iterator<CimagingPhysicalEntityCollectionType> iterator; };
	MemberElement<CcalculationEntityCollectionType, _altova_mi_altova_CAnnotationEntity_altova_calculationEntityCollection> calculationEntityCollection;
	struct calculationEntityCollection { typedef Iterator<CcalculationEntityCollectionType> iterator; };
	MemberElement<CinferenceEntityCollectionType, _altova_mi_altova_CAnnotationEntity_altova_inferenceEntityCollection> inferenceEntityCollection;
	struct inferenceEntityCollection { typedef Iterator<CinferenceEntityCollectionType> iterator; };
	MemberElement<CannotationRoleEntityCollectionType, _altova_mi_altova_CAnnotationEntity_altova_annotationRoleEntityCollection> annotationRoleEntityCollection;
	struct annotationRoleEntityCollection { typedef Iterator<CannotationRoleEntityCollectionType> iterator; };
	MemberElement<ClesionObservationEntityCollectionType, _altova_mi_altova_CAnnotationEntity_altova_lesionObservationEntityCollection> lesionObservationEntityCollection;
	struct lesionObservationEntityCollection { typedef Iterator<ClesionObservationEntityCollectionType> iterator; };
	MemberElement<CimagingObservationEntityCollectionType, _altova_mi_altova_CAnnotationEntity_altova_imagingObservationEntityCollection> imagingObservationEntityCollection;
	struct imagingObservationEntityCollection { typedef Iterator<CimagingObservationEntityCollectionType> iterator; };
	MemberElement<CtaskContextEntityCollectionType, _altova_mi_altova_CAnnotationEntity_altova_taskContextEntityCollection> taskContextEntityCollection;
	struct taskContextEntityCollection { typedef Iterator<CtaskContextEntityCollectionType> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAnnotationEntity
