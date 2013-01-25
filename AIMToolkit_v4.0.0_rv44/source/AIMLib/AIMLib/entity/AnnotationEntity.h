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
#ifndef _AIMLib_AnnotationEntity_Class_
#define _AIMLib_AnnotationEntity_Class_

#include <memory>
#include <string>

namespace aim_lib
{
	class AIMLIB_API AnnotationEntity : public Entity
	{
	public:
		enum AnnotationType
		{
			AT_ImageAnnotation,
			AT_AnnotationOfAnnotation,
			AT_Unknown
		};

		AnnotationEntity& operator=(const AnnotationEntity& annotationEntity);
		virtual ~AnnotationEntity(void);

		virtual AnnotationType GetAnnotationType() const = 0;

		const iso_21090::CDVector& GetTypeCode() const;
		const DateTime& GetDateTime() const;
		const std::string& GetName() const;
		const std::string& GetComment() const;
		iso_21090::II* GetPrecedentReferencedAnnotationUid() const;
		iso_21090::II* GetTemplateUid() const;
		const ImagingPhysicalEntityVector& GetImagingPhysicalEntityCollection() const;
		const ImagingObservationEntityVector& GetImagingObservationEntityCollection() const;
		const InferenceEntityVector& GetInferenceEntityCollection() const;
		const CalculationEntityVector& GetCalculationEntityCollection() const;
		const AnnotationRoleEntityVector& GetAnnotationRoleEntityCollection() const;
		const LesionObservationEntityPtrVector& GetLesionObservationEntityCollection() const;
		const AuditTrailVector& GetAuditTrailCollection() const;
		const TaskContextEntityVector& GetTaskContextEntityCollection() const;

		void SetTypeCode(const iso_21090::CDVector& typeCode);
		void SetDateTime(const DateTime& dateTime);
		void SetName(const std::string& name);
		void SetComment(const std::string& comment);
		void SetPrecedentReferencedAnnotationUid(iso_21090::II* precedentAnnotationUid);
		void SetTemplateUid(iso_21090::II* templateUid);
		void SetImagingPhysicalEntityCollection(const ImagingPhysicalEntityVector& imagingPhysicalEntities);
		void SetImagingObservationEntityCollection(const ImagingObservationEntityVector& imagingObservationEntities);
		void SetInferenceEntityCollection(const InferenceEntityVector& inferenceEntities);
		void SetCalculationEntityCollection(const CalculationEntityVector& calculationEntities);
		void SetAnnotationRoleEntityCollection(const AnnotationRoleEntityVector& annotationRoleEntities);
		void SetLesionOservationEntityCollection(const LesionObservationEntityPtrVector& lesionObservationEntities);
		void SetAuditTrailCollection(const AuditTrailVector& auditTrails);
		void SetTaskContextEntityCollection(const TaskContextEntityVector& taskContextEntities);

	protected:
		AnnotationEntity(const AnnotationEntity& annotationEntity);
		AnnotationEntity();

		iso_21090::CDVector _typeCode;
		DateTime _dateTime;
		std::string _name;
		std::string _comment;
		std::auto_ptr<iso_21090::II> _precedentReferencedAnnotationUid;
		std::auto_ptr<iso_21090::II> _templateUid;

		ImagingPhysicalEntityVector _imagingPhysicalEntityCollection;
		ImagingObservationEntityVector _imagingObservationEntityCollection;
		InferenceEntityVector _inferenceEntityCollection;
		CalculationEntityVector _calculationEntityCollection;
		AnnotationRoleEntityVector _annotationRoleEntityCollection;
		LesionObservationEntityPtrVector _lesionObservationEntityCollection;
		AuditTrailVector _auditTrailCollection;
		TaskContextEntityVector _taskContextEntityCollection;
	};
}
#endif // _AIMLib_AnnotationEntity_Class_
