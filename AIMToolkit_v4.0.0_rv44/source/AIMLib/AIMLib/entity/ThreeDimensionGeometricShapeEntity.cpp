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

#include "../stdafx.h"

#include "Entity.h"
#include "MarkupEntity.h"
#include "GeometricShapeEntity.h"
#include "ThreeDimensionSpatialCoordinate.h"
#include "ThreeDimensionGeometricShapeEntity.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;
using iso_21090::II;

ThreeDimensionGeometricShapeEntity::ThreeDimensionGeometricShapeEntity(const string& typeName, long numOfPoints /*=-1*/) : GeometricShapeEntity(typeName){
	_numOfPoints = numOfPoints;

	// Ensure that we have required number of points
	while(_numOfPoints >= 0 && _threeDimensionSpatialCoordinateCollection.size() <  (ThreeDimensionSpatialCoordinateVector::size_type)_numOfPoints)
	{
		ThreeDimensionSpatialCoordinate spatialCoord(0, 0, 0, _threeDimensionSpatialCoordinateCollection.size());
		_threeDimensionSpatialCoordinateCollection.push_back(spatialCoord);
	}
}

ThreeDimensionGeometricShapeEntity::ThreeDimensionGeometricShapeEntity(const ThreeDimensionGeometricShapeEntity& geoShapeEntity) : GeometricShapeEntity(geoShapeEntity){
	*this = geoShapeEntity;
}

ThreeDimensionGeometricShapeEntity& ThreeDimensionGeometricShapeEntity::operator =(const ThreeDimensionGeometricShapeEntity& geoShapeEntity){

	if (this != &geoShapeEntity)
	{
		GeometricShapeEntity::operator=(geoShapeEntity);
		_numOfPoints			= geoShapeEntity._numOfPoints;

		SetFrameOfReferenceUid(geoShapeEntity.GetFrameOfReferenceUid());
		SetFiducialUid(geoShapeEntity.GetFiducialUid());
		SetThreeDimensionSpatialCoordinateCollection(geoShapeEntity.GetThreeDimensionSpatialCoordinateCollection());
	}

	return *this;
}

ThreeDimensionGeometricShapeEntity::~ThreeDimensionGeometricShapeEntity(){
}

const II* ThreeDimensionGeometricShapeEntity::GetFrameOfReferenceUid() const {
	return _frameOfReferenceUid.get();
}

const II* ThreeDimensionGeometricShapeEntity::GetFiducialUid() const {
	return _fiducialUid.get();
}

const ThreeDimensionSpatialCoordinateVector& ThreeDimensionGeometricShapeEntity::GetThreeDimensionSpatialCoordinateCollection() const{
	return _threeDimensionSpatialCoordinateCollection;
}

void ThreeDimensionGeometricShapeEntity::SetFrameOfReferenceUid(const II* newVal){
	_frameOfReferenceUid.reset(newVal ? new II(*newVal) : NULL);
}

void ThreeDimensionGeometricShapeEntity::SetFiducialUid(const II* newVal){
	_fiducialUid.reset(newVal ? new II(*newVal) : NULL);
}

void ThreeDimensionGeometricShapeEntity::SetThreeDimensionSpatialCoordinateCollection(const ThreeDimensionSpatialCoordinateVector& spatialCoordinateCollection){
	_threeDimensionSpatialCoordinateCollection.assign(spatialCoordinateCollection.begin(), spatialCoordinateCollection.end());
}
