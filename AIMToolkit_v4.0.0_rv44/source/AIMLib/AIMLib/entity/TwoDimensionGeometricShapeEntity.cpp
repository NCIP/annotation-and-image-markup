/*L
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
