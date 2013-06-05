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
#include "ThreeDimensionPolygon.h"

#include "../memdebug.h"

using namespace aim_lib;

ThreeDimensionPolygon::ThreeDimensionPolygon() : ThreeDimensionGeometricShapeEntity(C_SHAPE_NAME_POLYGON_3D){
}

ThreeDimensionPolygon::ThreeDimensionPolygon(const ThreeDimensionPolygon& polygon) : ThreeDimensionGeometricShapeEntity(polygon){
}

ThreeDimensionPolygon::~ThreeDimensionPolygon(){
}

ThreeDimensionPolygon* ThreeDimensionPolygon::Clone() const{
	return new ThreeDimensionPolygon(*this);
}

const ThreeDimensionGeometricShapeEntity::ThreeDimensionShapeType ThreeDimensionPolygon::GetShapeType() const{
	return Polygon_3D;
}
