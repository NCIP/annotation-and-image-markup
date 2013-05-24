/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#pragma once
#ifndef _AIMLib_ThreeDimensionPoint_Class_
#define _AIMLib_ThreeDimensionPoint_Class_

namespace aim_lib
{
	class AIMLIB_API ThreeDimensionPoint : public ThreeDimensionGeometricShapeEntity
	{
	public:
		ThreeDimensionPoint();
		ThreeDimensionPoint(const ThreeDimensionPoint& point);
		virtual ~ThreeDimensionPoint();
		virtual ThreeDimensionPoint* Clone() const;

		virtual const ThreeDimensionShapeType GetShapeType() const;

		const ThreeDimensionSpatialCoordinate& GetCenter();
		void SetCenter(const ThreeDimensionSpatialCoordinate& spatialCoordinate);

	protected:
		enum PointCoordinateIndex
		{
			CenterPoint = 0
		};
	};
}
#endif // _AIMLib_ThreeDimensionPoint_Class_
