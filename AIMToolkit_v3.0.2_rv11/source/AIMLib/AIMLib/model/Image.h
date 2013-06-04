/*
  Classname: Image

*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(_AIMLib_Image_Class)
#define _AIMLib_Image_Class

#include <string>
#include <vector>

namespace aim_lib
{
	class AIMLIB_API Image
	{
	public:
		Image();
		Image(const Image& image);
		Image& operator=(const Image& image); // need to have it here; otherwise the auto_ptr template will break the build because of the const in the copy constructor
		~Image();

		const std::string& GetSopClassUID() const;
		const std::string& GetSopInstanceUID() const;
		void SetSopClassUID(const std::string& newVal);
		void SetSopInstanceUID(const std::string& newVal);

	protected:
		int _cagridId;
		std::string _sopClassUID;
		std::string _sopInstanceUID;
	};

	typedef std::vector<Image> ImageVector;
}

#endif  // _AIMLib_Image_Class