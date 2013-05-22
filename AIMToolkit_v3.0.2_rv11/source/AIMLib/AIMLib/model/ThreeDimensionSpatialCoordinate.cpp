/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "../stdafx.h"

#include "SpatialCoordinate.h"
#include "ThreeDimensionSpatialCoordinate.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;

ThreeDimensionSpatialCoordinate::ThreeDimensionSpatialCoordinate() : SpatialCoordinate(){

}

ThreeDimensionSpatialCoordinate::ThreeDimensionSpatialCoordinate(double x, double y, double z, const std::string& frameOfReferenceUID, int coordinateIndex) :
	SpatialCoordinate(coordinateIndex), _x(x), _y(y), _z(z), _frameOfReferenceUID(frameOfReferenceUID){

}

ThreeDimensionSpatialCoordinate::ThreeDimensionSpatialCoordinate(const ThreeDimensionSpatialCoordinate& spatialCoordinate) : 
	SpatialCoordinate(spatialCoordinate)
{
	_x = spatialCoordinate._x;
	_y = spatialCoordinate._y;
	_z = spatialCoordinate._z;
	_frameOfReferenceUID	= spatialCoordinate._frameOfReferenceUID;
}

ThreeDimensionSpatialCoordinate::~ThreeDimensionSpatialCoordinate(){

}

ThreeDimensionSpatialCoordinate* ThreeDimensionSpatialCoordinate::Clone() const{
	return new ThreeDimensionSpatialCoordinate(*this);
}

const SpatialCoordinate::SpatialCoordinateType ThreeDimensionSpatialCoordinate::GetCoordinateType() const
{
	return SpatialCoordinate::T_3D_SPCOORD;
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

const std::string& ThreeDimensionSpatialCoordinate::GetFrameOfReferenceUID() const{

	return _frameOfReferenceUID;
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

void ThreeDimensionSpatialCoordinate::SetFrameOfReferenceUID(const std::string& newVal){

	_frameOfReferenceUID = newVal;
}
