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
#ifndef _AIMLib_GeneralLesionObservationEntity_Class_
#define _AIMLib_GeneralLesionObservationEntity_Class_

#include <string>
#include <memory>

namespace aim_lib
{
	class AIMLIB_API GeneralLesionObservationEntity : public LesionObservationEntity
	{
	public:
		GeneralLesionObservationEntity(void);
		GeneralLesionObservationEntity(const GeneralLesionObservationEntity& lesionObservationEntity);
		virtual ~GeneralLesionObservationEntity(void);
		GeneralLesionObservationEntity& operator=(const GeneralLesionObservationEntity& lesionObservationEntity);
		virtual GeneralLesionObservationEntity* Clone() const;

		const iso_21090::CD& GetLesionType() const;
		const std::string& GetTrackingIdentifier() const;
		const iso_21090::CD* GetLaterality() const;
		const iso_21090::CD* GetReconstructionInterval() const;

		void SetLesionType(const iso_21090::CD& newVal);
		void SetTrackingIdentifier(const std::string& newVal);
		void SetLaterality(const iso_21090::CD* newVal);
		void SetReconstructionInterval(const iso_21090::CD* newVal);
	protected:
		iso_21090::CD _lesionType;
		std::string _trackingIdentifier;
		std::auto_ptr<iso_21090::CD> _laterality;
		std::auto_ptr<iso_21090::CD> _reconstructionInterval;
	};
}
#endif // _AIMLib_GeneralLesionObservationEntity_Class_
