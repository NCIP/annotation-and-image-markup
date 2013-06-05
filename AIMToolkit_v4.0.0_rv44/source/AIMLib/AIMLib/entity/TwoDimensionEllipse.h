/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_TwoDimensionEllipse_Class_
#define _AIMLib_TwoDimensionEllipse_Class_

namespace aim_lib
{
	class AIMLIB_API TwoDimensionEllipse : public TwoDimensionGeometricShapeEntity
	{
	public:
		TwoDimensionEllipse();
		TwoDimensionEllipse(const TwoDimensionEllipse& ellipse);
		virtual ~TwoDimensionEllipse();
		virtual TwoDimensionEllipse* Clone() const;

		virtual const TwoDimensionShapeType GetShapeType() const;

		const TwoDimensionSpatialCoordinateVector& GetEllipseCollection();
		void SetEllipseCollection(const TwoDimensionSpatialCoordinateVector& ellipseCollection);
	};
}
#endif // _AIMLib_TwoDimensionEllipse_Class_
