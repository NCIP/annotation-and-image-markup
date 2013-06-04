/*
  Classname: ImageStudy

*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(_AIMLib_ImageStudy_Class)
#define _AIMLib_ImageStudy_Class

#include <string>
#include <ctime>

namespace aim_lib
{
	class AIMLIB_API ImageStudy
	{
	public:
		ImageStudy();
		ImageStudy(const ImageStudy& study);
		~ImageStudy();

		const std::string& GetInstanceUID() const;
		const Date& GetStartDate() const;
		const Time& GetStartTime() const;
		const ImageSeries& GetSeries() const;
		void SetInstanceUID(const std::string& newVal);
		void SetStartDate(const Date& newVal);
		void SetStartTime(const Time& newVal);
		void SetSeries(const ImageSeries& series);

		// Convinience methods
		const Image* GetImage(const std::string& sopInstanceUID) const;

	protected:
		int _cagridId;
		std::string _instanceUID; // Study Instance UID
		Date _startDate;
		Time _startTime;
		ImageSeries _series;
	};
}

#endif // _AIMLib_ImageStudy_Class