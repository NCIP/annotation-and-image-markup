/*
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
#include "Point.h"
#include "MultiPoint.h"
#include "Ellipse.h"
#include "Polyline.h"

using std::string;
using namespace aim_lib;

GeometricShape::GeometricShape(const string& typeName, long numOfPoints /*=-1*/) : AimBase(typeName){
	_numOfPoints = numOfPoints;

	// Ensure that we have required number of points
	while(_numOfPoints >= 0 && _spatialCoordinateCollection.size() <  (SpatialCoordPtrVector::size_type)_numOfPoints)
		_spatialCoordinateCollection.push_back(NULL);

	_includeFlag	= false;
	_shapeIdetifier	= -1;
}

GeometricShape::GeometricShape(const GeometricShape& shape) : AimBase(shape){
	*this = shape;
}

GeometricShape& GeometricShape::operator =(const GeometricShape& shape){

	if (this != &shape)
	{
		AimBase::operator=(shape);

		_cagridId		= shape._cagridId;
		_shapeIdetifier	= shape._shapeIdetifier;
		_includeFlag	= shape._includeFlag;
		_lineColor		= shape._lineColor;
		_lineOpacity	= shape._lineOpacity;
		_lineStyle		= shape._lineStyle;
		_lineThickness	= shape._lineThickness;
		this->SetSpatialCoordinateCollection(shape._spatialCoordinateCollection);
		_numOfPoints = shape._numOfPoints;
	}

	return *this;
}

GeometricShape::~GeometricShape(){
	this->FreeAllSpatialCoords();
}

int GeometricShape::GetShapeIdentifier() const {

	return _shapeIdetifier;
}

bool GeometricShape::GetIncludeFlag() const {

	return _includeFlag;
}

const string& GeometricShape::GetLineColor() const {

	return _lineColor;
}

const string& GeometricShape::GetLineOpacity() const {

	return _lineOpacity;
}

const string& GeometricShape::GetLineStyle() const {

	return _lineStyle;
}

const string& GeometricShape::GetLineThickness() const {

	return _lineThickness;
}

const SpatialCoordPtrVector& GeometricShape::GetSpatialCoordinateCollection() const{

	return _spatialCoordinateCollection;
}

void GeometricShape::SetShapeIdentifier(int newVal){

	_shapeIdetifier = newVal;
}

void GeometricShape::SetIncludeFlag(bool newVal){

	_includeFlag = newVal;
}

void GeometricShape::SetLineColor(const string& newVal){

	_lineColor = newVal;
}

void GeometricShape::SetLineOpacity(const string& newVal){

	_lineOpacity = newVal;
}

void GeometricShape::SetLineStyle(const string& newVal){

	_lineStyle = newVal;
}

void GeometricShape::SetLineThickness(const string& newVal){

	_lineThickness = newVal;
}

void GeometricShape::SetSpatialCoordinateCollection(const SpatialCoordPtrVector& spatialCoordinateCollection){

	this->FreeAllSpatialCoords();
	for(SpatialCoordPtrVector::size_type i=0; i < spatialCoordinateCollection.size(); i++)
	{
		_spatialCoordinateCollection.push_back(spatialCoordinateCollection[i]->Clone());
	}
}

void GeometricShape::FreeAllSpatialCoords(){

	while(_spatialCoordinateCollection.size() > 0)
	{
		delete _spatialCoordinateCollection[_spatialCoordinateCollection.size()-1];
		_spatialCoordinateCollection.pop_back();
	}
	_spatialCoordinateCollection.clear();
}

void GeometricShape::ReplaceSpatialCoordinate(SpatialCoordPtrVector::size_type position, const SpatialCoordinate& newSpatialCoordinate){
	assert(position >= 0 && position < _spatialCoordinateCollection.size());

	if (position >= 0 && position < _spatialCoordinateCollection.capacity())
	{
		delete _spatialCoordinateCollection[position];
		_spatialCoordinateCollection[position] = newSpatialCoordinate.Clone();
	}
}

const GeometricShape::E_ShapeType GeometricShape::GetShapeType() const{
	if (dynamic_cast<const Point*>(this) != NULL)
		return SHT_Point;
	else if(dynamic_cast<const Circle*>(this) != NULL)
		return SHT_Circle;
	else if(dynamic_cast<const MultiPoint*>(this) != NULL)
		return SHT_Multipoint;
	else if(dynamic_cast<const Ellipse*>(this) != NULL)
		return SHT_Ellipse;
	else if(dynamic_cast<const Polyline*>(this) != NULL)
		return SHT_Polyline;
	else
		return SHT_Unknown;
}
