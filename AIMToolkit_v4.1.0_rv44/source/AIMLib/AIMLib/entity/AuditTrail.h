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
#ifndef _AIMLib_AuditTrail_Class_
#define _AIMLib_AuditTrail_Class_

#include <string>
#include <vector>
#include <memory>

namespace aim_lib
{
	class AIMLIB_API AuditTrail
	{
	public:
		AuditTrail(void);
		AuditTrail(const AuditTrail& auditTrail);
		AuditTrail& operator=(const AuditTrail& auditTrail);
		virtual ~AuditTrail(void);

		const iso_21090::CD& GetStatusCode() const;
		const DateTime& GetDateTime() const;
		const iso_21090::CD& GetChangeReason() const;
		const iso_21090::II* GetWorklistSubtaskUid() const;
		const std::string& GetComment() const;

		void SetStatusCode(const iso_21090::CD& newVal);
		void SetDateTime(const DateTime& newVal);
		void SetChangeReason(const iso_21090::CD& newVal);
		void SetWorklistSubtaskUid(const iso_21090::II* newVal);
		void SetComment(const std::string& newVal);

	protected:
		iso_21090::CD _statusCode;
		DateTime _dateTime;
		iso_21090::CD _changeReason;
		std::auto_ptr<iso_21090::II> _worklistSubtaskUid;
		std::string _comment;
	};
		
	typedef std::vector<AuditTrail> AuditTrailVector;
}
#endif // _AIMLib_AuditTrail_Class_
