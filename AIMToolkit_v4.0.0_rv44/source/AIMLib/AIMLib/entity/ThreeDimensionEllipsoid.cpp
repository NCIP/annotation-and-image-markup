/*
*  2007 – 2013 Copyright Northwestern University
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
#include "ThreeDimensionEllipsoid.h"

#include "../memdebug.h"

using namespace aim_lib;

ThreeDimensionEllipsoid::ThreeDimensionEllipsoid() : ThreeDimensionGeometricShapeEntity(C_SHAPE_NAME_ELLIPSOID_3D, 6){
}

ThreeDimensionEllipsoid::ThreeDimensionEllipsoid(const ThreeDimensionEllipsoid& threeDimensionEllipsoid) : ThreeDimensionGeometricShapeEntity(threeDimensionEllipsoid){
}

ThreeDimensionEllipsoid::~ThreeDimensionEllipsoid(){
}

ThreeDimensionEllipsoid* ThreeDimensionEllipsoid::Clone() const{
	return new ThreeDimensionEllipsoid(*this);
}

const ThreeDimensionGeometricShapeEntity::ThreeDimensionShapeType ThreeDimensionEllipsoid::GetShapeType() const{
	return Ellipsoid_3D;
}

const ThreeDimensionSpatialCoordinateVector& ThreeDimensionEllipsoid::GetEllipsoidCollection(){
	return ThreeDimensionGeometricShapeEntity::GetThreeDimensionSpatialCoordinateCollection();
}

const ThreeDimensionSpatialCoordinate& ThreeDimensionEllipsoid::GetAxisPointA1() const{
	assert(_threeDimensionSpatialCoordinateCollection.size() > AxisA1);
	return _threeDimensionSpatialCoordinateCollection[AxisA1];
}

const ThreeDimensionSpatialCoordinate& ThreeDimensionEllipsoid::GetAxisPointA2() const{
	assert(_threeDimensionSpatialCoordinateCollection.size() > AxisA2);
	return _threeDimensionSpatialCoordinateCollection[AxisA2];
}

const ThreeDimensionSpatialCoordinate& ThreeDimensionEllipsoid::GetAxisPointB1() const{
	assert(_threeDimensionSpatialCoordinateCollection.size() > AxisB1);
	return _threeDimensionSpatialCoordinateCollection[AxisB1];
}

const ThreeDimensionSpatialCoordinate& ThreeDimensionEllipsoid::GetAxisPointB2() const{
	assert(_threeDimensionSpatialCoordinateCollection.size() > AxisB2);
	return _threeDimensionSpatialCoordinateCollection[AxisB2];
}

const ThreeDimensionSpatialCoordinate& ThreeDimensionEllipsoid::GetAxisPointC1() const{
	assert(_threeDimensionSpatialCoordinateCollection.size() > AxisC1);
	return _threeDimensionSpatialCoordinateCollection[AxisC1];
}

const ThreeDimensionSpatialCoordinate& ThreeDimensionEllipsoid::GetAxisPointC2() const{
	assert(_threeDimensionSpatialCoordinateCollection.size() > AxisC2);
	return _threeDimensionSpatialCoordinateCollection[AxisC2];
}

void ThreeDimensionEllipsoid::SetEllipsoidCollection(const ThreeDimensionSpatialCoordinateVector& ellipsoidCollection){
	assert(ellipsoidCollection.size() == 6);
	ThreeDimensionGeometricShapeEntity::SetThreeDimensionSpatialCoordinateCollection(ellipsoidCollection);
}

void ThreeDimensionEllipsoid::SetAxisPointA1(const ThreeDimensionSpatialCoordinate& newVal){
	assert(_threeDimensionSpatialCoordinateCollection.size() > AxisA1);
	_threeDimensionSpatialCoordinateCollection[AxisA1] = newVal;
}

void ThreeDimensionEllipsoid::SetAxisPointA2(const ThreeDimensionSpatialCoordinate& newVal){
	assert(_threeDimensionSpatialCoordinateCollection.size() > AxisA2);
	_threeDimensionSpatialCoordinateCollection[AxisA2] = newVal;
}

void ThreeDimensionEllipsoid::SetAxisPointB1(const ThreeDimensionSpatialCoordinate& newVal){
	assert(_threeDimensionSpatialCoordinateCollection.size() > AxisB1);
	_threeDimensionSpatialCoordinateCollection[AxisB1] = newVal;
}

void ThreeDimensionEllipsoid::SetAxisPointB2(const ThreeDimensionSpatialCoordinate& newVal){
	assert(_threeDimensionSpatialCoordinateCollection.size() > AxisB2);
	_threeDimensionSpatialCoordinateCollection[AxisB2] = newVal;
}

void ThreeDimensionEllipsoid::SetAxisPointC1(const ThreeDimensionSpatialCoordinate& newVal){
	assert(_threeDimensionSpatialCoordinateCollection.size() > AxisC1);
	_threeDimensionSpatialCoordinateCollection[AxisC1] = newVal;
}

void ThreeDimensionEllipsoid::SetAxisPointC2(const ThreeDimensionSpatialCoordinate& newVal){
	assert(_threeDimensionSpatialCoordinateCollection.size() > AxisC2);
	_threeDimensionSpatialCoordinateCollection[AxisC2] = newVal;
}
