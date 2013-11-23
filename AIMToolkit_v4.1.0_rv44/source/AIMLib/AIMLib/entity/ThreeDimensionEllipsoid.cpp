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
