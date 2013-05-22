/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_ThreeDimensionPolyline_Class_
#define _AIMLib_ThreeDimensionPolyline_Class_

namespace aim_lib
{
	/*
	POLYLINE = a series of connected line segments with ordered vertices denoted by (x,y,z) triplets; the
	points need not be coplanar.
	*/
	class AIMLIB_API ThreeDimensionPolyline : public ThreeDimensionGeometricShapeEntity
	{
	public:
		ThreeDimensionPolyline();
		ThreeDimensionPolyline(const ThreeDimensionPolyline& polyline);
		virtual ~ThreeDimensionPolyline();
		virtual ThreeDimensionPolyline* Clone() const;

		virtual const ThreeDimensionShapeType GetShapeType() const;
	};
}
#endif // _AIMLib_ThreeDimensionPolyline_Class_
