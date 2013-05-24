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
#include "TwoDimensionSpatialCoordinate.h"
#include "TwoDimensionGeometricShapeEntity.h"
#include "TwoDimensionPoint.h"

#include "../memdebug.h"

using namespace aim_lib;

TwoDimensionPoint::TwoDimensionPoint() : TwoDimensionGeometricShapeEntity(C_SHAPE_NAME_POINT_2D, 1){
}

TwoDimensionPoint::TwoDimensionPoint(const TwoDimensionPoint& point) : TwoDimensionGeometricShapeEntity(point){
}

TwoDimensionPoint::~TwoDimensionPoint(){
}

TwoDimensionPoint* TwoDimensionPoint::Clone() const{
	return new TwoDimensionPoint(*this);
}

const TwoDimensionGeometricShapeEntity::TwoDimensionShapeType TwoDimensionPoint::GetShapeType() const{
	return Point_2D;
}

const TwoDimensionSpatialCoordinate& TwoDimensionPoint::GetCenter(){
	assert(_twoDimensionSpatialCoordinateCollection.size() > CenterPoint);
	return _twoDimensionSpatialCoordinateCollection[CenterPoint];
}

void TwoDimensionPoint::SetCenter(const TwoDimensionSpatialCoordinate& spatialCoordinate){
	assert(_twoDimensionSpatialCoordinateCollection.size() > CenterPoint);
	_twoDimensionSpatialCoordinateCollection[CenterPoint] = spatialCoordinate;
}
