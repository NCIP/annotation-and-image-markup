/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "SpatialCoordinate.h"
#include "TwoDimensionSpatialCoordinate.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;

TwoDimensionSpatialCoordinate::TwoDimensionSpatialCoordinate() : SpatialCoordinate(),
	_referencedFrameNumber(1) // 1 - default
{

}

TwoDimensionSpatialCoordinate::TwoDimensionSpatialCoordinate(double x, double y, const std::string& imageReferenceUID, int coordinateIndex, long referenceFrameNumber/* = 1*/)
 : SpatialCoordinate(coordinateIndex), _x(x), _y(y), _imageReferenceUID(imageReferenceUID), _referencedFrameNumber(referenceFrameNumber)
{

}

TwoDimensionSpatialCoordinate::TwoDimensionSpatialCoordinate(const TwoDimensionSpatialCoordinate& spatialCoordinate) : SpatialCoordinate(spatialCoordinate)
{
	_x						= spatialCoordinate._x;
	_y						= spatialCoordinate._y;
	_referencedFrameNumber	= spatialCoordinate._referencedFrameNumber;
	_imageReferenceUID		= spatialCoordinate._imageReferenceUID;
}

TwoDimensionSpatialCoordinate::~TwoDimensionSpatialCoordinate(){

}

TwoDimensionSpatialCoordinate* TwoDimensionSpatialCoordinate::Clone() const{
	return new TwoDimensionSpatialCoordinate(*this);
}

const SpatialCoordinate::SpatialCoordinateType TwoDimensionSpatialCoordinate::GetCoordinateType() const{
	return SpatialCoordinate::T_2D_SPCOORD;
}

double TwoDimensionSpatialCoordinate::GetX() const{

	return _x;
}

double TwoDimensionSpatialCoordinate::GetY() const{

	return _y;
}

long TwoDimensionSpatialCoordinate::GetReferencedFrameNumber() const{

	return _referencedFrameNumber;
}

const string& TwoDimensionSpatialCoordinate::GetImageReferenceUID() const{

	return _imageReferenceUID;
}

void TwoDimensionSpatialCoordinate::SetX(double newVal){

	_x = newVal;
}

void TwoDimensionSpatialCoordinate::SetY(double newVal){

	_y = newVal;
}

void TwoDimensionSpatialCoordinate::SetReferencedFrameNumber(long newVal){

	_referencedFrameNumber = newVal;
}

void TwoDimensionSpatialCoordinate::SetImageReferenceUID(const string& newVal){

	_imageReferenceUID = newVal;
}
