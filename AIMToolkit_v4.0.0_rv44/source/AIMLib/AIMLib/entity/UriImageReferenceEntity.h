/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_UriImageReferenceEntity_Class
#define _AIMLib_UriImageReferenceEntity_Class

#include <string>

namespace aim_lib
{
	class AIMLIB_API UriImageReferenceEntity : public ImageReferenceEntity
	{
	public:
		UriImageReferenceEntity();
		UriImageReferenceEntity(const UriImageReferenceEntity& imageReference);
		virtual ~UriImageReferenceEntity();
		virtual UriImageReferenceEntity* Clone() const;

		virtual ImageReferenceEntityType GetImageReferenceEntityType() const;

		const std::string& GetUri() const;
		const std::string& GetMimeType() const;
		void SetUri(const std::string& newVal);
		void SetMimeType(const std::string& newVal);

	private:
		std::string _uri;
		std::string _mimeType;
	};
}
#endif // _AIMLib_UriImageReferenceEntity_Class
