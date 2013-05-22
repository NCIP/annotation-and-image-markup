/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
