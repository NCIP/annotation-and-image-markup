/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#pragma once
#ifndef _AIMLib_TwoDimensionPoint_Class_
#define _AIMLib_TwoDimensionPoint_Class_

namespace aim_lib
{
	class AIMLIB_API TwoDimensionPoint : public TwoDimensionGeometricShapeEntity
	{
	public:
		TwoDimensionPoint();
		TwoDimensionPoint(const TwoDimensionPoint& point);
		virtual ~TwoDimensionPoint();
		virtual TwoDimensionPoint* Clone() const;

		virtual const TwoDimensionShapeType GetShapeType() const;

		const TwoDimensionSpatialCoordinate& GetCenter();
		void SetCenter(const TwoDimensionSpatialCoordinate& spatialCoordinate);

	protected:
		enum PointCoordinateIndex
		{
			CenterPoint = 0
		};
	};
}
#endif // _AIMLib_TwoDimensionPoint_Class_
