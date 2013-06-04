/*
  Classname: ThreeDimensionSpatialCoordinate

*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

*/

#if !defined(EA_787096FC_52CB_4814_871F_CD3748135237__INCLUDED_)
#define EA_787096FC_52CB_4814_871F_CD3748135237__INCLUDED_

#include <string>

namespace aim_lib
{
	class AIMLIB_API ThreeDimensionSpatialCoordinate : public SpatialCoordinate
	{

	public:
		ThreeDimensionSpatialCoordinate();
		ThreeDimensionSpatialCoordinate(double x, double y, double z, const std::string& frameOfReferenceUID, int coordinateIndex);
		ThreeDimensionSpatialCoordinate(const ThreeDimensionSpatialCoordinate& spatialCoordinate);
		virtual ~ThreeDimensionSpatialCoordinate();
		virtual ThreeDimensionSpatialCoordinate* Clone() const;

		virtual const SpatialCoordinateType GetCoordinateType() const;

		double GetX() const;
		double GetY() const;
		double GetZ() const;
		const std::string& GetFrameOfReferenceUID() const;
		void SetX(double newVal);
		void SetY(double newVal);
		void SetZ(double newVal);
		void SetFrameOfReferenceUID(const std::string& newVal);

	private:
		double _x;
		double _y;
		double _z;
		std::string _frameOfReferenceUID;
	};
}
#endif // !defined(EA_787096FC_52CB_4814_871F_CD3748135237__INCLUDED_)
