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
#include "ThreeDimensionSpatialCoordinate.h"
#include "ThreeDimensionGeometricShapeEntity.h"
#include "ThreeDimensionMultiPoint.h"

#include "../memdebug.h"

using namespace aim_lib;

ThreeDimensionMultiPoint::ThreeDimensionMultiPoint() : ThreeDimensionGeometricShapeEntity(C_SHAPE_NAME_MULTIPOINT_3D){
}

ThreeDimensionMultiPoint::ThreeDimensionMultiPoint(const ThreeDimensionMultiPoint& multiPoint) : ThreeDimensionGeometricShapeEntity(multiPoint){
}

ThreeDimensionMultiPoint::~ThreeDimensionMultiPoint(){
}

ThreeDimensionMultiPoint* ThreeDimensionMultiPoint::Clone() const{
	return new ThreeDimensionMultiPoint(*this);
}

const ThreeDimensionGeometricShapeEntity::ThreeDimensionShapeType ThreeDimensionMultiPoint::GetShapeType() const{
	return Multipoint_3D;
}
