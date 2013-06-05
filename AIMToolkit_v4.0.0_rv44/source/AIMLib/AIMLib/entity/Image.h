/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_Image_Class_
#define _AIMLib_Image_Class_

#include <memory>
#include <vector>

namespace aim_lib
{
	class AIMLIB_API Image
	{
	public:
		Image();
		Image(const Image& image);
		Image& operator=(const Image& image); // need to have it here; otherwise the auto_ptr template will break the build because of the const in the copy constructor
		virtual ~Image();

		const iso_21090::II& GetSopClassUid() const;
		const iso_21090::II& GetSopInstanceUid() const;
		const GeneralImage* GetGeneralImage() const;
		const ImagePlane* GetImagePlane() const;
		void SetSopClassUid(const iso_21090::II& newVal);
		void SetSopInstanceUid(const iso_21090::II& newVal);
		void SetGeneralImage(const GeneralImage* newVal);
		void SetImagePlane(const ImagePlane* newVal);

	protected:
		iso_21090::II _sopClassUid;
		iso_21090::II _sopInstanceUid;
		std::auto_ptr<GeneralImage> _generalImage;
		std::auto_ptr<ImagePlane> _imagePlane;
	};

	typedef std::vector<Image> ImageVector;
}

#endif  // _AIMLib_Image_Class_