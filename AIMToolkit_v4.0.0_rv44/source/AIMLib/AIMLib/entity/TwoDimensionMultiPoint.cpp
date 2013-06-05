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
#include "TwoDimensionMultiPoint.h"

#include "../memdebug.h"

using namespace aim_lib;

TwoDimensionMultiPoint::TwoDimensionMultiPoint() : TwoDimensionGeometricShapeEntity(C_SHAPE_NAME_MULTIPOINT_2D){
}

TwoDimensionMultiPoint::TwoDimensionMultiPoint(const TwoDimensionMultiPoint& multiPoint) : TwoDimensionGeometricShapeEntity(multiPoint){
}

TwoDimensionMultiPoint::~TwoDimensionMultiPoint(){
}

TwoDimensionMultiPoint* TwoDimensionMultiPoint::Clone() const{
	return new TwoDimensionMultiPoint(*this);
}

const TwoDimensionGeometricShapeEntity::TwoDimensionShapeType TwoDimensionMultiPoint::GetShapeType() const{
	return Multipoint_2D;
}
