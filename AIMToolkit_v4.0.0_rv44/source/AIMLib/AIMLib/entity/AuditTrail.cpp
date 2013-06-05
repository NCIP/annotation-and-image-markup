/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
