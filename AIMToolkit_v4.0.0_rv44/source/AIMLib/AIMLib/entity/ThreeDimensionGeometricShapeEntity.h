/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#pragma once
#ifndef _AIMLib_ThreeDimensionGeometricShapeEntity_Class_
#define _AIMLib_ThreeDimensionGeometricShapeEntity_Class_

#include <string>
#include <vector>

namespace aim_lib
{
// NOTE: These are internal library definitions and should be treated as such
#define C_SHAPE_NAME_ELLIPSOID_3D	std::string("3D Ellipsoid")
#define C_SHAPE_NAME_ELLIPSE_3D		std::string("3D Ellipse")
#define C_SHAPE_NAME_POINT_3D		std::string("3D Point")
#define C_SHAPE_NAME_MULTIPOINT_3D	std::string("3D Multipoint")
#define C_SHAPE_NAME_POLYLINE_3D	std::string("3D Polyline")
#define C_SHAPE_NAME_POLYGON_3D		std::string("3D Polygon")

	class AIMLIB_API ThreeDimensionGeometricShapeEntity : public GeometricShapeEntity
	{
	public:
		enum ThreeDimensionShapeType
		{
			Ellipsoid_3D,
			Ellipse_3D,
			Point_3D,
			Multipoint_3D,
			Polyline_3D,
			Polygon_3D,
			Unknown = -1
		};

	public:
		ThreeDimensionGeometricShapeEntity& operator=(const ThreeDimensionGeometricShapeEntity& geoShapeEntity);
		virtual ~ThreeDimensionGeometricShapeEntity();
		virtual ThreeDimensionGeometricShapeEntity* Clone() const = 0;

		const iso_21090::II* GetFrameOfReferenceUid() const;
		const iso_21090::II* GetFiducialUid() const;
		const ThreeDimensionSpatialCoordinateVector& GetThreeDimensionSpatialCoordinateCollection() const;

		void SetFrameOfReferenceUid(const iso_21090::II* newVal);
		void SetFiducialUid(const iso_21090::II* newVal);
		virtual void SetThreeDimensionSpatialCoordinateCollection(const ThreeDimensionSpatialCoordinateVector& spatialCoordinateCollection);

		virtual const ThreeDimensionShapeType GetShapeType() const = 0;

	protected:
		ThreeDimensionGeometricShapeEntity(const std::string& typeName, long numOfPoints = -1);
		ThreeDimensionGeometricShapeEntity(const ThreeDimensionGeometricShapeEntity& geoShapeEntity);

		std::auto_ptr<iso_21090::II> _frameOfReferenceUid;
		std::auto_ptr<iso_21090::II> _fiducialUid;
		ThreeDimensionSpatialCoordinateVector _threeDimensionSpatialCoordinateCollection;

		long _numOfPoints;
	};
}
#endif // _AIMLib_ThreeDimensionGeometricShapeEntity_Class_
