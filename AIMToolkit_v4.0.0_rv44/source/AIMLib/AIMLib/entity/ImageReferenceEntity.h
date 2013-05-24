/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#pragma once
#ifndef _AIMLib_ImageReferenceEntity_Class_
#define _AIMLib_ImageReferenceEntity_Class_

#include <string>
#include <vector>

namespace aim_lib
{
// NOTE: These are internal library definitions and should be treated as such
#define C_DICOM_IMAGE_REFERENCE_NAME	std::string("DicomImageReferenceEntity")
#define C_URI_IMAGE_REFERENCE_NAME	std::string("UriImageReferenceEntity")

	class AIMLIB_API ImageReferenceEntity : public Entity
	{
	public:
		enum ImageReferenceEntityType
		{
			T_UNDEFINED_IMAGE_REF,
			T_DICOM_IMAGE_REF,
			T_URI_IMAGE_REF
		};

		virtual ~ImageReferenceEntity();
		virtual ImageReferenceEntity* Clone() const = 0;

		virtual ImageReferenceEntityType GetImageReferenceEntityType() const = 0;

	protected:
		ImageReferenceEntity(const std::string& typeName);
		ImageReferenceEntity(const ImageReferenceEntity& imageReference);
	};

	typedef std::vector<ImageReferenceEntity*> ImageReferenceEntityPtrVector;
}
#endif // _AIMLib_ImageReferenceEntity_Class_
