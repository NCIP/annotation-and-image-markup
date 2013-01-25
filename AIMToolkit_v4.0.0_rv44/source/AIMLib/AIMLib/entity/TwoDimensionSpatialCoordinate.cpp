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

#include "TwoDimensionSpatialCoordinate.h"

#include "../memdebug.h"

using namespace aim_lib;

TwoDimensionSpatialCoordinate::TwoDimensionSpatialCoordinate(){
}

TwoDimensionSpatialCoordinate::TwoDimensionSpatialCoordinate(double x, double y, TwoDimensionSpatialCoordinateVector::size_type coordinateIndex) :
				_x(x), _y(y), _coordinateIndex(coordinateIndex){
}

TwoDimensionSpatialCoordinate::TwoDimensionSpatialCoordinate(const TwoDimensionSpatialCoordinate& spatialCoordinate){
	_x					= spatialCoordinate._x;
	_y					= spatialCoordinate._y;
	_coordinateIndex	= spatialCoordinate._coordinateIndex;
}

TwoDimensionSpatialCoordinate::~TwoDimensionSpatialCoordinate(){
}

TwoDimensionSpatialCoordinate* TwoDimensionSpatialCoordinate::Clone() const{
	return new TwoDimensionSpatialCoordinate(*this);
}

double TwoDimensionSpatialCoordinate::GetX() const{
	return _x;
}

double TwoDimensionSpatialCoordinate::GetY() const{
	return _y;
}

TwoDimensionSpatialCoordinateVector::size_type TwoDimensionSpatialCoordinate::GetCoordinateIndex() const{
	return _coordinateIndex;
}

void TwoDimensionSpatialCoordinate::SetX(double newVal){
	_x = newVal;
}

void TwoDimensionSpatialCoordinate::SetY(double newVal){
	_y = newVal;
}

void TwoDimensionSpatialCoordinate::SetCoordinateIndex(TwoDimensionSpatialCoordinateVector::size_type newVal){
	_coordinateIndex = newVal;
}

bool TwoDimensionSpatialCoordinate::SpatialCoordinateSortPredicate(const TwoDimensionSpatialCoordinate& coord1, const TwoDimensionSpatialCoordinate& coord2)
{
	return coord1.GetCoordinateIndex() < coord2.GetCoordinateIndex();
}
