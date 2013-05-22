/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#if !defined(EA_4FC2DA23_0450_426e_8B36_867467058ADE__INCLUDED_)
#define EA_4FC2DA23_0450_426e_8B36_867467058ADE__INCLUDED_

#include <string>

namespace aim_lib
{
	class AIMLIB_API TwoDimensionSpatialCoordinate : public SpatialCoordinate
	{
	public:
		TwoDimensionSpatialCoordinate();
		TwoDimensionSpatialCoordinate(double x, double y, const std::string& imageReferenceUID, int coordinateIndex, long referenceFrameNumber = 1);
		TwoDimensionSpatialCoordinate(const TwoDimensionSpatialCoordinate& spatialCoordinate);
		virtual ~TwoDimensionSpatialCoordinate();
		virtual TwoDimensionSpatialCoordinate* Clone() const;

		virtual const SpatialCoordinateType GetCoordinateType() const;

		double GetX() const;
		double GetY() const;
		long GetReferencedFrameNumber() const;
		const std::string& GetImageReferenceUID() const;
		void SetX(double newVal);
		void SetY(double newVal);
		void SetReferencedFrameNumber(long newVal);
		void SetImageReferenceUID(const std::string& newVal);

	private:
		double _x;
		double _y;
		long _referencedFrameNumber;
		std::string _imageReferenceUID; // DICOM - SOP Instance UID; Web - image URI

	};
}
#endif // !defined(EA_4FC2DA23_0450_426e_8B36_867467058ADE__INCLUDED_)
