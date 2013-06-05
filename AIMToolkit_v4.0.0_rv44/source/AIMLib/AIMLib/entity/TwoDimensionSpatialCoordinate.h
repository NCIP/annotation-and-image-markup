/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_TwoDimensionSpatialCoordinate_Class_
#define _AIMLib_TwoDimensionSpatialCoordinate_Class_

#include <vector>

namespace aim_lib
{
	class TwoDimensionSpatialCoordinate;
	typedef std::vector<TwoDimensionSpatialCoordinate> TwoDimensionSpatialCoordinateVector;

	class AIMLIB_API TwoDimensionSpatialCoordinate
	{
	public:
		TwoDimensionSpatialCoordinate();
		TwoDimensionSpatialCoordinate(double x, double y, TwoDimensionSpatialCoordinateVector::size_type coordinateIndex);
		TwoDimensionSpatialCoordinate(const TwoDimensionSpatialCoordinate& spatialCoordinate);
		virtual ~TwoDimensionSpatialCoordinate();
		virtual TwoDimensionSpatialCoordinate* Clone() const;

		double GetX() const;
		double GetY() const;
		TwoDimensionSpatialCoordinateVector::size_type GetCoordinateIndex() const;
		void SetX(double newVal);
		void SetY(double newVal);
		void SetCoordinateIndex(TwoDimensionSpatialCoordinateVector::size_type newVal);

		// Spatial Coordinates Sorting Predicate
		static bool SpatialCoordinateSortPredicate(const TwoDimensionSpatialCoordinate& coord1, const TwoDimensionSpatialCoordinate& coord2);

	private:
		double _x;
		double _y;
		TwoDimensionSpatialCoordinateVector::size_type _coordinateIndex;
	};
}
#endif // _AIMLib_TwoDimensionSpatialCoordinate_Class_
