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
#include "ThreeDimensionEllipse.h"

#include "../memdebug.h"

using namespace aim_lib;

ThreeDimensionEllipse::ThreeDimensionEllipse() : ThreeDimensionGeometricShapeEntity(C_SHAPE_NAME_ELLIPSE_3D, 4){
}

ThreeDimensionEllipse::ThreeDimensionEllipse(const ThreeDimensionEllipse& ellipse) : ThreeDimensionGeometricShapeEntity(ellipse){
}

ThreeDimensionEllipse::~ThreeDimensionEllipse(){
}

ThreeDimensionEllipse* ThreeDimensionEllipse::Clone() const{
	return new ThreeDimensionEllipse(*this);
}

const ThreeDimensionGeometricShapeEntity::ThreeDimensionShapeType ThreeDimensionEllipse::GetShapeType() const{
	return Ellipse_3D;
}

const ThreeDimensionSpatialCoordinateVector& ThreeDimensionEllipse::GetEllipseCollection(){
	return ThreeDimensionGeometricShapeEntity::GetThreeDimensionSpatialCoordinateCollection();
}

const ThreeDimensionSpatialCoordinate& ThreeDimensionEllipse::GetMajorAxisPoint1() const{
	assert(_threeDimensionSpatialCoordinateCollection.size() > MajorAxis1);
	return _threeDimensionSpatialCoordinateCollection[MajorAxis1];
}

const ThreeDimensionSpatialCoordinate& ThreeDimensionEllipse::GetMajorAxisPoint2() const{
	assert(_threeDimensionSpatialCoordinateCollection.size() > MajorAxis2);
	return _threeDimensionSpatialCoordinateCollection[MajorAxis2];
}

const ThreeDimensionSpatialCoordinate& ThreeDimensionEllipse::GetMinorAxisPoint1() const{
	assert(_threeDimensionSpatialCoordinateCollection.size() > MinorAxis1);
	return _threeDimensionSpatialCoordinateCollection[MinorAxis1];
}

const ThreeDimensionSpatialCoordinate& ThreeDimensionEllipse::GetMinorAxisPoint2() const{
	assert(_threeDimensionSpatialCoordinateCollection.size() > MinorAxis2);
	return _threeDimensionSpatialCoordinateCollection[MinorAxis2];
}

void ThreeDimensionEllipse::SetEllipseCollection(const ThreeDimensionSpatialCoordinateVector& ellipseCollection){
	assert(ellipseCollection.size() == 4);
	ThreeDimensionGeometricShapeEntity::SetThreeDimensionSpatialCoordinateCollection(ellipseCollection);
}

void ThreeDimensionEllipse::SetMajorAxisPoint1(const ThreeDimensionSpatialCoordinate& newVal){
	assert(_threeDimensionSpatialCoordinateCollection.size() > MajorAxis1);
	_threeDimensionSpatialCoordinateCollection[MajorAxis1] = newVal;
}

void ThreeDimensionEllipse::SetMajorAxisPoint2(const ThreeDimensionSpatialCoordinate& newVal){
	assert(_threeDimensionSpatialCoordinateCollection.size() > MajorAxis2);
	_threeDimensionSpatialCoordinateCollection[MajorAxis2] = newVal;
}

void ThreeDimensionEllipse::SetMinorAxisPoint1(const ThreeDimensionSpatialCoordinate& newVal){
	assert(_threeDimensionSpatialCoordinateCollection.size() > MinorAxis1);
	_threeDimensionSpatialCoordinateCollection[MinorAxis1] = newVal;
}

void ThreeDimensionEllipse::SetMinorAxisPoint2(const ThreeDimensionSpatialCoordinate& newVal){
	assert(_threeDimensionSpatialCoordinateCollection.size() > MinorAxis2);
	_threeDimensionSpatialCoordinateCollection[MinorAxis2] = newVal;
}
