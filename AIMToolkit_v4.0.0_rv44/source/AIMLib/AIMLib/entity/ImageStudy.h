/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef _AIMLib_ImageStudy_Class_
#define _AIMLib_ImageStudy_Class_

#include <string>

namespace aim_lib
{
	class AIMLIB_API ImageStudy
	{
	public:
		ImageStudy();
		ImageStudy(const ImageStudy& study);
		virtual ~ImageStudy();

		const iso_21090::II& GetInstanceUid() const;
		const Date& GetStartDate() const;
		const Time& GetStartTime() const;
		const std::string& GetProceduDescription() const;
		const ImageSeries& GetImageSeries() const;
		const ReferencedDicomObjectVector& GetReferencedDicomObjectCollection() const;
		void SetInstanceUid(const iso_21090::II& newVal);
		void SetStartDate(const Date& newVal);
		void SetStartTime(const Time& newVal);
		void SetProcedureDescription(const std::string& newVal);
		void SetImageSeries(const ImageSeries& imageSeries);
		void SetReferencedDicomObjectCollection(const ReferencedDicomObjectVector& referencedDicomObjects);

		// Convinience methods
		const Image* GetImage(const iso_21090::II& sopInstanceUid) const;

	protected:
		iso_21090::II _instanceUid; // Study Instance UID
		Date _startDate;
		Time _startTime;
		std::string _procedureDecription;
		ImageSeries _imageSeries;
		ReferencedDicomObjectVector _referencedDicomObjectCollection;
	};
}

#endif // _AIMLib_ImageStudy_Class_
