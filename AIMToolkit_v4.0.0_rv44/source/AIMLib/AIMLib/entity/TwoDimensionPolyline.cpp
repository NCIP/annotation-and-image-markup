/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "Entity.h"
#include "MarkupEntity.h"
#include "GeometricShapeEntity.h"
#include "TwoDimensionSpatialCoordinate.h"
#include "TwoDimensionGeometricShapeEntity.h"
#include "TwoDimensionPolyline.h"

#include "../memdebug.h"

using namespace aim_lib;

TwoDimensionPolyline::TwoDimensionPolyline() : TwoDimensionGeometricShapeEntity(C_SHAPE_NAME_POLYLINE_2D){
}

TwoDimensionPolyline::TwoDimensionPolyline(const TwoDimensionPolyline& polyline) : TwoDimensionGeometricShapeEntity(polyline){
}

TwoDimensionPolyline::~TwoDimensionPolyline(){
}

TwoDimensionPolyline* TwoDimensionPolyline::Clone() const{
	return new TwoDimensionPolyline(*this);
}

const TwoDimensionGeometricShapeEntity::TwoDimensionShapeType TwoDimensionPolyline::GetShapeType() const{
	return Polyline_2D;
}
