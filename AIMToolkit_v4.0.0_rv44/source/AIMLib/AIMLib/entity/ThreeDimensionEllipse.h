/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
L*/

#pragma once
#ifndef _AIMLib_ThreeDimensionEllipse_Class_
#define _AIMLib_ThreeDimensionEllipse_Class_

namespace aim_lib
{
	/*
	ELLIPSE = an ellipse defined by four (x,y,z) triplets, the first two triplets specifying the endpoints of the
	major axis and the second two triplets specifying the endpoints of the minor axis.
	*/
	class AIMLIB_API ThreeDimensionEllipse : public ThreeDimensionGeometricShapeEntity
	{
	public:
		ThreeDimensionEllipse();
		ThreeDimensionEllipse(const ThreeDimensionEllipse& ellipse);
		virtual ~ThreeDimensionEllipse();
		virtual ThreeDimensionEllipse* Clone() const;

		virtual const ThreeDimensionShapeType GetShapeType() const;

		const ThreeDimensionSpatialCoordinateVector& GetEllipseCollection();
		const ThreeDimensionSpatialCoordinate& GetMajorAxisPoint1() const;
		const ThreeDimensionSpatialCoordinate& GetMajorAxisPoint2() const;
		const ThreeDimensionSpatialCoordinate& GetMinorAxisPoint1() const;
		const ThreeDimensionSpatialCoordinate& GetMinorAxisPoint2() const;

		void SetEllipseCollection(const ThreeDimensionSpatialCoordinateVector& ellipseCollection);
		void SetMajorAxisPoint1(const ThreeDimensionSpatialCoordinate& newVal);
		void SetMajorAxisPoint2(const ThreeDimensionSpatialCoordinate& newVal);
		void SetMinorAxisPoint1(const ThreeDimensionSpatialCoordinate& newVal);
		void SetMinorAxisPoint2(const ThreeDimensionSpatialCoordinate& newVal);
	protected:
		enum EllipseCoordinateIndex
		{
			MajorAxis1 = 0,
			MajorAxis2 = 1,
			MinorAxis1 = 2,
			MinorAxis2 = 3
		};
	};
}
#endif // _AIMLib_ThreeDimensionEllipse_Class_
