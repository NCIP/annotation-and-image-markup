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
