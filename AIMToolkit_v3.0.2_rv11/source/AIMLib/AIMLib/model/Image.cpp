/*
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "Image.h"

using namespace aim_lib;

Image::Image(){
}

Image::Image(const Image& image){
	*this = image;
}

Image& Image::operator =(const Image& image){
	_cagridId			= image._cagridId;
	_sopClassUID		= image._sopClassUID;
	_sopInstanceUID		= image._sopInstanceUID;

	return *this;
}

Image::~Image(){
}

const std::string& Image::GetSopClassUID() const{
	return _sopClassUID;
}

const std::string& Image::GetSopInstanceUID() const{
	return _sopInstanceUID;
}

void Image::SetSopClassUID(const std::string& newVal){
	_sopClassUID = newVal;
}

void Image::SetSopInstanceUID(const std::string& newVal){
	_sopInstanceUID = newVal;
}
