/*
*  Copyright Northwestern University
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
#include "TwoDimensionEllipse.h"

#include "../memdebug.h"

using namespace aim_lib;

TwoDimensionEllipse::TwoDimensionEllipse() : TwoDimensionGeometricShapeEntity(C_SHAPE_NAME_ELLIPSE_2D, 4){
}

TwoDimensionEllipse::TwoDimensionEllipse(const TwoDimensionEllipse& ellipse) : TwoDimensionGeometricShapeEntity(ellipse){
}

TwoDimensionEllipse::~TwoDimensionEllipse(){
}

TwoDimensionEllipse* TwoDimensionEllipse::Clone() const{
	return new TwoDimensionEllipse(*this);
}

const TwoDimensionGeometricShapeEntity::TwoDimensionShapeType TwoDimensionEllipse::GetShapeType() const{
	return Ellipse_2D;
}

const TwoDimensionSpatialCoordinateVector& TwoDimensionEllipse::GetEllipseCollection(){
	return TwoDimensionGeometricShapeEntity::GetTwoDimensionSpatialCoordinateCollection();
}

void TwoDimensionEllipse::SetEllipseCollection(const TwoDimensionSpatialCoordinateVector& ellipseCollection){
	TwoDimensionGeometricShapeEntity::SetTwoDimensionSpatialCoordinateCollection(ellipseCollection);
}
