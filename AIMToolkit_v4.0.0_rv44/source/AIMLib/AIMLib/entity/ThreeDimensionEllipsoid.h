/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
