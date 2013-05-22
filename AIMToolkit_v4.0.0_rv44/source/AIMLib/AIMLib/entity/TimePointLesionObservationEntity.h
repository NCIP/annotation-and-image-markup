/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_TimePointLesionObservationEntity_Class_
#define _AIMLib_TimePointLesionObservationEntity_Class_

#include <string>
#include <memory>

namespace aim_lib
{
	class AIMLIB_API TimePointLesionObservationEntity : public LesionObservationEntity
	{
	public:
		TimePointLesionObservationEntity(void);
		TimePointLesionObservationEntity(const TimePointLesionObservationEntity& lesionObservationEntity);
		virtual ~TimePointLesionObservationEntity(void);
		TimePointLesionObservationEntity& operator=(const TimePointLesionObservationEntity& lesionObservationEntity);
		virtual TimePointLesionObservationEntity* Clone() const;

		bool GetCalibration() const;
		bool* GetCanEvaluateLesion() const;
		bool* GetCanMeasureLesion() const;
		const std::string& GetComment() const;
		bool* GetIsUnequivocalProgression() const;
		const iso_21090::II* GetPredecessorLesionTrackingUid() const;
		const iso_21090::CD* GetQualitativeAssessment() const;
		const iso_21090::CD* GetReasonUnableToEvaluate() const;
		const iso_21090::CD* GetReasonUnableToMeasure() const;
		const iso_21090::CD* GetTherapeuticResponse() const;

		void SetCalibration(bool newVal);
		void SetCanEvaluateLesion(bool* newVal);
		void SetCanMeasureLesion(bool* newVal);
		void SetComment(const std::string& newVal);
		void SetIsUnequivocalProgression(bool* newVal);
		void SetPredecessorLesionTrackingUid(const iso_21090::II* newVal);
		void SetQualitativeAssessment(const iso_21090::CD* newVal);
		void SetReasonUnableToEvaluate(const iso_21090::CD* newVal);
		void SetReasonUnableToMeasure(const iso_21090::CD* newVal);
		void SetTherapeuticResponse(const iso_21090::CD* newVal);

	protected:
		bool _calibration;
		std::auto_ptr<bool> _canEvaluateLesion;
		std::auto_ptr<bool> _canMeasureLesion;
		std::string _comment;
		std::auto_ptr<bool> _isUnequivocalProgression;
		std::auto_ptr<iso_21090::II> _predecessorLesionTrackingUid;
		std::auto_ptr<iso_21090::CD> _qualitativeAssessment;
		std::auto_ptr<iso_21090::CD> _reasonUnableToEvaluate;
		std::auto_ptr<iso_21090::CD> _reasonUnableToMeasure;
		std::auto_ptr<iso_21090::CD> _therapeuticResponse;
	};
}
#endif // _AIMLib_TimePointLesionObservationEntity_Class_
