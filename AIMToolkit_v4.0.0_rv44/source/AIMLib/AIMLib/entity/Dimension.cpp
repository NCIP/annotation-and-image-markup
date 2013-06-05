/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "Dimension.h"

using std::string;
using namespace aim_lib;

Dimension::Dimension(){
}

Dimension::Dimension(const Dimension& dimension){
	*this = dimension;
}

Dimension& Dimension::operator=(const Dimension& dimension){
	if (this != &dimension)
	{
		_index		= dimension._index;
		_size		= dimension._size;
		_label		= dimension._label;
	}

	return *this;
}

Dimension::~Dimension(){
}

int Dimension::GetIndex() const{
	return _index;
}

void Dimension::SetIndex(int newVal){
	_index = newVal;
}

int Dimension::GetSize() const{
	return _size;
}

void Dimension::SetSize(int newVal){
	_size = newVal;
}

const string& Dimension::GetLabel() const{
	return _label;
}

void Dimension::SetLabel(const string& newVal){
	_label = newVal;
}
