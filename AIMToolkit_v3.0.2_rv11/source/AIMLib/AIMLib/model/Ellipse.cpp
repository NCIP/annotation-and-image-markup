/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "../stdafx.h"

#include "AimBase.h"
#include "SpatialCoordinate.h"
#include "GeometricShape.h"
#include "Ellipse.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;

Ellipse::Ellipse() : GeometricShape(C_SHAPE_NAME_ELLIPSE, 4){

}

Ellipse::~Ellipse(){

}

aim_lib::Ellipse* Ellipse::Clone() const
{
	return new Ellipse(*this);
}

const SpatialCoordPtrVector& Ellipse::GetEllipseCollection(){

	return GeometricShape::GetSpatialCoordinateCollection();
}

void Ellipse::SetEllipseCollection(const SpatialCoordPtrVector& ellipseCollection){
	GeometricShape::SetSpatialCoordinateCollection(ellipseCollection);
}
