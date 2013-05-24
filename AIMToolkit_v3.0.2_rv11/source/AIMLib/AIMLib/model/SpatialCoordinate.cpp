/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "SpatialCoordinate.h"

using namespace aim_lib;

SpatialCoordinate::SpatialCoordinate(){
	_cagridId = 0;
}

SpatialCoordinate::SpatialCoordinate(int coordianteIndex) : _coordinateIndex(coordianteIndex){
	_cagridId = 0;
}

SpatialCoordinate::SpatialCoordinate(const SpatialCoordinate& spatialCoordinate){
	_cagridId			= spatialCoordinate._cagridId;
	_coordinateIndex	= spatialCoordinate._coordinateIndex;
}

SpatialCoordinate::~SpatialCoordinate(){

}

const SpatialCoordinate::SpatialCoordinateType SpatialCoordinate::GetCoordinateType() const{
	return SpatialCoordinate::T_UNDEFINED_SPCOORD;
}

const int SpatialCoordinate::GetCoordinateIndex() const{
	return _coordinateIndex;
}

void SpatialCoordinate::SetCoordinateIndex(int newVal){
	_coordinateIndex = newVal;
}

bool SpatialCoordinate::SpatialCoordinateSortPredicate(const SpatialCoordinate* pCoord1, const SpatialCoordinate* pCoord2)
{
	return pCoord1->GetCoordinateIndex() < pCoord2->GetCoordinateIndex();
}
