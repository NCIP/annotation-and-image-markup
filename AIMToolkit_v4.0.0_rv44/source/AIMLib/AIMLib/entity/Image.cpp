/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "GeneralImage.h"
#include "ImagePlane.h"
#include "Image.h"

using namespace aim_lib;
using iso_21090::II;

Image::Image(){
}

Image::Image(const Image& image){
	*this = image;
}

Image& Image::operator =(const Image& image){
	_sopClassUid		= image._sopClassUid;
	_sopInstanceUid		= image._sopInstanceUid;
	SetGeneralImage(image.GetGeneralImage());
	SetImagePlane(image.GetImagePlane());

	return *this;
}

Image::~Image(){
}

const iso_21090::II& Image::GetSopClassUid() const{
	return _sopClassUid;
}

const iso_21090::II& Image::GetSopInstanceUid() const{
	return _sopInstanceUid;
}

const GeneralImage* Image::GetGeneralImage() const{
	return _generalImage.get();
}

const ImagePlane* Image::GetImagePlane() const{
	return _imagePlane.get();
}

void Image::SetSopClassUid(const iso_21090::II& newVal){
	_sopClassUid = newVal;
}

void Image::SetSopInstanceUid(const iso_21090::II& newVal){
	_sopInstanceUid = newVal;
}

void Image::SetGeneralImage(const GeneralImage *newVal){
	_generalImage.reset(newVal ? new GeneralImage(*newVal) : NULL);
}

void Image::SetImagePlane(const ImagePlane *newVal){
	_imagePlane.reset(newVal ? new ImagePlane(*newVal) : NULL);
}
