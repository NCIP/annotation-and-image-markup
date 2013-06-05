/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "Coordinate.h"

using namespace aim_lib;

Coordinate::Coordinate()
{
}

Coordinate::Coordinate(const Coordinate& coordinate)
{
	*this = coordinate;
}

Coordinate& Coordinate::operator=(const Coordinate& coordinate)
{
	if (this != &coordinate)
	{
		_cagridId		= coordinate._cagridId;
		_dimensionIndex	= coordinate._dimensionIndex;
		_position		= coordinate._position;
	}

	return *this;
}

Coordinate::~Coordinate()
{
}

int Coordinate::GetDimensionIndex() const{
	return _dimensionIndex;
}

void Coordinate::SetDimensionIndex(int newValue){
	_dimensionIndex = newValue;
}

int Coordinate::GetPosition() const{
	return _position;
}

void Coordinate::SetPosition(int newValue){
	_position = newValue;
}
