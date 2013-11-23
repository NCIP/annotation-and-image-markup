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
#ifndef _AIMLib_ThreeDimensionEllipsoid_Class_
#define _AIMLib_ThreeDimensionEllipsoid_Class_

namespace aim_lib
{
	/*
	ELLIPSOID = A three-dimensional geometric surface whose plane sections are either ellipses or circles
	and contains three intersecting orthogonal axes, ?a?, ?b?, and ?c?. The ellipsoid is defined by six
	(x,y,z) triplets, the first and second triplets specifying the endpoints of axis ?a?, the third and fourth
	triplets specifying the endpoints of axis ?b?, and the fifth and sixth triplets specifying the endpoints of
	axis ?c?.
	*/
	class AIMLIB_API ThreeDimensionEllipsoid : public ThreeDimensionGeometricShapeEntity
	{
	public:
		ThreeDimensionEllipsoid();
		ThreeDimensionEllipsoid(const ThreeDimensionEllipsoid& threeDimensionEllipsoid);
		virtual ~ThreeDimensionEllipsoid();
		virtual ThreeDimensionEllipsoid* Clone() const;

		virtual const ThreeDimensionShapeType GetShapeType() const;

		const ThreeDimensionSpatialCoordinateVector& GetEllipsoidCollection();
		const ThreeDimensionSpatialCoordinate& GetAxisPointA1() const;
		const ThreeDimensionSpatialCoordinate& GetAxisPointA2() const;
		const ThreeDimensionSpatialCoordinate& GetAxisPointB1() const;
		const ThreeDimensionSpatialCoordinate& GetAxisPointB2() const;
		const ThreeDimensionSpatialCoordinate& GetAxisPointC1() const;
		const ThreeDimensionSpatialCoordinate& GetAxisPointC2() const;

		void SetEllipsoidCollection(const ThreeDimensionSpatialCoordinateVector& ellipsoidCollection);
		void SetAxisPointA1(const ThreeDimensionSpatialCoordinate& newVal);
		void SetAxisPointA2(const ThreeDimensionSpatialCoordinate& newVal);
		void SetAxisPointB1(const ThreeDimensionSpatialCoordinate& newVal);
		void SetAxisPointB2(const ThreeDimensionSpatialCoordinate& newVal);
		void SetAxisPointC1(const ThreeDimensionSpatialCoordinate& newVal);
		void SetAxisPointC2(const ThreeDimensionSpatialCoordinate& newVal);

	protected:
		enum EllipsoidCoordinateIndex
		{
			AxisA1 = 0,
			AxisA2 = 1,
			AxisB1 = 2,
			AxisB2 = 3,
			AxisC1 = 4,
			AxisC2 = 5
		};
	};
}
#endif // _AIMLib_ThreeDimensionEllipsoid_Class_
