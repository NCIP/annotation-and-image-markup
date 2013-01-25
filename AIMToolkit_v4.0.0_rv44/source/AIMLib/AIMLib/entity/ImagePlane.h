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

#pragma once
#ifndef _AIMLib_ImagePlane_Class_
#define _AIMLib_ImagePlane_Class_

#include <memory>

namespace aim_lib
{
	class AIMLIB_API ImagePlane
	{
	public:
		ImagePlane(void);
		ImagePlane(const ImagePlane& imagePlane);
		virtual ~ImagePlane(void);
		ImagePlane& operator=(const ImagePlane& imagePlane); // need to have it here; otherwise the auto_ptr template will break the build because of the const in the copy constructor
		ImagePlane* Clone() const;

		double* GetRowImageOrientationX() const;
		double* GetRowImageOrientationY() const;
		double* GetRowImageOrientationZ() const;
		double* GetColumnImageOrientationX() const;
		double* GetColumnImageOrientationY() const;
		double* GetColumnImageOrientationZ() const;
		double* GetVerticalPixelSpacing() const;
		double* GetHorizontalPixelSpacing() const;
		double* GetSliceThickness() const;
		double* GetImagePositionX() const;
		double* GetImagePositionY() const;
		double* GetImagePositionZ() const;

		void SetRowImageOrientationX(double* newVal);
		void SetRowImageOrientationY(double* newVal);
		void SetRowImageOrientationZ(double* newVal);
		void SetColumnImageOrientationX(double* newVal);
		void SetColumnImageOrientationY(double* newVal);
		void SetColumnImageOrientationZ(double* newVal);
		void SetVerticalPixelSpacing(double* newVal);
		void SetHorizontalPixelSpacing(double* newVal);
		void SetSliceThickness(double* newVal);
		void SetImagePositionX(double* newVal);
		void SetImagePositionY(double* newVal);
		void SetImagePositionZ(double* newVal);

	protected:
		std::auto_ptr<double> _rowImageOrientationX;
		std::auto_ptr<double> _rowImageOrientationY;
		std::auto_ptr<double> _rowImageOrientationZ;
		std::auto_ptr<double> _columnImageOrientationX;
		std::auto_ptr<double> _columnImageOrientationY;
		std::auto_ptr<double> _columnImageOrientationZ;
		std::auto_ptr<double> _verticalPixelSpacing;
		std::auto_ptr<double> _horizontalPixelSpacing;
		std::auto_ptr<double> _sliceThickness;
		std::auto_ptr<double> _imagePositionX;
		std::auto_ptr<double> _imagePositionY;
		std::auto_ptr<double> _imagePositionZ;
	};
}
#endif // _AIMLib_ImagePlane_Class_
