/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_TwoDimensionGeometricShapeEntity_Class_
#define _AIMLib_TwoDimensionGeometricShapeEntity_Class_

#include <string>
#include <vector>

namespace aim_lib
{
// NOTE: These are internal library definitions and should be treated as such
#define C_SHAPE_NAME_CIRCLE_2D		std::string("2D Circle")
#define C_SHAPE_NAME_POINT_2D		std::string("2D Point")
#define C_SHAPE_NAME_MULTIPOINT_2D	std::string("2D Multipoint")
#define C_SHAPE_NAME_ELLIPSE_2D		std::string("2D Ellipse")
#define C_SHAPE_NAME_POLYLINE_2D	std::string("2D Polyline")

	class AIMLIB_API TwoDimensionGeometricShapeEntity : public GeometricShapeEntity
	{
	public:
		enum TwoDimensionShapeType
		{
			Circle_2D,
			Point_2D,
			Multipoint_2D,
			Ellipse_2D,
			Polyline_2D,
			Unknown = -1
		};

	public:
		TwoDimensionGeometricShapeEntity& operator=(const TwoDimensionGeometricShapeEntity& geoShapeEntity);
		virtual ~TwoDimensionGeometricShapeEntity();
		virtual TwoDimensionGeometricShapeEntity* Clone() const = 0;

		const iso_21090::II* GetImageReferenceUid() const;
		int GetReferencedFrameNumber() const;
		const std::string& GetUri() const;
		const TwoDimensionSpatialCoordinateVector& GetTwoDimensionSpatialCoordinateCollection() const;

		void SetImageReferenceUid(const iso_21090::II* newVal);
		void SetReferencedFrameNumber(int newVal);
		void SetUri(const std::string& newVal);
		virtual void SetTwoDimensionSpatialCoordinateCollection(const TwoDimensionSpatialCoordinateVector& spatialCoordinateCollection);

		virtual const TwoDimensionShapeType GetShapeType() const = 0;

	protected:
		TwoDimensionGeometricShapeEntity(const std::string& typeName, long numOfPoints = -1);
		TwoDimensionGeometricShapeEntity(const TwoDimensionGeometricShapeEntity& geoShapeEntity);

		std::auto_ptr<iso_21090::II> _imageReferenceUid;
		int _referencedFrameNumber; // Invalid: -1
		std::string _uri;
		TwoDimensionSpatialCoordinateVector _twoDimensionSpatialCoordinateCollection;

		long _numOfPoints;
	};
}
#endif // _AIMLib_TwoDimensionGeometricShapeEntity_Class_
