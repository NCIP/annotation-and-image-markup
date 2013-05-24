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
#include "ThreeDimensionPoint.h"

#include "../memdebug.h"

using namespace aim_lib;

ThreeDimensionPoint::ThreeDimensionPoint() : ThreeDimensionGeometricShapeEntity(C_SHAPE_NAME_POINT_3D, 1){
}

ThreeDimensionPoint::ThreeDimensionPoint(const ThreeDimensionPoint& point) : ThreeDimensionGeometricShapeEntity(point){
}

ThreeDimensionPoint::~ThreeDimensionPoint(){
}

ThreeDimensionPoint* ThreeDimensionPoint::Clone() const{
	return new ThreeDimensionPoint(*this);
}

const ThreeDimensionGeometricShapeEntity::ThreeDimensionShapeType ThreeDimensionPoint::GetShapeType() const{
	return Point_3D;
}

const ThreeDimensionSpatialCoordinate& ThreeDimensionPoint::GetCenter(){
	assert(_threeDimensionSpatialCoordinateCollection.size() > CenterPoint);
	return _threeDimensionSpatialCoordinateCollection[CenterPoint];
}

void ThreeDimensionPoint::SetCenter(const ThreeDimensionSpatialCoordinate& spatialCoordinate){
	assert(_threeDimensionSpatialCoordinateCollection.size() > CenterPoint);
	_threeDimensionSpatialCoordinateCollection[CenterPoint] = spatialCoordinate;
}
