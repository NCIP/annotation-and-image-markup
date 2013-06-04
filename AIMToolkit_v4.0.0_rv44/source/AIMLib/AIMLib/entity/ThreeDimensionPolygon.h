/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_ThreeDimensionPolygon_Class_
#define _AIMLib_ThreeDimensionPolygon_Class_

namespace aim_lib
{
	/*
	POLYGON = a series of connected line segments with ordered vertices denoted by (x,y,z) triplets,
	where the first and last vertices shall be the same forming a polygon; the points shall be coplanar.
	*/
	class AIMLIB_API ThreeDimensionPolygon : public ThreeDimensionGeometricShapeEntity
	{
	public:
		ThreeDimensionPolygon();
		ThreeDimensionPolygon(const ThreeDimensionPolygon& polygon);
		virtual ~ThreeDimensionPolygon();
		virtual ThreeDimensionPolygon* Clone() const;

		virtual const ThreeDimensionShapeType GetShapeType() const;
	};
}
#endif // _AIMLib_ThreeDimensionPolygon_Class_
