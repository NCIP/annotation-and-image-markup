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
#include "TwoDimensionCircle.h"

#include "../memdebug.h"

using namespace aim_lib;

TwoDimensionCircle::TwoDimensionCircle() : TwoDimensionGeometricShapeEntity(C_SHAPE_NAME_CIRCLE_2D, 2){
}

TwoDimensionCircle::TwoDimensionCircle(const TwoDimensionCircle& twoDimensionCircle) : TwoDimensionGeometricShapeEntity(twoDimensionCircle){
}

TwoDimensionCircle::~TwoDimensionCircle(){
}

TwoDimensionCircle* TwoDimensionCircle::Clone() const{
	return new TwoDimensionCircle(*this);
}

const TwoDimensionGeometricShapeEntity::TwoDimensionShapeType TwoDimensionCircle::GetShapeType() const{
	return Circle_2D;
}

const TwoDimensionSpatialCoordinate& TwoDimensionCircle::GetCenter() const{
	assert(_twoDimensionSpatialCoordinateCollection.size() > CenterPoint);
	return _twoDimensionSpatialCoordinateCollection[CenterPoint];
}

const TwoDimensionSpatialCoordinate& TwoDimensionCircle::GetRadiusPoint() const{
	assert(_twoDimensionSpatialCoordinateCollection.size() > CircumferencePoint);
	return _twoDimensionSpatialCoordinateCollection[CircumferencePoint];
}

void TwoDimensionCircle::SetCenter(const TwoDimensionSpatialCoordinate& center){
	assert(_twoDimensionSpatialCoordinateCollection.size() > CenterPoint);
	_twoDimensionSpatialCoordinateCollection[CenterPoint] = center;
}

void TwoDimensionCircle::SetRadiusPoint(const TwoDimensionSpatialCoordinate& radiusPoint){
	assert(_twoDimensionSpatialCoordinateCollection.size() > CircumferencePoint);
	_twoDimensionSpatialCoordinateCollection[CircumferencePoint] = radiusPoint;
}
