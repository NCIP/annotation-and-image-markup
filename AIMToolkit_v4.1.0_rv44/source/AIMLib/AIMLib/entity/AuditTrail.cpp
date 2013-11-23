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

#include "../util/DateTime.h"
#include "AuditTrail.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;
using namespace iso_21090;

AuditTrail::AuditTrail(void){
}

AuditTrail::AuditTrail(const AuditTrail& auditTrail){
	*this = auditTrail;
}

AuditTrail& AuditTrail::operator=(const AuditTrail& auditTrail){
	if (this != &auditTrail)
	{
		_statusCode		= auditTrail._statusCode;
		_dateTime		= auditTrail._dateTime;
		_changeReason	= auditTrail._changeReason;
		SetWorklistSubtaskUid(auditTrail.GetWorklistSubtaskUid());
		_comment		= auditTrail._comment;
	}
	return *this;
}

AuditTrail::~AuditTrail(void){
}

const CD& AuditTrail::GetStatusCode() const{
	return _statusCode;
}

const DateTime& AuditTrail::GetDateTime() const{
	return _dateTime;
}

const CD& AuditTrail::GetChangeReason() const{
	return _changeReason;
}

const II* AuditTrail::GetWorklistSubtaskUid() const{
	return _worklistSubtaskUid.get();
}

const string& AuditTrail::GetComment() const{
	return _comment;
}

void AuditTrail::SetStatusCode(const CD& newVal){
	_statusCode = newVal;
}

void AuditTrail::SetDateTime(const DateTime& newVal){
	_dateTime = newVal;
}

void AuditTrail::SetChangeReason(const CD& newVal){
	_changeReason = newVal;
}

void AuditTrail::SetWorklistSubtaskUid(const II* newVal){
	_worklistSubtaskUid.reset(newVal ? new II(*newVal) : NULL);
}

void AuditTrail::SetComment(const string& newVal){
	_comment = newVal;
}
