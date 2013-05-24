/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#pragma once
#ifndef _AIMLib_TaskContextEntity_Class_
#define _AIMLib_TaskContextEntity_Class_

#include <string>
#include <vector>
#include <memory>

namespace aim_lib
{
	class TaskContextEntity;
	typedef std::vector<TaskContextEntity> TaskContextEntityVector;

	class AIMLIB_API TaskContextEntity : public Entity
	{
	public:
		TaskContextEntity(void);
		TaskContextEntity(const TaskContextEntity& taskContextEntity);
		TaskContextEntity& operator=(const TaskContextEntity& taskContextEntity);
		virtual ~TaskContextEntity(void);

		const iso_21090::II& GetWorklistTaskUid() const;
		const std::string& GetWorklistTaskName() const;
		const std::string& GetWorklistTaskDescription() const;
		const iso_21090::CD& GetWorklistTaskCategory() const;
		const iso_21090::CD& GetWorklistTaskLevel() const;
		const iso_21090::CD& GetWorklistTaskType() const;
		const iso_21090::CD* GetWorklistTaskRepeatType() const;
		const iso_21090::CD* GetWorklistTaskVariabilityType() const;
		const std::string& GetWorklistTaskVersion() const;
		const iso_21090::II& GetWorklistSubtaskUid() const;
		const std::string& GetWorklistSubtaskName() const;
		const DateTime& GetWorklistSubtaskStartDateTime() const;
		const DateTime& GetWorklistSubtaskClosedDateTime() const;
		const TaskContextEntityVector& GetTaskContextEntityCollection() const;

		void SetWorklistTaskUid(const iso_21090::II& newVal);
		void SetWorklistTaskName(const std::string& newVal);
		void SetWorklistTaskDescription(const std::string& newVal);
		void SetWorklistTaskCategory(const iso_21090::CD& newVal);
		void SetWorklistTaskLevel(const iso_21090::CD& newVal);
		void SetWorklistTaskType(const iso_21090::CD& newVal);
		void SetWorklistTaskRepeatType(const iso_21090::CD* newVal);
		void SetWorklistTaskVariabilityType(const iso_21090::CD* newVal);
		void SetWorklistTaskVersion(const std::string& newVal);
		void SetWorklistSubtaskUid(const iso_21090::II& newVal);
		void SetWorklistSubtaskName(const std::string& newVal);
		void SetWorklistSubtaskStartDateTime(const DateTime& newVal);
		void SetWorklistSubtaskClosedDateTime(const DateTime& newVal);
		void SetTaskContextEntityCollection(const TaskContextEntityVector& newVal);

	protected:
		iso_21090::II _worklistTaskUid;
		std::string _worklistTaskName;
		std::string _worklistTaskDescription;
		iso_21090::CD _worklistTaskCategory;
		iso_21090::CD _worklistTaskLevel;
		iso_21090::CD _worklistTaskType;
		std::auto_ptr<iso_21090::CD> _worklistTaskRepeatType;
		std::auto_ptr<iso_21090::CD> _worklistTaskVariabilityType;
		std::string _worklistTaskVersion;
		iso_21090::II _worklistSubtaskUid;
		std::string _worklistSubtaskName;
		DateTime _worklistSubtaskStartDateTime;
		DateTime _worklistSubtaskClosedDateTime;
		TaskContextEntityVector _taskContextEntityCollection;
	};

}
#endif // _AIMLib_TaskContextEntity_Class_
