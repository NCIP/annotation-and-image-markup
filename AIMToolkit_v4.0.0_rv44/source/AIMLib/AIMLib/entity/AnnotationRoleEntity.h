/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_AnnotationRoleEntity_Class_
#define _AIMLib_AnnotationRoleEntity_Class_

#include <vector>

namespace aim_lib
{
	class AIMLIB_API AnnotationRoleEntity : public Entity
	{
	public:
		AnnotationRoleEntity(void);
		AnnotationRoleEntity(const AnnotationRoleEntity& annotationEntity);
		virtual ~AnnotationRoleEntity(void);

		const iso_21090::CD& GetRoleCode() const;
		const iso_21090::CDVector& GetQuestionTypeCode() const;
		int GetRoleSequenceNumber() const;

		void SetRoleCode(const iso_21090::CD& roleCode);
		void SetQuestionTypeCode(const iso_21090::CDVector& questionTypeCode);
		void SetRoleSequenceNumber(int roleSequenceNumber);

	protected:
		iso_21090::CD _roleCode;
		iso_21090::CDVector _questionTypeCode;
		int _roleSequenceNumber;
	};

	typedef std::vector<AnnotationRoleEntity> AnnotationRoleEntityVector;
}
#endif // _AIMLib_AnnotationRoleEntity_Class_
