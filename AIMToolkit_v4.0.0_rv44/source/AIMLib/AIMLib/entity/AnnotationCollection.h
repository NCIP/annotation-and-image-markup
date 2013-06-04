/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
