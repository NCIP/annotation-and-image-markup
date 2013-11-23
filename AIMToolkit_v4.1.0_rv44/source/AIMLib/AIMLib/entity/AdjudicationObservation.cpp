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
