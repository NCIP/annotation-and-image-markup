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
