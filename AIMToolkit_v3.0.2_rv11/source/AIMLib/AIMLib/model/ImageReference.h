/*
  Classname: ImageReference

*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(EA_AE03A494_45F6_4691_B800_CE0CC8753DC4__INCLUDED_)
#define EA_AE03A494_45F6_4691_B800_CE0CC8753DC4__INCLUDED_

#include <string>
#include <vector>

namespace aim_lib
{
// NOTE: These are internal library definitions and should be treated as such
#define C_DICOM_IMAGE_NAME	std::string("DICOMImage")
#define C_WEB_IMAGE_NAME	std::string("WebImage")

	class AIMLIB_API ImageReference : public AimBase
	{
	public:
		enum ImageReferenceType
		{
			T_UNDEFINED_IMAGE_REF,
			T_DICOM_IMAGE_REF,
			T_WEB_IMAGE_REF
		};

		virtual ~ImageReference();
		virtual ImageReference* Clone() const = 0;

		ImageReferenceType GetImageReferenceType() const;

	protected:
		ImageReference(const std::string& typeName);
		ImageReference(const ImageReference& imageReference);

		int _cagridId;
	};

	typedef std::vector<ImageReference*> ImageReferencePtrVector;

}
#endif // !defined(EA_AE03A494_45F6_4691_B800_CE0CC8753DC4__INCLUDED_)
