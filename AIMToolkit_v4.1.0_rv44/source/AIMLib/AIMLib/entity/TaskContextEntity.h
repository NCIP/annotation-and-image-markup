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
