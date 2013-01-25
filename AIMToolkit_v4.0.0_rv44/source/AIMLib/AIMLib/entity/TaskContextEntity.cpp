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

#include "../stdafx.h"
#include "Entity.h"
#include "../util/DateTime.h"
#include "TaskContextEntity.h"

using std::string;
using namespace aim_lib;
using namespace iso_21090;

TaskContextEntity::TaskContextEntity(void){
}

TaskContextEntity::TaskContextEntity(const TaskContextEntity& taskContextEntity){
	*this = taskContextEntity;
}

TaskContextEntity& TaskContextEntity::operator=(const TaskContextEntity& taskContextEntity){
	if (this != &taskContextEntity)
	{
		Entity::operator=(taskContextEntity);
		_worklistTaskUid				= taskContextEntity._worklistTaskUid;
		_worklistTaskName				= taskContextEntity._worklistTaskName;
		_worklistTaskDescription		= taskContextEntity._worklistTaskDescription;
		_worklistTaskCategory			= taskContextEntity._worklistTaskCategory;
		_worklistTaskLevel				= taskContextEntity._worklistTaskLevel;
		_worklistTaskType				= taskContextEntity._worklistTaskType;
		_worklistTaskVersion			= taskContextEntity._worklistTaskVersion;
		_worklistSubtaskUid				= taskContextEntity._worklistSubtaskUid;
		_worklistSubtaskName			= taskContextEntity._worklistSubtaskName;
		_worklistSubtaskStartDateTime	= taskContextEntity._worklistSubtaskStartDateTime;
		_worklistSubtaskClosedDateTime	= taskContextEntity._worklistSubtaskClosedDateTime;
		SetWorklistTaskRepeatType(taskContextEntity.GetWorklistTaskRepeatType());
		SetWorklistTaskVariabilityType(taskContextEntity.GetWorklistTaskVariabilityType());
		SetTaskContextEntityCollection(taskContextEntity.GetTaskContextEntityCollection());
	}
	return *this;
}

TaskContextEntity::~TaskContextEntity(void){
	_taskContextEntityCollection.clear();
}

const II& TaskContextEntity::GetWorklistTaskUid() const{
	return _worklistTaskUid;
}

const string& TaskContextEntity::GetWorklistTaskName() const{
	return _worklistTaskName;
}

const string& TaskContextEntity::GetWorklistTaskDescription() const{
	return _worklistTaskDescription;
}

const CD& TaskContextEntity::GetWorklistTaskCategory() const{
	return _worklistTaskCategory;
}

const CD& TaskContextEntity::GetWorklistTaskLevel() const{
	return _worklistTaskLevel;
}

const CD& TaskContextEntity::GetWorklistTaskType() const{
	return _worklistTaskType;
}

const CD* TaskContextEntity::GetWorklistTaskRepeatType() const{
	return _worklistTaskRepeatType.get();
}

const CD* TaskContextEntity::GetWorklistTaskVariabilityType() const{
	return _worklistTaskVariabilityType.get();
}

const string& TaskContextEntity::GetWorklistTaskVersion() const{
	return _worklistTaskVersion;
}

const II& TaskContextEntity::GetWorklistSubtaskUid() const{
	return _worklistSubtaskUid;
}

const string& TaskContextEntity::GetWorklistSubtaskName() const{
	return _worklistSubtaskName;
}

const DateTime& TaskContextEntity::GetWorklistSubtaskStartDateTime() const{
	return _worklistSubtaskStartDateTime;
}

const DateTime& TaskContextEntity::GetWorklistSubtaskClosedDateTime() const{
	return _worklistSubtaskClosedDateTime;
}

const TaskContextEntityVector& TaskContextEntity::GetTaskContextEntityCollection() const{
	return _taskContextEntityCollection;
}


void TaskContextEntity::SetWorklistTaskUid(const II& newVal){
	_worklistTaskUid = newVal;
}

void TaskContextEntity::SetWorklistTaskName(const string& newVal){
	_worklistTaskName = newVal;
}

void TaskContextEntity::SetWorklistTaskDescription(const string& newVal){
	_worklistTaskDescription = newVal;
}

void TaskContextEntity::SetWorklistTaskCategory(const CD& newVal){
	_worklistTaskCategory = newVal;
}

void TaskContextEntity::SetWorklistTaskLevel(const CD& newVal){
	_worklistTaskLevel = newVal;
}

void TaskContextEntity::SetWorklistTaskType(const CD& newVal){
	_worklistTaskType = newVal;
}

void TaskContextEntity::SetWorklistTaskRepeatType(const CD* newVal){
	_worklistTaskRepeatType.reset(newVal ? new CD(*newVal) : NULL);
}

void TaskContextEntity::SetWorklistTaskVariabilityType(const CD* newVal){
	_worklistTaskVariabilityType.reset(newVal ? new CD(*newVal) : NULL);
}

void TaskContextEntity::SetWorklistTaskVersion(const string& newVal){
	_worklistTaskVersion = newVal;
}

void TaskContextEntity::SetWorklistSubtaskUid(const II& newVal){
	_worklistSubtaskUid = newVal;
}

void TaskContextEntity::SetWorklistSubtaskName(const string& newVal){
	_worklistSubtaskName = newVal;
}

void TaskContextEntity::SetWorklistSubtaskStartDateTime(const DateTime& newVal){
	_worklistSubtaskStartDateTime = newVal;
}

void TaskContextEntity::SetWorklistSubtaskClosedDateTime(const DateTime& newVal){
	_worklistSubtaskClosedDateTime = newVal;
}

void TaskContextEntity::SetTaskContextEntityCollection(const TaskContextEntityVector& newVal){
	_taskContextEntityCollection.assign(newVal.begin(), newVal.end());
}
