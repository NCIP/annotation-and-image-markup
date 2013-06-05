/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
