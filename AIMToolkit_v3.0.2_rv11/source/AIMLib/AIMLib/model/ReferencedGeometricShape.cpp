/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include <limits.h>

#include "ReferencedGeometricShape.h"

#include "../memdebug.h"

using namespace aim_lib;

ReferencedGeometricShape::ReferencedGeometricShape(void) : _referencedShapeIdentifier(INT_MIN){
}

ReferencedGeometricShape::ReferencedGeometricShape(const ReferencedGeometricShape& refGeoShape){
	*this = refGeoShape;
}

ReferencedGeometricShape::~ReferencedGeometricShape(void){
}

ReferencedGeometricShape& ReferencedGeometricShape::operator=(const ReferencedGeometricShape& refGeoShape){
	if (this != &refGeoShape)
	{
		_cagridId					= refGeoShape._cagridId;
		_referencedShapeIdentifier	= refGeoShape._referencedShapeIdentifier;
	}
	return *this;
}

ReferencedGeometricShape* ReferencedGeometricShape::Clone() const{
	return new ReferencedGeometricShape(*this);
}

int ReferencedGeometricShape::GetReferencedShapeIdentifier() const{
	return _referencedShapeIdentifier;
}

void ReferencedGeometricShape::SetReferencedShapeIdentifier(int newVal){
	_referencedShapeIdentifier = newVal;
}
