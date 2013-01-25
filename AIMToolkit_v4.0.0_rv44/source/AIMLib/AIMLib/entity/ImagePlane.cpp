/*
Copyright (c) 2008-2013, Northwestern University
All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 
  Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
 
  Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
 
  Neither the name of the Northwestern University nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "../stdafx.h"
#include "ImagePlane.h"

#include "../memdebug.h"

using namespace aim_lib;

ImagePlane::ImagePlane(void){
}

ImagePlane::ImagePlane(const ImagePlane& imagePlane){
	*this = imagePlane;
}

ImagePlane::~ImagePlane(void){
}

ImagePlane& ImagePlane::operator=(const ImagePlane& imagePlane){
	if (this != &imagePlane)
	{
		SetRowImageOrientationX(imagePlane.GetRowImageOrientationX());
		SetRowImageOrientationY(imagePlane.GetRowImageOrientationY());
		SetRowImageOrientationZ(imagePlane.GetRowImageOrientationZ());
		SetColumnImageOrientationX(imagePlane.GetColumnImageOrientationX());
		SetColumnImageOrientationY(imagePlane.GetColumnImageOrientationY());
		SetColumnImageOrientationZ(imagePlane.GetColumnImageOrientationZ());
		SetVerticalPixelSpacing(imagePlane.GetVerticalPixelSpacing());
		SetHorizontalPixelSpacing(imagePlane.GetHorizontalPixelSpacing());
		SetSliceThickness(imagePlane.GetSliceThickness());
		SetImagePositionX(imagePlane.GetImagePositionX());
		SetImagePositionY(imagePlane.GetImagePositionY());
		SetImagePositionZ(imagePlane.GetImagePositionZ());
	}
	return *this;
}

ImagePlane* ImagePlane::Clone() const{
	return new ImagePlane(*this);
}

double* ImagePlane::GetRowImageOrientationX() const{
	return _rowImageOrientationX.get();
}

double* ImagePlane::GetRowImageOrientationY() const{
	return _rowImageOrientationY.get();
}

double* ImagePlane::GetRowImageOrientationZ() const{
	return _rowImageOrientationX.get();
}

double* ImagePlane::GetColumnImageOrientationX() const{
	return _columnImageOrientationX.get();
}

double* ImagePlane::GetColumnImageOrientationY() const{
	return _columnImageOrientationY.get();
}

double* ImagePlane::GetColumnImageOrientationZ() const{
	return _columnImageOrientationX.get();
}

double* ImagePlane::GetVerticalPixelSpacing() const{
	return _verticalPixelSpacing.get();
}

double* ImagePlane::GetHorizontalPixelSpacing() const{
	return _horizontalPixelSpacing.get();
}

double* ImagePlane::GetSliceThickness() const{
	return _sliceThickness.get();
}

double* ImagePlane::GetImagePositionX() const{
	return _imagePositionX.get();
}

double* ImagePlane::GetImagePositionY() const{
	return _imagePositionY.get();
}

double* ImagePlane::GetImagePositionZ() const{
	return _imagePositionZ.get();
}


void ImagePlane::SetRowImageOrientationX(double* newVal){
	_rowImageOrientationX.reset(newVal ? new double(*newVal) : NULL);
}

void ImagePlane::SetRowImageOrientationY(double* newVal){
	_rowImageOrientationY.reset(newVal ? new double(*newVal) : NULL);
}

void ImagePlane::SetRowImageOrientationZ(double* newVal){
	_rowImageOrientationZ.reset(newVal ? new double(*newVal) : NULL);
}

void ImagePlane::SetColumnImageOrientationX(double* newVal){
	_columnImageOrientationX.reset(newVal ? new double(*newVal) : NULL);
}

void ImagePlane::SetColumnImageOrientationY(double* newVal){
	_columnImageOrientationY.reset(newVal ? new double(*newVal) : NULL);
}

void ImagePlane::SetColumnImageOrientationZ(double* newVal){
	_columnImageOrientationZ.reset(newVal ? new double(*newVal) : NULL);
}

void ImagePlane::SetVerticalPixelSpacing(double* newVal){
	_verticalPixelSpacing.reset(newVal ? new double(*newVal) : NULL);
}

void ImagePlane::SetHorizontalPixelSpacing(double* newVal){
	_horizontalPixelSpacing.reset(newVal ? new double(*newVal) : NULL);
}

void ImagePlane::SetSliceThickness(double* newVal){
	_sliceThickness.reset(newVal ? new double(*newVal) : NULL);
}

void ImagePlane::SetImagePositionX(double* newVal){
	_imagePositionX.reset(newVal ? new double(*newVal) : NULL);
}

void ImagePlane::SetImagePositionY(double* newVal){
	_imagePositionY.reset(newVal ? new double(*newVal) : NULL);
}

void ImagePlane::SetImagePositionZ(double* newVal){
	_imagePositionZ.reset(newVal ? new double(*newVal) : NULL);
}
