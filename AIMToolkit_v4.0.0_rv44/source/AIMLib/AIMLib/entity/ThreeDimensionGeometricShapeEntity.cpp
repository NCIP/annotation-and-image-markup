/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
