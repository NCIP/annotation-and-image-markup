/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAdjudicationObservation
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAdjudicationObservation



namespace AIMXML
{

class CAdjudicationObservation : public TypeBase
{
public:
	AIMXML_EXPORT CAdjudicationObservation(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CAdjudicationObservation(CAdjudicationObservation const& init);
	void operator=(CAdjudicationObservation const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CAdjudicationObservation); }
	MemberElement<iso::CII, _altova_mi_altova_CAdjudicationObservation_altova_observationUid> observationUid;
	struct observationUid { typedef Iterator<iso::CII> iterator; };
	MemberElement<iso::CCD, _altova_mi_altova_CAdjudicationObservation_altova_observationScope> observationScope;
	struct observationScope { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CCD, _altova_mi_altova_CAdjudicationObservation_altova_personObserversRoleInThisProcedure> personObserversRoleInThisProcedure;
	struct personObserversRoleInThisProcedure { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CAdjudicationObservation_altova_identifierWithinAcceptedPersonObserversRole> identifierWithinAcceptedPersonObserversRole;
	struct identifierWithinAcceptedPersonObserversRole { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CAdjudicationObservation_altova_identifierWithinRejectedPersonObserversRole> identifierWithinRejectedPersonObserversRole;
	struct identifierWithinRejectedPersonObserversRole { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CCD, _altova_mi_altova_CAdjudicationObservation_altova_reasonForChoice> reasonForChoice;
	struct reasonForChoice { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CCD, _altova_mi_altova_CAdjudicationObservation_altova_reasonForDiscordance> reasonForDiscordance;
	struct reasonForDiscordance { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CAdjudicationObservation_altova_comment> comment;
	struct comment { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CBL, _altova_mi_altova_CAdjudicationObservation_altova_imageQualityIssuesDiscordance> imageQualityIssuesDiscordance;
	struct imageQualityIssuesDiscordance { typedef Iterator<iso::CBL> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CAdjudicationObservation
