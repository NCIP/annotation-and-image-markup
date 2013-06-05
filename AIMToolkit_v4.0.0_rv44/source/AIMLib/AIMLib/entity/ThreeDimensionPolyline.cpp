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
#include "ThreeDimensionSpatialCoordinate.h"
#include "ThreeDimensionGeometricShapeEntity.h"
#include "ThreeDimensionPolyline.h"

#include "../memdebug.h"

using namespace aim_lib;

ThreeDimensionPolyline::ThreeDimensionPolyline() : ThreeDimensionGeometricShapeEntity(C_SHAPE_NAME_POLYLINE_3D){
}

ThreeDimensionPolyline::ThreeDimensionPolyline(const ThreeDimensionPolyline& polyline) : ThreeDimensionGeometricShapeEntity(polyline){
}

ThreeDimensionPolyline::~ThreeDimensionPolyline(){
}

ThreeDimensionPolyline* ThreeDimensionPolyline::Clone() const{
	return new ThreeDimensionPolyline(*this);
}

const ThreeDimensionGeometricShapeEntity::ThreeDimensionShapeType ThreeDimensionPolyline::GetShapeType() const{
	return Polyline_3D;
}
