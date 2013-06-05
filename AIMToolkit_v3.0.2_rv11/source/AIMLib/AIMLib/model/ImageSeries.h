/*
  Classname: ImageSeries

*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(_AIMLib_ImageSeries_INCLUDED_)
#define _AIMLib_ImageSeries_INCLUDED_

#include <string>
#include <vector>

namespace aim_lib
{
	class AIMLIB_API ImageSeries
	{
	public:
		ImageSeries(void);
		ImageSeries(const ImageSeries& series);
		~ImageSeries(void);

		const std::string& GetInstanceUID() const;
		const ImageVector& GetImageCollection() const;
		void SetInstanceUID(const std::string& newVal);
		void SetImageCollection(const ImageVector& images);

	protected:
		int _cagridId;
		std::string _instanceUID; // Series Instance UID
		ImageVector _imageCollection;
	};
}

#endif // !defined(_AIMLib_ImageSeries_INCLUDED_)
