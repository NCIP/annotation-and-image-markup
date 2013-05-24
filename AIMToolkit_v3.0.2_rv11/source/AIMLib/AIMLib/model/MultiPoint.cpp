/*
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
#include "MultiPoint.h"

#include "../memdebug.h"

using std::string;
using namespace aim_lib;

MultiPoint::MultiPoint() : GeometricShape(C_SHAPE_NAME_MULTIPOINT){

}

MultiPoint::~MultiPoint(){

}

MultiPoint* MultiPoint::Clone() const
{
	return new MultiPoint(*this);
}
