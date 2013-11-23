/*
Copyright (c) 2008-2013, Northwestern University
All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 
  Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
 
  Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
 
  Neither the name of the Northwestern University nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
