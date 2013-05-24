/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

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
