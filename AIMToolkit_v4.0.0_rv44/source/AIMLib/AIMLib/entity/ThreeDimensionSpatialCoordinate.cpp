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

#include "ThreeDimensionSpatialCoordinate.h"

#include "../memdebug.h"

using namespace aim_lib;

ThreeDimensionSpatialCoordinate::ThreeDimensionSpatialCoordinate(){
}

ThreeDimensionSpatialCoordinate::ThreeDimensionSpatialCoordinate(double x, double y, double z, ThreeDimensionSpatialCoordinateVector::size_type coordinateIndex) :
	_x(x), _y(y), _z(z), _coordinateIndex(coordinateIndex){
}

ThreeDimensionSpatialCoordinate::ThreeDimensionSpatialCoordinate(const ThreeDimensionSpatialCoordinate& spatialCoordinate){
	_x					= spatialCoordinate._x;
	_y					= spatialCoordinate._y;
	_z					= spatialCoordinate._z;
	_coordinateIndex	= spatialCoordinate._coordinateIndex;
}

ThreeDimensionSpatialCoordinate::~ThreeDimensionSpatialCoordinate(){
}

ThreeDimensionSpatialCoordinate* ThreeDimensionSpatialCoordinate::Clone() const{
	return new ThreeDimensionSpatialCoordinate(*this);
}

double ThreeDimensionSpatialCoordinate::GetX() const{
	return _x;
}

double ThreeDimensionSpatialCoordinate::GetY() const{
	return _y;
}

double ThreeDimensionSpatialCoordinate::GetZ() const{
	return _z;
}

int ThreeDimensionSpatialCoordinate::GetCoordinateIndex() const{
	return _coordinateIndex;
}

void ThreeDimensionSpatialCoordinate::SetX(double newVal){
	_x = newVal;
}

void ThreeDimensionSpatialCoordinate::SetY(double newVal){
	_y = newVal;
}

void ThreeDimensionSpatialCoordinate::SetZ(double newVal){
	_z = newVal;
}

void ThreeDimensionSpatialCoordinate::SetCoordinateIndex(int newVal){
	_coordinateIndex = newVal;
}

bool ThreeDimensionSpatialCoordinate::SpatialCoordinateSortPredicate(const ThreeDimensionSpatialCoordinate& coord1, const ThreeDimensionSpatialCoordinate& coord2)
{
	return coord1.GetCoordinateIndex() < coord2.GetCoordinateIndex();
}
