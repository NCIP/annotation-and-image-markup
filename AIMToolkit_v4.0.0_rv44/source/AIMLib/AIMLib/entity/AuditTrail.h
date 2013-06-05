/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
