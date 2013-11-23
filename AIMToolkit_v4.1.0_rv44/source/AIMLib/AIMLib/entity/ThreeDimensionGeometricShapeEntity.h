/*
Copyright (c) 2008-2013, Northwestern University
All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 
  Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
 
  Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
 
  Neither the name of the Northwestern University nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
