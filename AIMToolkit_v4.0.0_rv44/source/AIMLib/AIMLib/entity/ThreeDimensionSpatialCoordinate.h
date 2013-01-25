/*
Copyright (c) 2008-2013, Northwestern University
All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 
  Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
 
  Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
 
  Neither the name of the Northwestern University nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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
