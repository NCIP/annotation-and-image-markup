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
#include "ImageSeries.h"

using namespace aim_lib;
using namespace iso_21090;

ImageSeries::ImageSeries(){
}

ImageSeries::ImageSeries(const ImageSeries& series){
	_instanceUid	= series._instanceUid;
	_modality		= series._modality;

	SetImageCollection(series.GetImageCollection());
}

ImageSeries::~ImageSeries(){
}

const iso_21090::II& ImageSeries::GetInstanceUid() const{
	return _instanceUid;
}

const iso_21090::CD& ImageSeries::GetModality() const{
	return _modality;
}

const ImageVector& ImageSeries::GetImageCollection() const{
	return _imageCollection;
}

void ImageSeries::SetInstanceUid(const iso_21090::II& newVal){
	_instanceUid = newVal;
}

void ImageSeries::SetModality(const iso_21090::CD& newVal){
	_modality = newVal;
}

void ImageSeries::SetImageCollection(const ImageVector& images){
	_imageCollection.assign(images.begin(), images.end());
}
