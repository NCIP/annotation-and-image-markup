/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#ifndef _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CTimePointLesionObservationEntity
#define _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CTimePointLesionObservationEntity

#include "type_.CLesionObservationEntity.h"


namespace AIMXML
{

class CTimePointLesionObservationEntity : public ::AIMXML::CLesionObservationEntity
{
public:
	AIMXML_EXPORT CTimePointLesionObservationEntity(xercesc::DOMNode* const& init);
	AIMXML_EXPORT CTimePointLesionObservationEntity(CTimePointLesionObservationEntity const& init);
	void operator=(CTimePointLesionObservationEntity const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_altova_CTimePointLesionObservationEntity); }
	MemberElement<iso::CBL, _altova_mi_altova_CTimePointLesionObservationEntity_altova_calibration> calibration;
	struct calibration { typedef Iterator<iso::CBL> iterator; };
	MemberElement<iso::CII, _altova_mi_altova_CTimePointLesionObservationEntity_altova_predecessorLesionTrackingUid> predecessorLesionTrackingUid;
	struct predecessorLesionTrackingUid { typedef Iterator<iso::CII> iterator; };
	MemberElement<iso::CST, _altova_mi_altova_CTimePointLesionObservationEntity_altova_comment> comment;
	struct comment { typedef Iterator<iso::CST> iterator; };
	MemberElement<iso::CCD, _altova_mi_altova_CTimePointLesionObservationEntity_altova_therapeuticResponse> therapeuticResponse;
	struct therapeuticResponse { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CCD, _altova_mi_altova_CTimePointLesionObservationEntity_altova_qualitativeAssessment> qualitativeAssessment;
	struct qualitativeAssessment { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CBL, _altova_mi_altova_CTimePointLesionObservationEntity_altova_canEvaluateLesion> canEvaluateLesion;
	struct canEvaluateLesion { typedef Iterator<iso::CBL> iterator; };
	MemberElement<iso::CCD, _altova_mi_altova_CTimePointLesionObservationEntity_altova_reasonUnableToEvaluate> reasonUnableToEvaluate;
	struct reasonUnableToEvaluate { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CBL, _altova_mi_altova_CTimePointLesionObservationEntity_altova_canMeasureLesion> canMeasureLesion;
	struct canMeasureLesion { typedef Iterator<iso::CBL> iterator; };
	MemberElement<iso::CCD, _altova_mi_altova_CTimePointLesionObservationEntity_altova_reasonUnableToMeasure> reasonUnableToMeasure;
	struct reasonUnableToMeasure { typedef Iterator<iso::CCD> iterator; };
	MemberElement<iso::CBL, _altova_mi_altova_CTimePointLesionObservationEntity_altova_isUnequivocalProgression> isUnequivocalProgression;
	struct isUnequivocalProgression { typedef Iterator<iso::CBL> iterator; };
	AIMXML_EXPORT void SetXsiType();
};


}	// namespace AIMXML

#endif // _ALTOVA_INCLUDED_AIMXML_ALTOVA__ALTOVA_CTimePointLesionObservationEntity
