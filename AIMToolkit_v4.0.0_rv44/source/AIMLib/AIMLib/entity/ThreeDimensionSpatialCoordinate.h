/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#pragma once
#ifndef _AIMLib_ThreeDimensionSpatialCoordinate_Class_
#define _AIMLib_ThreeDimensionSpatialCoordinate_Class_

#include <vector>

namespace aim_lib
{
	class ThreeDimensionSpatialCoordinate;
	typedef std::vector<ThreeDimensionSpatialCoordinate> ThreeDimensionSpatialCoordinateVector;

	class AIMLIB_API ThreeDimensionSpatialCoordinate
	{
	public:
		ThreeDimensionSpatialCoordinate();
		ThreeDimensionSpatialCoordinate(double x, double y, double z, ThreeDimensionSpatialCoordinateVector::size_type coordinateIndex);
		ThreeDimensionSpatialCoordinate(const ThreeDimensionSpatialCoordinate& spatialCoordinate);
		virtual ~ThreeDimensionSpatialCoordinate();
		virtual ThreeDimensionSpatialCoordinate* Clone() const;

		double GetX() const;
		double GetY() const;
		double GetZ() const;
		int GetCoordinateIndex() const;
		void SetX(double newVal);
		void SetY(double newVal);
		void SetZ(double newVal);
		void SetCoordinateIndex(int newVal);

		// Spatial Coordinates Sorting Predicate
		static bool SpatialCoordinateSortPredicate(const ThreeDimensionSpatialCoordinate& coord1, const ThreeDimensionSpatialCoordinate& coord2);

	private:
		double _x;
		double _y;
		double _z;
		int _coordinateIndex;
	};
}
#endif // _AIMLib_ThreeDimensionSpatialCoordinate_Class_
