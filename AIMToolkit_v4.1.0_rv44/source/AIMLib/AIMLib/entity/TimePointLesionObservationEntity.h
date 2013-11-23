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
