/*
Copyright (c) 2008-2013, Northwestern University
All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 
  Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
 
  Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
 
  Neither the name of the Northwestern University nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "../stdafx.h"

#include "Entity.h"
#include "MarkupEntity.h"
#include "GeometricShapeEntity.h"
#include "TwoDimensionSpatialCoordinate.h"
#include "TwoDimensionGeometricShapeEntity.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;
using iso_21090::II;

TwoDimensionGeometricShapeEntity::TwoDimensionGeometricShapeEntity(const string& typeName, long numOfPoints /*=-1*/) :
		GeometricShapeEntity(typeName), _referencedFrameNumber(-1){
	_numOfPoints = numOfPoints;

	// Ensure that we have required number of points
	while(_numOfPoints >= 0 && _twoDimensionSpatialCoordinateCollection.size() <  (TwoDimensionSpatialCoordinateVector::size_type)_numOfPoints)
	{
		TwoDimensionSpatialCoordinate spatialCoord(0, 0, _twoDimensionSpatialCoordinateCollection.size());
		_twoDimensionSpatialCoordinateCollection.push_back(spatialCoord);
	}
}

TwoDimensionGeometricShapeEntity::TwoDimensionGeometricShapeEntity(const TwoDimensionGeometricShapeEntity& geoShapeEntity) : GeometricShapeEntity(geoShapeEntity){
	*this = geoShapeEntity;
}

TwoDimensionGeometricShapeEntity& TwoDimensionGeometricShapeEntity::operator =(const TwoDimensionGeometricShapeEntity& geoShapeEntity){

	if (this != &geoShapeEntity)
	{
		GeometricShapeEntity::operator=(geoShapeEntity);
		_referencedFrameNumber	= geoShapeEntity._referencedFrameNumber;
		_uri					= geoShapeEntity._uri;
		_numOfPoints			= geoShapeEntity._numOfPoints;

		SetImageReferenceUid(geoShapeEntity.GetImageReferenceUid());
		SetTwoDimensionSpatialCoordinateCollection(geoShapeEntity.GetTwoDimensionSpatialCoordinateCollection());
	}

	return *this;
}

TwoDimensionGeometricShapeEntity::~TwoDimensionGeometricShapeEntity(){
}

const II* TwoDimensionGeometricShapeEntity::GetImageReferenceUid() const {
	return _imageReferenceUid.get();
}

int TwoDimensionGeometricShapeEntity::GetReferencedFrameNumber() const {
	return _referencedFrameNumber;
}

const string& TwoDimensionGeometricShapeEntity::GetUri() const {
	return _uri;
}

const TwoDimensionSpatialCoordinateVector& TwoDimensionGeometricShapeEntity::GetTwoDimensionSpatialCoordinateCollection() const{
	return _twoDimensionSpatialCoordinateCollection;
}

void TwoDimensionGeometricShapeEntity::SetImageReferenceUid(const II* newVal){
	_imageReferenceUid.reset(newVal ? new II(*newVal) : NULL);
}

void TwoDimensionGeometricShapeEntity::SetReferencedFrameNumber(int newVal){
	_referencedFrameNumber = newVal;
}

void TwoDimensionGeometricShapeEntity::SetUri(const string& newVal){
	_uri = newVal;
}

void TwoDimensionGeometricShapeEntity::SetTwoDimensionSpatialCoordinateCollection(const TwoDimensionSpatialCoordinateVector& spatialCoordinateCollection){
	_twoDimensionSpatialCoordinateCollection.assign(spatialCoordinateCollection.begin(), spatialCoordinateCollection.end());
}
