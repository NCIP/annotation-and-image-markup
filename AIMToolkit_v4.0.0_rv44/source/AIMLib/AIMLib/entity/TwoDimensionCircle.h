/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_TwoDimensionCircle_Class_
#define _AIMLib_TwoDimensionCircle_Class_

namespace aim_lib
{
	class AIMLIB_API TwoDimensionCircle : public TwoDimensionGeometricShapeEntity
	{
	public:
		TwoDimensionCircle();
		TwoDimensionCircle(const TwoDimensionCircle& twoDimensionCircle);
		virtual ~TwoDimensionCircle();
		virtual TwoDimensionCircle* Clone() const;

		virtual const TwoDimensionShapeType GetShapeType() const;

		const TwoDimensionSpatialCoordinate& GetCenter() const;
		const TwoDimensionSpatialCoordinate& GetRadiusPoint() const;
		void SetCenter(const TwoDimensionSpatialCoordinate& center);
		void SetRadiusPoint(const TwoDimensionSpatialCoordinate& radiusPoint);

	protected:
		enum CircleCoordinateIndex
		{
			CenterPoint = 0,
			CircumferencePoint = 1
		};

	};
}
#endif // _AIMLib_TwoDimensionCircle_Class_
