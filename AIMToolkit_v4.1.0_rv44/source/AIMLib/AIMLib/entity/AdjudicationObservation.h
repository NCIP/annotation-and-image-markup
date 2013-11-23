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
#ifndef _AIMLib_AdjudicationObservation_Class_
#define _AIMLib_AdjudicationObservation_Class_

#include <string>
#include <memory>
#include <vector>

namespace aim_lib
{
	class AIMLIB_API AdjudicationObservation
	{
	public:
		AdjudicationObservation(void);
		AdjudicationObservation(const AdjudicationObservation& adjudicationObservation);
		virtual ~AdjudicationObservation(void);
		virtual AdjudicationObservation* Clone() const;

		const iso_21090::II& GetObservationUid() const;
		const iso_21090::CD* GetPersonObserversRoleInThisProcedure() const;
		const std::vector<std::string>& GetIdentifierWithinAcceptedPersonObserversRole() const;
		const std::vector<std::string>& GetIdentifierWithinRejectedPersonObserversRole() const;
		const iso_21090::CD& GetReasonForChoice() const;
		const iso_21090::CD* GetReasonForDiscordance() const;
		const std::string& GetComment() const;
		bool GetImageQualityIssuesDiscordance() const;
		const iso_21090::CD& GetObservationScope() const;

		void SetObservationUid(const iso_21090::II& newVal);
		void SetPersonObserversRoleInThisProcedure(const iso_21090::CD* newVal);
		void SetIdentifierWithinAcceptedPersonObserversRole(const std::vector<std::string>& newVal);
		void SetIdentifierWithinRejectedPersonObserversRole(const std::vector<std::string>& newVal);
		void SetReasonForChoice(const iso_21090::CD& newVal);
		void SetReasonForDiscordance(const iso_21090::CD* newVal);
		void SetComment(const std::string& newVal);
		void SetImageQualityIssuesDiscordance(bool newVal);
		void SetObservationScope(const iso_21090::CD& newVal);

	protected:
		iso_21090::II _observationUid;
		std::auto_ptr<iso_21090::CD> _personObserversRoleInThisProcedure;
		std::vector<std::string> _identifierWithinAcceptedPersonObserversRole;
		std::vector<std::string> _identifierWithinRejectedPersonObserversRole;
		iso_21090::CD _reasonForChoice;
		std::auto_ptr<iso_21090::CD> _reasonForDiscordance;
		std::string _comment;
		bool _imageQualityIssuesDiscordance;
		iso_21090::CD _observationScope;
	};
}
#endif // _AIMLib_AdjudicationObservation_Class_
