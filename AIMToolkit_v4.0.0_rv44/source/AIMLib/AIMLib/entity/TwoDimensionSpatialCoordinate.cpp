/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
