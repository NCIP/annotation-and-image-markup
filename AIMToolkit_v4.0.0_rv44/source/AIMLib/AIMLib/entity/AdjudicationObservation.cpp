/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "AdjudicationObservation.h"

#include "../memdebug.h"

using namespace std;
using namespace aim_lib;
using namespace iso_21090;

AdjudicationObservation::AdjudicationObservation(void){
}

AdjudicationObservation::AdjudicationObservation(const AdjudicationObservation& adjudicationObservation){
	_observationUid									= adjudicationObservation._observationUid;
	_reasonForChoice								= adjudicationObservation._reasonForChoice;
	_comment										= adjudicationObservation._comment;
	_imageQualityIssuesDiscordance					= adjudicationObservation._imageQualityIssuesDiscordance;
	_observationScope								= adjudicationObservation._observationScope;

	SetIdentifierWithinAcceptedPersonObserversRole(adjudicationObservation.GetIdentifierWithinAcceptedPersonObserversRole());
	SetIdentifierWithinRejectedPersonObserversRole(adjudicationObservation.GetIdentifierWithinRejectedPersonObserversRole());
	SetPersonObserversRoleInThisProcedure(adjudicationObservation.GetPersonObserversRoleInThisProcedure());
	SetReasonForDiscordance(adjudicationObservation.GetReasonForDiscordance());
}

AdjudicationObservation::~AdjudicationObservation(void){
}

AdjudicationObservation* AdjudicationObservation::Clone(void) const{
	return new AdjudicationObservation(*this);
}

const II& AdjudicationObservation::GetObservationUid() const{
	return _observationUid;
}

const CD* AdjudicationObservation::GetPersonObserversRoleInThisProcedure() const{
	return _personObserversRoleInThisProcedure.get();
}

const vector<string>& AdjudicationObservation::GetIdentifierWithinAcceptedPersonObserversRole() const{
	return _identifierWithinAcceptedPersonObserversRole;
}

const vector<string>& AdjudicationObservation::GetIdentifierWithinRejectedPersonObserversRole() const{
	return _identifierWithinRejectedPersonObserversRole;
}

const CD& AdjudicationObservation::GetReasonForChoice() const{
	return _reasonForChoice;
}

const CD* AdjudicationObservation::GetReasonForDiscordance() const{
	return _reasonForDiscordance.get();
}

const string& AdjudicationObservation::GetComment() const{
	return _comment;
}

bool AdjudicationObservation::GetImageQualityIssuesDiscordance() const{
	return _imageQualityIssuesDiscordance;
}

const CD& AdjudicationObservation::GetObservationScope() const{
	return _observationScope;
}

void AdjudicationObservation::SetObservationUid(const II& newVal){
	_observationUid = newVal;
}

void AdjudicationObservation::SetPersonObserversRoleInThisProcedure(const CD* newVal){
	_personObserversRoleInThisProcedure.reset(newVal ? new CD(*newVal) : NULL);
}

void AdjudicationObservation::SetIdentifierWithinAcceptedPersonObserversRole(const vector<string>& newVal){
	_identifierWithinAcceptedPersonObserversRole.assign(newVal.begin(), newVal.end());
}

void AdjudicationObservation::SetIdentifierWithinRejectedPersonObserversRole(const vector<string>& newVal){
	_identifierWithinRejectedPersonObserversRole.assign(newVal.begin(), newVal.end());
}

void AdjudicationObservation::SetReasonForChoice(const CD& newVal){
	_reasonForChoice = newVal;
}

void AdjudicationObservation::SetReasonForDiscordance(const CD* newVal){
	_reasonForDiscordance.reset(newVal ? new CD(*newVal) : NULL);
}

void AdjudicationObservation::SetComment(const string& newVal){
	_comment = newVal;
}

void AdjudicationObservation::SetImageQualityIssuesDiscordance(bool newVal){
	_imageQualityIssuesDiscordance = newVal;
}

void AdjudicationObservation::SetObservationScope(const CD& newVal){
	_observationScope = newVal;
}
