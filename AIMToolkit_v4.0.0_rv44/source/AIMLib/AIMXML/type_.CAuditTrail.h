/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAuditTrail
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAuditTrail



namespace AIMXML
{

class CAuditTrail : public TypeBase
{
public:
	AIMXML_EXPORT CAuditTrail(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CAuditTrail(CAuditTrail const& init);
	void operator=(CAuditTrail const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CAuditTrail); }
	MemberElement<iso::CCD, _altova_mi_altova_CAuditTrail_altova_statusCode> statusCode;
	struct statusCode { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CTS, _altova_mi_altova_CAuditTrail_altova_dateTime> dateTime;
	struct dateTime { typedef Iterator<iso::CTS> iterator; };
	MemberElement<iso::CCD, _altova_mi_altova_CAuditTrail_altova_changeReason> changeReason;
	struct changeReason { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CII, _altova_mi_altova_CAuditTrail_altova_worklistSubtaskUid> worklistSubtaskUid;
	struct worklistSubtaskUid { typedef Iterator<iso::CII> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CAuditTrail_altova_comment> comment;
	struct comment { typedef Iterator<iso::CST> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAuditTrail
