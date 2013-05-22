/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "../stdafx.h"

#include "AimBase.h"
#include "SpatialCoordinate.h"
#include "GeometricShape.h"
#include "Circle.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;

Circle::Circle() : GeometricShape(C_SHAPE_NAME_CIRCLE, 2){

}

Circle::~Circle(){

}

Circle* Circle::Clone() const
{
	return new Circle(*this);
}

const SpatialCoordinate& Circle::GetCenter() const{

	assert(this->_spatialCoordinateCollection[CenterPoint] != NULL);
	return *this->_spatialCoordinateCollection[CenterPoint];
}

const SpatialCoordinate& Circle::GetRadiusPoint() const{

	assert(this->_spatialCoordinateCollection[CircumferencePoint] != NULL);
	return *this->_spatialCoordinateCollection[CircumferencePoint];
}

void Circle::SetCenter(const SpatialCoordinate& center){
	this->ReplaceSpatialCoordinate(CenterPoint, center);
}

void Circle::SetRadiusPoint(const SpatialCoordinate& radiusPoint){
	this->ReplaceSpatialCoordinate(CircumferencePoint, radiusPoint);
}
