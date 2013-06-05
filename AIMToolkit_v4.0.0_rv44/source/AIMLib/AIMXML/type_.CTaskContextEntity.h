/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CTaskContextEntity
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CTaskContextEntity

#include "type_.CEntity.h"


namespace AIMXML
{

class CTaskContextEntity : public ::AIMXML::CEntity
{
public:
	AIMXML_EXPORT CTaskContextEntity(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CTaskContextEntity(CTaskContextEntity const& init);
	void operator=(CTaskContextEntity const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CTaskContextEntity); }
	MemberElement<iso::CII, _altova_mi_altova_CTaskContextEntity_altova_worklistTaskUid> worklistTaskUid;
	struct worklistTaskUid { typedef Iterator<iso::CII> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CTaskContextEntity_altova_worklistTaskName> worklistTaskName;
	struct worklistTaskName { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CTaskContextEntity_altova_worklistTaskDescription> worklistTaskDescription;
	struct worklistTaskDescription { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CCD, _altova_mi_altova_CTaskContextEntity_altova_worklistTaskCategory> worklistTaskCategory;
	struct worklistTaskCategory { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CCD, _altova_mi_altova_CTaskContextEntity_altova_worklistTaskLevel> worklistTaskLevel;
	struct worklistTaskLevel { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CCD, _altova_mi_altova_CTaskContextEntity_altova_worklistTaskType> worklistTaskType;
	struct worklistTaskType { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CCD, _altova_mi_altova_CTaskContextEntity_altova_worklistTaskRepeatType> worklistTaskRepeatType;
	struct worklistTaskRepeatType { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CCD, _altova_mi_altova_CTaskContextEntity_altova_worklistTaskVariabilityType> worklistTaskVariabilityType;
	struct worklistTaskVariabilityType { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CTaskContextEntity_altova_worklistTaskVersion> worklistTaskVersion;
	struct worklistTaskVersion { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CII, _altova_mi_altova_CTaskContextEntity_altova_worklistSubtaskUid> worklistSubtaskUid;
	struct worklistSubtaskUid { typedef Iterator<iso::CII> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CTaskContextEntity_altova_worklistSubtaskName> worklistSubtaskName;
	struct worklistSubtaskName { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CTS, _altova_mi_altova_CTaskContextEntity_altova_worklistSubtaskStartDateTime> worklistSubtaskStartDateTime;
	struct worklistSubtaskStartDateTime { typedef Iterator<iso::CTS> iterator; };
	MemberElement<iso::CTS, _altova_mi_altova_CTaskContextEntity_altova_worklistSubtaskClosedDateTime> worklistSubtaskClosedDateTime;
	struct worklistSubtaskClosedDateTime { typedef Iterator<iso::CTS> iterator; };
	MemberElement<CtaskContextEntityCollectionType2, _altova_mi_altova_CTaskContextEntity_altova_taskContextEntityCollection> taskContextEntityCollection;
	struct taskContextEntityCollection { typedef Iterator<CtaskContextEntityCollectionType2> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CTaskContextEntity
