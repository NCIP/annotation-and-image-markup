/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "AimBase.h"
#include "SpatialCoordinate.h"
#include "GeometricShape.h"
#include "Point.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;

Point::Point() : GeometricShape(C_SHAPE_NAME_POINT, 1){

}

Point::~Point(){

}

Point* Point::Clone() const
{
	return new Point(*this);
}

const SpatialCoordinate& Point::GetCenter(){

	assert(_spatialCoordinateCollection.size() > CenterPoint);
	return  *_spatialCoordinateCollection[CenterPoint];
}

void Point::SetCenter(const SpatialCoordinate& spatialCoordinate){
	this->ReplaceSpatialCoordinate(CenterPoint, spatialCoordinate);
}
