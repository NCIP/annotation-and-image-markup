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
#ifndef _AIMLib_AnnotationCollection_Class_
#define _AIMLib_AnnotationCollection_Class_

#include <memory>

namespace aim_lib
{
	class AIMLIB_API AnnotationCollection
	{
	public:
		enum AnnotationCollectionType
		{
			ACT_ImageAnnotationCollection,
			ACT_AnnotationOfAnnotationCollection
		};

		virtual ~AnnotationCollection(void);
		virtual AnnotationCollection* Clone() const = 0;
		virtual AnnotationCollectionType GetAnnotationCollectionType() const = 0;
		virtual void ClearAnnotations() = 0;

		const iso_21090::II& GetUniqueIdentifier() const;
		AimVersion GetAimVersion() const;
		const std::string& GetDescription() const;
		const DateTime& GetDateTime() const;
		const User* GetUser() const;
		const Equipment* GetEquipment() const;

		void SetUniqueIdentifier(const iso_21090::II& newVal);
		void SetAimVersion(AimVersion newVal);
		void SetDescription(const std::string& newVal);
		void SetDateTime(const DateTime& newVal);
		void SetUser(const User* newVal);
		void SetEquipment(const Equipment* newVal);

	protected:
		AnnotationCollection(void);
		AnnotationCollection(const AnnotationCollection& annotationCollection);

		iso_21090::II _uniqueIdentifier;
		AimVersion _aimVersion;
		std::string _description;
		DateTime _dateTime;
		std::auto_ptr<User> _user;
		std::auto_ptr<Equipment> _equipment;
	};
}
#endif // _AIMLib_AnnotationCollection_Class_
