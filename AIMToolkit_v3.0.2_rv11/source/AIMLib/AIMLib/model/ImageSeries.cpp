/*
*  2007 – 2013 Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "Image.h"
#include "ImageSeries.h"

using namespace aim_lib;

ImageSeries::ImageSeries(){
}

ImageSeries::ImageSeries(const ImageSeries& series){
	_cagridId		= series._cagridId;
	_instanceUID	= series._instanceUID;

	this->SetImageCollection(series.GetImageCollection());
}

ImageSeries::~ImageSeries(){
}

const std::string& ImageSeries::GetInstanceUID() const{
	return _instanceUID;
}

const ImageVector& ImageSeries::GetImageCollection() const{
	return _imageCollection;
}

void ImageSeries::SetInstanceUID(const std::string& newVal){
	_instanceUID = newVal;
}

void ImageSeries::SetImageCollection(const ImageVector& images){
	_imageCollection.assign(images.begin(), images.end());
}
