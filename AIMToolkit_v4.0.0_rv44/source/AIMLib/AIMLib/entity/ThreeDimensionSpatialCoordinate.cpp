/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
