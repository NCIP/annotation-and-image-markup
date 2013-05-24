/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
